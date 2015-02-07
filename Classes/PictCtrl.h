////////////////////////////////////////////////////////////////
// MSDN Magazine -- October 2001
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0 for Windows 98 and probably Windows 2000 too.
// Set tabsize = 3 in your editor.
//
#include "picture.h"
#include "StatLink.h"
#pragma once

//////////////////
// Class to encapsulate IPicture. This does not wrap all IPicture methods,
// only the ones I needed to implement ImgView -- feel free to add the others
// yourself.
//
class CPictureCtrl : public CStaticLink {
public:
	CString GetImagePathName();
	void DisEnableDisplay();

	CPictureCtrl(BOOL bAutoLoadImage=TRUE);
	~CPictureCtrl();

	// brainless wrappers call CPicture
	BOOL LoadImage(UINT nIDRes) {
		Invalidate();
		return m_pict.Load(nIDRes);
	}
	BOOL LoadImage(LPCTSTR pszPathName) {
		
		if(m_pict.Load(pszPathName))
		{   m_bGetRect=false;
			m_bPaint=true;
			m_sImagePathName.Empty();
			m_sImagePathName=pszPathName;
			Invalidate();
			return true;
		}
		else 
		{
			m_sImagePathName="";
			return false;
		}
	}
	BOOL LoadImage(CArchive& ar) {
		if(m_pict.Load(ar))
		{
			 m_bGetRect=false;
			 Invalidate();
			 return true;
		}
		else
			 return false;
	}
	BOOL LoadImage(IStream* pstm) {
		if(m_pict.Load(pstm))
		{
			 m_bGetRect=false;
			 Invalidate();
			 return true;
		}
		else
			 return false;
	}

	CSize GetImageSize() {
		return m_pict.GetImageSize();
	}

	const CPicture* GetPicture() {
		return &m_pict;
	}

protected:
	CRect m_RightRect;
	CString m_sImagePathName;
	CPicture m_pict;			// picture
	BOOL m_bAutoLoadImage;	// automatically load image w/same Ctrl ID
	int SuitableWidth(int Width, int Heigth, int DisplayWidth, int DisplayHeigth);
	int SuitableHeight(int Width, int Heigth, int DisplayWidth, int DisplayHeigth);
	virtual void PreSubclassWindow();

	// message handlers
	afx_msg void OnPaint();
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_DYNAMIC(CPictureCtrl)
	DECLARE_MESSAGE_MAP()
private:
	bool m_bGetRect;
	bool m_bPaint;
	CRect GetRightRect();  //get the suitable rect for dis
};
