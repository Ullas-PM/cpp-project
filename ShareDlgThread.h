#pragma once
#include "ShareDlg.h"


// CShareDlgThread

class CShareDlgThread : public CWinThread
{
	DECLARE_DYNCREATE(CShareDlgThread)

public:
	/// <summary>
	/// default constructor
	/// </summary>
	CShareDlgThread(); 
	// protected constructor used by dynamic creation
	virtual ~CShareDlgThread();

	/// <summary>
	/// initialise function of share dlg
	/// </summary>
	/// <param name="pPatient"></param>
	/// <returns></returns>
	virtual BOOL InitInstance();



	virtual int ExitInstance();

protected:

	/// <summary>
	/// CPatient object pointer
	/// </summary>
	CPatient * m_pPatient = NULL;

	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// function to set the m_pPatient
	/// </summary>
	/// <param name="pPatient"></param>
	void SetPatient(CPatient * pPatient);
};


