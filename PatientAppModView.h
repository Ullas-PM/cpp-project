
// PatientAppModView.h : interface of the CPatientAppModView class
//

#pragma once
#include "Patient.h"
#include "Procedure.h"
#include "Series.h"
#include "Images.h"
#include "PictureControl.h"
#include "PatientAppModDoc.h"

class CPatientAppModView : public CFormView
{
protected: // create from serialization only
	CPatientAppModView() noexcept;
	DECLARE_DYNCREATE(CPatientAppModView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_PATIENTAPPMOD_FORM };
#endif

// Attributes
public:
	CPatientAppModDoc * GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CPatientAppModView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonOpen();


	//// patient object
	//CPatient m_oPatient;
	//
	///// <summary>
	///// Procedure map
	///// </summary>
	//CMap <CString, LPCWSTR, CProcedure*, CProcedure*> m_ProcedureMap;
	///// <summary>
	///// series map
	///// </summary>
	//CMap <CString, LPCWSTR, CSeries*, CSeries*> m_SeriesMap;

	afx_msg void OnDblclkListControl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnTreeAddprocedure();
	afx_msg void OnTreeAddSeries();
	afx_msg void OnTreeAddImage();
	afx_msg void OnUpdateTreeAddSeries(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTreeAddImage(CCmdUI* pCmdUI);
	afx_msg void OnDblclkTreeControl(NMHDR* pNMHDR, LRESULT* pResult);

	// picture control
	CPictureControl m_oPictureCtrl;
	afx_msg void OnBnClickedBtnShare();
};

#ifndef _DEBUG  // debug version in PatientAppModView.cpp
inline CPatientAppModDoc* CPatientAppModView::GetDocument() const
   { return reinterpret_cast<CPatientAppModDoc*>(m_pDocument); }
#endif

