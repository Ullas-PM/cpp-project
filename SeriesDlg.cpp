// SeriesDlg.cpp : implementation file
//

#include "pch.h"
#include "PatientAppMod.h"
#include "afxdialogex.h"
#include "SeriesDlg.h"


// CSeriesDlg dialog

IMPLEMENT_DYNAMIC(CSeriesDlg, CDialog)

CSeriesDlg::CSeriesDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_SERIES, pParent)
	, m_sSeriesName(_T(""))
{

}

CSeriesDlg::~CSeriesDlg()
{
}

void CSeriesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERIESNAME, m_sSeriesName);
}





BEGIN_MESSAGE_MAP(CSeriesDlg, CDialog)
END_MESSAGE_MAP()


// CSeriesDlg message handlers

	/// <summary>
	/// function return series name
	/// </summary>
	/// <returns></returns>
CString CSeriesDlg::GetSeriesName()
{
	return m_sSeriesName;
}