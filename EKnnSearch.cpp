#include "StdAfx.h"
#include "EKnnSearch.h"

EKnnSearch::EKnnSearch()
{
	distances.dimension = NULL;
	distances.value = NULL;
//	this->ActualPage = knnResults.begin();
}

EKnnSearch::~EKnnSearch(void)
{
//	for (list<KNNRESULTTYPE>::iterator iter = knnResults.begin(); iter != knnResults.end(); iter++)
//		delete [] iter->indices;
	if ( distances.dimension != NULL ) delete [] distances.dimension;
	if ( distances.value != NULL ) delete [] distances.value;
}

double EKnnSearch::distMeasure(double a)
{
	return a*a;
}

//// function getQueryIndex : ///
//// using bisecting method to find the nearest vector in the database to the query vector ////
//// based on their means ////
DWORD getQueryIndex( double *means, DWORD databaseSize, double queryMean)
{
	DWORD queryMeanIndex;
	if ( means[0]>queryMean)
	{
		queryMeanIndex = 0;
	}
	else
	{
		if ( means[databaseSize-1] < queryMean )
		{
			queryMeanIndex = databaseSize-1;
		} 
		else
		{
			// bisecting search //
			DWORD p;
			DWORD left =0;
			DWORD right =databaseSize -1;
			while ( left < right-1 ) {
				p =(left+right)/2;
				if ( queryMean < means[p] ) {
					right=p;
				} else 
					left=p;
			}
			if ( abs(queryMean - means[left]) < abs(queryMean - means[right]) ) {
				p=left;
			}else
				p=right;

			queryMeanIndex = p;
		}
	}
	return queryMeanIndex;
}


DWORD EKnnSearch::EKNNS( double *database, double *means, DWORD databaseSize, double *normalizedQueryVector, WORD featureDimension, double queryMean, DWORD k, DWORD * &resultParameter)
{
	multimap<KNN_SEARCH_RESULT_TYPE> searchResult;

	//// Step 1: finding the index of the query feature in the means list ////
	//// using the bisecting method ////
	// the functoin also checks if nearest mean value to queryMean could be in the orderd database //
	DWORD queryMeanIndex = getQueryIndex(database,databaseSize,queryMean);
		
	//// get the queryMeanIndex - k/2 lower and the queryMeanIndex + k/2 higher range ////
	//// take attation on overflow of DWORD ////
	//// low and high are indices of the means array ////
	DWORD low, high;
	if ( queryMeanIndex < k/2 ) {				//// the first k
		low = 0;
		high = k;
	}else
	if ( queryMeanIndex >= databaseSize - k/2 ) { //// the last k
		low = databaseSize - k;
		high = databaseSize;
	}else {
		low = queryMeanIndex - k/2;						//// low inclusive
		high = queryMeanIndex + (DWORD)(k/2.0 + 0.5);	//// high exclusive
	}

	// create sorted list (searchResult) of distances from low to high-1
	//// Step 2 ////
	double dist;
	DWORD i;
	for (i=low; i < high; i++) {
		dist = 0;
		for (WORD dim=0; dim < featureDimension; dim++)	// calculate the squared euclidean distance
			dist += distMeasure( database[i*featureDimension+dim] - normalizedQueryVector[dim] );
		searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(dist,i) );
	}
		
	//// The knn search on distances - searching on the database ////
	//// Step 3 ////
	double upperDistanceBound = (--searchResult.end())->first;		// ! using variables for faster program execution
	double lowerMeanBound = queryMean - sqrt(upperDistanceBound/featureDimension);
	double upperMeanBound = queryMean + sqrt(upperDistanceBound/featureDimension);
	bool pds;
	double distance;
	WORD dim;
	bool flag1 = true;
	bool flag2 = true;
	while ( flag1 || flag2 ) {
	// the look at the lower index on the database
		if ( flag1 ) {
		 if ( low > 0 ) {
			low--;
			if ( lowerMeanBound < means[low] && means[low] < upperMeanBound ) {
				distance = 0;
				pds = true;
				for (dim=0; dim < featureDimension; dim++) {
					// squared euclidean distance
					distance += distMeasure(database[low*featureDimension+dim] - normalizedQueryVector[dim] );
					if ( distance >= upperDistanceBound ) {
						pds = false;
						break;
					}
				}
				if (pds) {
					searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distance,low) );	// insert distance in sorted list
					searchResult.erase( --searchResult.end() );		// delete the last element
					upperDistanceBound = (--searchResult.end())->first;			// new upper bound
					lowerMeanBound = queryMean - sqrt(upperDistanceBound/featureDimension);	// new lower bound
					upperMeanBound = queryMean + sqrt(upperDistanceBound/featureDimension); // new upper bound
				} 
			} else flag1 = false; // else of the mean border condition
		 } else flag1 = false; // reaching the database top position
		}
	// the look at the higher index on the database
		if ( flag2 ) {
		 if ( high < databaseSize ) {
			if ( lowerMeanBound < means[high] && means[high] < upperMeanBound ) {
				distance = 0;
				pds = true;
				for (dim=0; dim < featureDimension; dim++) {
					// euclidean distance
					distance += distMeasure(database[high*featureDimension+dim] - normalizedQueryVector[dim] );
					if ( distance >= upperDistanceBound ) {
						pds = false;
						break;
					}
				}
				if (pds) {
					searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distance,high) );	// insert distance in sorted list
					searchResult.erase( --searchResult.end() );	// delete the last element
					upperDistanceBound = (--searchResult.end())->first;			// new upper bound
					lowerMeanBound = queryMean - sqrt(upperDistanceBound/featureDimension);	// new lower bound
					upperMeanBound = queryMean + sqrt(upperDistanceBound/featureDimension); // new upper bound
				} 
			} else flag2 = false;  //  no mean in the mean bound range found
			high++;
		 } else flag2 = false;   // reaching the end of the database
		}
	} // end of while - the walk through the database

	// convert searchResult to an array, for interface definitions
	resultParameter = new DWORD[databaseSize];
	multimap<KNN_SEARCH_RESULT_TYPE>::iterator sr = searchResult.begin();
	for (i=0; i < k && sr != searchResult.end(); i++ )
	{
		resultParameter[i] = sr->second;
		sr++;
	}

	return searchResult.size();	
}


