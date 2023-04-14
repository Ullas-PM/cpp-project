
// PatientAppMod.h : main header file for the PatientAppMod application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPatientAppModApp:
// See PatientAppMod.cpp for the implementation of this class
//

class CPatientAppModApp : public CWinApp
{
public:
	CPatientAppModApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPatientAppModApp theApp;
