#pragma once
#include "afxdialogex.h"


// CProcedureDlg dialog

class CProcedureDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcedureDlg)

public:
	CProcedureDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProcedureDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCEDURE_DLG };
#endif

protected:

	// variable to store the procedure name
	CString m_sProcedureName = _T("");

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// function returns the procedure name
	/// </summary>
	/// <returns></returns>
	CString GetProcedureName();
	
};