DWORD EKnnSearch::IEKNNS( double *database, double *means, DWORD databaseSize, double *queryVector, WORD featureDimension, double queryMean, DWORD k, DWORD * &resultParameter)
{
	this->Database = database;
	this->Means = means;
	this->DatabaseSize = databaseSize;
	this->FeatureDimension = featureDimension; 
	this->K = k;
	this->NormalizedQueryVector = queryVector;

	for (list<KNNRESULTTYPE>::iterator iter = knnResults.begin(); iter != knnResults.end(); iter++)
		delete [] iter->indices;
	knnResults.clear();
	this->ActualPage = knnResults.begin();

	//// for distance arrays ////
	if ( distances.dimension != NULL ) delete [] distances.dimension;
	if ( distances.value != NULL ) delete [] distances.value;
	//// create new arrays
	distances.dimension = new INT64[databaseSize];
	distances.value = new double[databaseSize];
	//// initzialise distances with zeros
	DWORD i;
	for (i=0; i < databaseSize; i++) {
		distances.dimension[i] = 0;
		distances.value[i] = 0;
	}
	
	multimap<KNN_SEARCH_RESULT_TYPE> searchResult;

	//// Step 1: finding the index of the query feature in the means list ////
	//// using the bisecting method ////
	// the functoin also checks if nearest mean value to queryMean could be in the orderd database //
	this->QueryMean = queryMean;		// !! for faster memory access
	this->QueryMeanIndex = getQueryIndex(database,databaseSize,queryMean);
	
	
	//// get the queryMeanIndex - k/2 lower and the queryMeanIndex + k/2 higher range ////
	//// take attation on overflow of DWORD ////
	//// low and high are indices of the means array ////
	DWORD low, high;
	if ( this->QueryMeanIndex < k/2 ) {				//// the first k
		low = 0;
		high = k;
	}else
	if ( this->QueryMeanIndex >= databaseSize - k/2 ) { //// the last k
		low = databaseSize - k;
		high = databaseSize;
	}else {
		low = this->QueryMeanIndex - k/2;						//// low inclusive
		high = this->QueryMeanIndex + (DWORD)(k/2.0 + 0.5);	//// high exclusive
	}

	// create sorted list (searchResult) of distances from low to high-1
	//// Step 2 ////
	
	double dist;
	for (i=low; i < high; i++) {
		dist = 0;
		for (WORD dim=0; dim < featureDimension; dim++)	// calculate the squared euclidean distance
			dist += distMeasure( database[i*featureDimension+dim] - this->NormalizedQueryVector[dim]);
		distances.value[i] = dist;
		distances.dimension[i] = featureDimension;
		searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(dist,i) );
	}
		
	//// The knn search on distances - searching on the database ////
	//// Step 3 ////
	double upperDistanceBound = (--searchResult.end())->first;		// ! using variables for faster program execution
	double lowerMeanBound = queryMean - sqrt(upperDistanceBound/featureDimension);
	double upperMeanBound = queryMean + sqrt(upperDistanceBound/featureDimension);
	bool pds;
	double distance;
	WORD dim;
	bool flag1 = true;
	bool flag2 = true;
	while ( flag1 || flag2 ) {
	// the look at the lower index on the database
		if ( flag1 ) {
		 if (low > 0 ) {
			low--;
			if ( lowerMeanBound < means[low] && means[low] < upperMeanBound ) {
				distance = 0;
				pds = true;
				for (dim=0; dim < featureDimension; dim++) {
					// squared euclidean distance
					distance += distMeasure(database[low*featureDimension+dim] - NormalizedQueryVector[dim]);
					if ( distance >= upperDistanceBound ) {
						pds = false;
						dim++;	// cause next for loop will start with this dimension
						break;
					}
				}
				if (pds) {
					searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distance,low) );	// insert distance in sorted list
					searchResult.erase( --searchResult.end() );		// delete the last element
					upperDistanceBound = (--searchResult.end())->first;			// new upper bound
					lowerMeanBound = queryMean - sqrt(upperDistanceBound/featureDimension);	// new lower bound
					upperMeanBound = queryMean + sqrt(upperDistanceBound/featureDimension); // new upper bound
				} 
				// insert new distance in distance array
				distances.dimension[low] = dim;
				distances.value[low] = distance;    
			} else flag1 = false; // else of the mean border condition
		 } else flag1 = false; // reaching the database top position
		} 
	// the look at the higher index on the database
		if ( flag2 ) {
		 if ( high < databaseSize ) {
			if ( lowerMeanBound < means[high] && means[high] < upperMeanBound ) {
				distance = 0;
				pds = true;
				for (dim=0; dim < featureDimension; dim++) {
					// euclidean distance
					distance += distMeasure(database[high*featureDimension+dim] - this->NormalizedQueryVector[dim]);
					if ( distance >= upperDistanceBound ) {
						pds = false;
						dim++;	// cause next for loop will start with this dimension
						break;
					}
				}
				if (pds) {
					searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distance,high) );	// insert distance in sorted list
					searchResult.erase( --searchResult.end() );	// delete the last element
					upperDistanceBound = (--searchResult.end())->first;			// new upper bound
					lowerMeanBound = queryMean - sqrt(upperDistanceBound/featureDimension);	// new lower bound
					upperMeanBound = queryMean + sqrt(upperDistanceBound/featureDimension); // new upper bound
				} 
				// insert new distance in distance array
				distances.dimension[high] = dim;
				distances.value[high] = distance;    
			} else flag2 = false;  //  no mean in the mean bound range found
			high++;
		 } else flag2 = false;   // reaching the end of the database
		}
	} // end of while - the walk through the database

	// convert searchResult to an array, for interface definitions
	KNNRESULTTYPE result;
	result.size = searchResult.size();
	result.indices = new DWORD[result.size];
	resultParameter = new DWORD[result.size];
	multimap<KNN_SEARCH_RESULT_TYPE>::iterator sr = searchResult.begin();
	for (i=0; i < k && sr != searchResult.end(); i++ )
	{
		resultParameter[i] = result.indices[i] = sr->second;
		distances.dimension[sr->second] = -1;			//// !! mark the allready found vectors - cause futher searching
		sr++;
	}

	knnResults.push_back( result );		// save the result for later use

	return result.size;	

}


