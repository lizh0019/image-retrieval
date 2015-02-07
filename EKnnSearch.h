// EKnnSearch.h: interface for the EKnnSearch class.
//
//////////////////////////////////////////////////////////////////////

#ifndef EKNNSEARCH_H
#define EKNNSEARCH_H

#if _MSC_VER > 1000
#pragma once
#endif

#include <string>
#include <stdio.h>
#include <map>				// neccessary for multimap - an ordered associative container
#include <list>				// neccessary for knnResult list
#include <math.h>			// neccessary for the pow in euclidean distance calculation

using namespace std;
#define KNN_SEARCH_RESULT_TYPE double,DWORD
#define KNN_MEAN_MAP_TYPE double,DWORD

typedef struct tagDistanceType
{
  double *value;
  INT64 *dimension;
}DISTANCE, *PDISTANCE, FAR *LPDISTANCE;	 // cache of distances - using mean indexes	

typedef struct tagKnnResultType
{						// only used for iterative EKNNS (IEKNNS)
  DWORD* indices;
  DWORD size;
  DWORD* copy()
  {
	DWORD* tmp = new DWORD[size];
	for (DWORD i=0; i < size; i++)
		tmp[i] = indices[i];
	return tmp;
  }
}KNNRESULTTYPE, *PKNNRESULTTYPE, FAR *LPKNNRESULTTYPE;
	
class EKnnSearch
{
public:
	EKnnSearch();
	~EKnnSearch();

	// for testing - use this function for finding only the k nearest vectors //
	DWORD EKNNS(double *database, double *means, DWORD databaseSize, double *queryVector, WORD featureDimension, double queryMean, DWORD k, DWORD * &result);

	// start a new knn search - initialization
	// return the count of found nearest k vectors ,
	// and return the indexes of the nearest k vectors in parameter result
	DWORD IEKNNS(double *database, double *means, DWORD databaseSize, double *queryVector, WORD featureDimension, double queryMean, DWORD k, DWORD * &result);

	// get next page - return 0 if this object is not initialized with search
	DWORD IEKNNSnext(DWORD * &result);	
	// get previous page - return NULL if no previous page exists
	DWORD IEKNNSprevious(DWORD * &result);

	// with peek messages //
	DWORD IEKNNSrest(DWORD * &result);

	// for time tests - without peek message //
	// search over the hole database using IEKNNSnext with k=databaseSize/pageSize
	void IEKNNStest( double *database, double *means, DWORD databaseSize, double *queryVector, WORD featureDimension, double queryMean, DWORD k, DWORD pageSize);
	// the corresponding results of IEKNNStest execution //
	DWORD getIEKNNSresults (DWORD * &result);
	// full search of the nearest vectors in the database - usefull for comparison in the tests //
	DWORD fullSearch( double *database, DWORD databaseSize, double *queryVector, WORD featureDimension, DWORD * &result);
	
	DISTANCE distances;								// cache of distances - using mean indexes	

protected:
	// distance measurement method 
	double distMeasure(double a);
	list<KNNRESULTTYPE> knnResults;				// list of pages 
	list<KNNRESULTTYPE>::iterator ActualPage;	// pointer to the actual page
	double *Database;				// database pointer - initiated by function search
	double *Means;// means pointer
	DWORD DatabaseSize;							// corresponding size of the databaseSize
	WORD FeatureDimension;						// feature dimension
	double *NormalizedQueryVector;				// for faster memory access
	double QueryMean;							// the actual mean value of the query
	DWORD QueryMeanIndex;						// the corresponding index to the vector
												// initiated in function search
	DWORD K;									// the K value for KNN Search - initiated by search
};


#endif // EKNNSEARCH_H