#pragma once
#include "afxdialogex.h"


// CSeriesDlg dialog

class CSeriesDlg : public CDialog
{
	DECLARE_DYNAMIC(CSeriesDlg)

public:
	CSeriesDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSeriesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SERIES };
#endif

protected:
	// variable to store the name of series
	CString m_sSeriesName;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	

public:
	/// <summary>
	/// function return series name
	/// </summary>
	/// <returns></returns>
	CString GetSeriesName();
	
};