DWORD EKnnSearch::IEKNNSnext(DWORD * &resultParameter)
{
	if ( distances.value == NULL || knnResults.empty() ) return 0;	// the function search wasn't started - or empty database
	if ( this->ActualPage != knnResults.end() ) 
	{
		resultParameter =this->ActualPage->copy();
		return (this->ActualPage++)->size;
	}
	//// start low and high index at the queryMeanIndex ////
  	DWORD low = this->QueryMeanIndex;		// queryMeanIndex is means array index
	DWORD high = this->QueryMeanIndex;
	//// create next k nearest page	////
	multimap<KNN_SEARCH_RESULT_TYPE> searchResult;
	//// !! search the first not used k vectors !! ////
	//// so no flag is needed and no border is used ////
	//// for the search of the k nearest see next while loop ////
	//// this is similar to Step 2 ////
	DWORD newK = 0;

	while ( (low > 0 || high < this->DatabaseSize) && newK < this->K ) 
	{
		if ( low > 0 )
		{
			low--;
			if (distances.dimension[low] != -1) 
			{
				//// calculate hole distance cause in this while loop we have to collect the first next k distances ////
				for (;distances.dimension[low] < this->FeatureDimension; distances.dimension[low]++)
					distances.value[low] += distMeasure(this->Database[low*this->FeatureDimension+distances.dimension[low]] - this->NormalizedQueryVector[distances.dimension[low]]);
				searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distances.value[low],low) );	// insert distance in sorted list
				newK++;
			}
		}
		if ( high < this->DatabaseSize && newK < this->K ) 
		{
			if (distances.dimension[high] != -1) 
			{
					//// calculate hole distance cause in this while loop we have to collect the first next k distances ////
				for (;distances.dimension[high] < this->FeatureDimension; distances.dimension[high]++)
					distances.value[high] += distMeasure(this->Database[high*this->FeatureDimension+distances.dimension[high]] - this->NormalizedQueryVector[distances.dimension[high]]);
				searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distances.value[high],high) );	// insert distance in sorted list
				newK++;
			}
			high++;
		}
	}

	if (searchResult.size() < this->K ) return searchResult.size();	// no neccessary k vectors found
	
	//// start search over the database ////
	double upperDistanceBound = (--searchResult.end())->first;		// ! using variables for faster program execution
	double lowerMeanBound = this->QueryMean - sqrt(upperDistanceBound/this->FeatureDimension);
	double upperMeanBound = this->QueryMean + sqrt(upperDistanceBound/this->FeatureDimension);		// ! using variables for faster program execution
	bool pds;
	bool flag1 = true;
	bool flag2 = true;
	while ( flag1 && flag2 ) 
	{
	// the look at the lower index on the database
		if ( flag1 ) {
		 if ( low > 0 ) {
			low--;
			if (distances.dimension[low] != -1) {
				if ( lowerMeanBound < this->Means[low] &&	this->Means[low] < upperMeanBound ) {
					if ( distances.value[low] < upperDistanceBound ) {
						pds = true;
						for (;distances.dimension[low] < this->FeatureDimension; distances.dimension[low]++) {
							// euclidean distance
							distances.value[low] += distMeasure(this->Database[low*this->FeatureDimension+distances.dimension[low]] - this->NormalizedQueryVector[distances.dimension[low]]);
							if ( distances.value[low] >= upperDistanceBound ) {	
								pds = false;
								distances.dimension[low]++;		// neccessary for the next calculation
								break;
							}
						}
						if (pds) {
							searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distances.value[low],low) );	// insert distance in sorted list
							searchResult.erase( --searchResult.end() );	// delete the last element
							upperDistanceBound = (--searchResult.end())->first;	// new upper bound
							lowerMeanBound = this->QueryMean - sqrt(upperDistanceBound/this->FeatureDimension);	// new lower bound
							upperMeanBound = this->QueryMean + sqrt(upperDistanceBound/this->FeatureDimension); // new upper bound
						}
					}
				} else flag1 = false;	// lower meanBound ...
			}
		 } else flag1 = false;		// low > 0
		}
	// the look at the higher index on the database
		if ( flag2 ) {
		 if ( high < this->DatabaseSize ) {
			if (distances.dimension[high] != -1) {
				if ( lowerMeanBound < this->Means[high] && this->Means[high] < upperMeanBound ) {
					if ( distances.value[high] < upperDistanceBound ) {
						pds = true;
						for (;distances.dimension[high] < this->FeatureDimension; distances.dimension[high]++) {
							// euclidean distance
							distances.value[high] += distMeasure(this->Database[high*this->FeatureDimension+distances.dimension[high]] - this->NormalizedQueryVector[distances.dimension[high]]);
							if ( distances.value[high] >= upperDistanceBound ) {		// !! only check of upperBound necessary, cause the euclidean distance has no negative value
								pds = false;
								distances.dimension[high]++;
								break;
							}
						}
						if (pds) {
							searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(distances.value[high],high) );	// insert distance in sorted list
							searchResult.erase( --searchResult.end() );	// delete the last element
							upperDistanceBound = (--searchResult.end())->first;	// new upper bound
							lowerMeanBound = this->QueryMean - sqrt(upperDistanceBound/this->FeatureDimension);	// new lower bound
							upperMeanBound = this->QueryMean + sqrt(upperDistanceBound/this->FeatureDimension); // new upper bound
						} 
					}
				} else flag2 = false;	// lowerMeanBound ...
			}
			high++;
		 } else flag2 = false;		// high < databaseSize
		}
	} // end of while - the walk through the database

	//// convert searchResult to an array, cause interface definition ////
	//// and mark this k nearest vectors in distance array ////
	KNNRESULTTYPE result;
	result.size = searchResult.size();
	result.indices = new DWORD[result.size];	
	resultParameter = new DWORD[result.size];	
	multimap<KNN_SEARCH_RESULT_TYPE>::iterator sr = searchResult.begin();
	for (DWORD i=0; sr != searchResult.end(); i++ )
	{
		resultParameter[i] = result.indices[i] = sr->second;
		distances.dimension[sr->second] = -1;	//// !! mark the new k vectors
		sr++;
	}

	knnResults.push_back( result );

	return result.size;
}


