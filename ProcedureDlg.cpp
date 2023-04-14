// ProcedureDlg.cpp : implementation file
//

#include "pch.h"
#include "PatientAppMod.h"
#include "afxdialogex.h"
#include "ProcedureDlg.h"


// CProcedureDlg dialog

IMPLEMENT_DYNAMIC(CProcedureDlg, CDialog)

CProcedureDlg::CProcedureDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PROCEDURE_DLG, pParent)
	, m_sProcedureName()
{

}

CProcedureDlg::~CProcedureDlg()
{
}

void CProcedureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROCEDURENAME, m_sProcedureName);
}

/// <summary>
/// function returns the procedure name
/// </summary>
/// <returns></returns>
CString CProcedureDlg::GetProcedureName()
{
	
	return m_sProcedureName;
}


BEGIN_MESSAGE_MAP(CProcedureDlg, CDialog)
END_MESSAGE_MAP()


// CProcedureDlg message handlers





