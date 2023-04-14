#pragma once
#include "afxdialogex.h"
#include "Patient.h"
#include "PictureControl.h"
#include "Procedure.h"
#include "Series.h"
#include "Images.h"
#include "CommunicationSocket.h"

// CShareDlg dialog

class CShareDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShareDlg)

public:
	CShareDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CShareDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAREDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	/// <summary>
	/// On button click Share clinical details
	/// </summary>
	afx_msg void OnBnClickedButtonShareclinicaldetails();
	/// <summary>
	/// on button click share image
	/// </summary>
	afx_msg void OnBnClickedButtonShareimage();
	
protected:
	// control of picture
	CPictureControl m_oPictureControl;

	// client socket for communication between processes
	CCommunicationSocket * m_pCommunicationSocket = NULL;

public:
	
	/// <summary>
	/// set clinical details of patient
	/// </summary>
	/// <param name="pPatient"></param>
	void SetClinicalDetails(CPatient* pPatient);
	
	/// <summary>
	/// Get Details of the patient
	/// </summary>
	/// <returns> patient pointer</returns>
	CPatient* GetClinicalDetails();

	/// <summary>
	/// On double click image item in tree
	/// </summary>
	/// <param name="pNMHDR"></param>
	/// <param name="pResult"></param>
	afx_msg void OnDblclkShareclinicaltree(NMHDR* pNMHDR, LRESULT* pResult);

};