DWORD EKnnSearch::IEKNNSprevious(DWORD * &resultParameter) {
	if ( this->ActualPage != knnResults.begin() ) {
		this->ActualPage--;
		resultParameter = this->ActualPage->copy();
		return this->ActualPage->size;
	} else return 0;
}

// EKNNSrest only sorts the rest (not allready returned) vectors in the database and return the sorted result //
// and with peek messages (::PeekMessage) for multitasking //
// It's not suitable for time estimation on KNN //
// It's no KNN Search //
DWORD EKnnSearch::IEKNNSrest(DWORD * &resultParameter) {
	if ( distances.value == NULL || knnResults.empty() ) return 0;	// the function search wasn't started - or empty database

	multimap<KNN_SEARCH_RESULT_TYPE> searchResult;

	MSG Mymsg;
    DWORD i;
	double dist;
	for (i=0; i < this->DatabaseSize; i++)
		if ( distances.dimension[i] != -1 ) {
			dist=0;
			for (; distances.dimension[i] < this->FeatureDimension; distances.dimension[i]++) {
				dist += distMeasure( this->Database[i*this->FeatureDimension+distances.dimension[i]] - this->NormalizedQueryVector[distances.dimension[i]]);
				::PeekMessage(&Mymsg,NULL,0,0,PM_REMOVE);
				::TranslateMessage(&Mymsg);
				::DispatchMessage(&Mymsg);
			}
			searchResult.insert( pair<KNN_SEARCH_RESULT_TYPE>(dist,i) );
		}
	
	//// convert searchResult to an array, cause interface definition ////
	//// and mark this k nearest vectors in distance array ////
	KNNRESULTTYPE result;
	result.size = searchResult.size();
	result.indices = new DWORD[result.size];	
	resultParameter = new DWORD[result.size];	
	multimap<KNN_SEARCH_RESULT_TYPE>::iterator sr = searchResult.begin();
	for (i=0; sr != searchResult.end(); i++ )
	{
		resultParameter[i] = result.indices[i] = sr->second;
		distances.dimension[sr->second] = -1;	//// !! mark the found vectors
		sr++;
	}

	knnResults.push_back( result );		// save the result for later use

	return result.size;
}

