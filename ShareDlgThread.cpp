// ShareDlgThread.cpp : implementation file
//

#include "pch.h"
#include "PatientAppMod.h"
#include "ShareDlgThread.h"
#include "PatientAppModView.h"
#include "Patient.h"
// CShareDlgThread

IMPLEMENT_DYNCREATE(CShareDlgThread, CWinThread)

CShareDlgThread::CShareDlgThread()
{
}

CShareDlgThread::~CShareDlgThread()
{
}

BOOL CShareDlgThread::InitInstance()
{
	
	CShareDlg * pShareDlg = new CShareDlg();
	m_pMainWnd = pShareDlg;
	pShareDlg->Create(IDD_SHAREDLG);
	pShareDlg->SetClinicalDetails(m_pPatient);
	pShareDlg->ShowWindow(SW_SHOW);

	return TRUE;
}

int CShareDlgThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here

	return CWinThread::ExitInstance();
}

void CShareDlgThread::SetPatient(CPatient* pPatient)
{
	m_pPatient = pPatient;
}

BEGIN_MESSAGE_MAP(CShareDlgThread, CWinThread)
END_MESSAGE_MAP()


// CShareDlgThread message handlers

/// <summary>