void EKnnSearch::IEKNNStest( double *database, double *means, DWORD databaseSize, double *queryVector, WORD featureDimension, double queryMean, DWORD k, DWORD pageSize) {
	DWORD *result = NULL;
	DWORD resultCount;
	resultCount = IEKNNS(database,means,databaseSize,queryVector,featureDimension,queryMean,databaseSize/pageSize,result);
	while (resultCount > 0)
		resultCount = IEKNNSnext(result);
}
DWORD EKnnSearch::getIEKNNSresults(DWORD * &result) {
	result = new DWORD[this->DatabaseSize];
	DWORD pos=0;
	for (list<KNNRESULTTYPE>::iterator iter= knnResults.begin(); iter != knnResults.end(); iter++)
		for (DWORD i=0; i < iter->size; i++)
			result[pos++] = iter->indices[i];
	
	return this->DatabaseSize;
}

DWORD EKnnSearch::fullSearch( double *database, DWORD databaseSize, double *normalizedQueryVector, WORD featureDimension, DWORD * &result) {
	//// First step - calculate the squared euclidean distances and create sorted list ////
	multimap<double,DWORD> distances;
	double dist;
	for (DWORD i=0; i < databaseSize; i++) {
		dist=0;
		for (WORD j=0; j < featureDimension; j++)
			dist += distMeasure(database[i*featureDimension+j] - normalizedQueryVector[j]);
		distances.insert(pair<double,DWORD>(dist,i));			//// !!! sorts the distances 
	}

	// Second step - convert list to array
	result =  new DWORD[databaseSize];
	DWORD pos =0;
	for (multimap<double,DWORD>::iterator iter = distances.begin();
		iter != distances.end(); iter++)
			result[pos++] = iter->second;	
	return databaseSize;
}
