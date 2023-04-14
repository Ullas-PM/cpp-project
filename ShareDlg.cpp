// ShareDlg.cpp : implementation file
//

#include "pch.h"
#include "PatientAppMod.h"
#include "afxdialogex.h"
#include "ShareDlg.h"
#include <vector>

// CShareDlg dialog

IMPLEMENT_DYNAMIC(CShareDlg, CDialogEx)

CShareDlg::CShareDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAREDLG, pParent)
{

}

CShareDlg::~CShareDlg()
{
}

void CShareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHAREIMAGE, m_oPictureControl);
}


BEGIN_MESSAGE_MAP(CShareDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SHARECLINICALDETAILS, &CShareDlg::OnBnClickedButtonShareclinicaldetails)
	ON_BN_CLICKED(IDC_BUTTON_SHAREIMAGE, &CShareDlg::OnBnClickedButtonShareimage)
	ON_NOTIFY(NM_DBLCLK, IDC_SHARECLINICALTREE, &CShareDlg::OnDblclkShareclinicaltree)
END_MESSAGE_MAP()


// CShareDlg message handlers

/// <summary>
/// On button click Share clinical details
/// </summary>
void CShareDlg::OnBnClickedButtonShareclinicaldetails()
{
	// TODO: Add your control notification handler code here
	CString sIP = _T("127.0.0.1");
	GetDlgItemText(IDC_EDIT_SERVERIP, sIP);
	int nPortNumber = 8520;
	GetDlgItemInt(IDC_EDIT_SERVERPORTNUMBER);
	int nConnectionResult = 0;

	if (m_pCommunicationSocket == NULL)
	{
		m_pCommunicationSocket = new CCommunicationSocket();
		m_pCommunicationSocket->CreateCommunicationSocket();
		nConnectionResult = m_pCommunicationSocket->ConnectToServer(sIP, nPortNumber);
	}


	if (nConnectionResult)
	{
		AfxMessageBox(_T("Connection Successfull"));
		
		CString sDataToSend = _T(" ");

		CPatient* pPatient = GetClinicalDetails();
		CString sAge;
		sAge.Format(_T("%d"), pPatient->GetAge());
		sDataToSend += pPatient->GetFirstName() + _T(",") + pPatient->GetSecondName() + _T(",")+sAge+ _T(",")+pPatient->GetDOB()+ _T(",")+pPatient->GetAddress()+ _T(",");
		sDataToSend += pPatient->GetGender() + _T(",") + pPatient->GetMRN();
		
		// sending clinical details
		std::vector<CProcedure*> vProcedures = pPatient->GetProcedureVector();
		for (size_t nCounter1 = 0; nCounter1 < vProcedures.size(); ++nCounter1)
		{
			
			sDataToSend += _T(",PRO") + vProcedures[nCounter1] -> GetProcedureName();
			
			std::vector<CSeries*> vSeries = vProcedures[nCounter1]->GetSeriesVector();
			for (size_t nCounter2 = 0; nCounter2 < vSeries.size(); ++nCounter2)
			{
				sDataToSend += _T(",SER")+ vSeries[nCounter2]->GetSeriesName();
				std::vector<CImages*> vImages = vSeries[nCounter2]->GetImagePathVector();
				for (size_t nCounter3 = 0; nCounter3 < vImages.size(); ++nCounter3)
				{
					sDataToSend += _T(",IMG") + vImages[nCounter3]->GetImgPath()+ _T(",NME")+vImages[nCounter3]->GetImgName();
				
				}
			}
		}

		int nCount = sDataToSend.GetLength();
		char* StrToSend = new char(nCount);
		strcpy( StrToSend, CStringA( sDataToSend ).GetString( ) );
		int nSendResult = m_pCommunicationSocket->Send(StrToSend, nCount);
		//int nSendResult = m_pCommunicationSocket->Send(sDataToSend.GetBuffer(sDataToSend.GetLength()), sDataToSend.GetLength());

		if (!nSendResult)
		{
			AfxMessageBox(_T("Message sending failed"));
		}

	}
	else
	{
		AfxMessageBox(_T("Connection Failed"));
	}

}

/// <summary>
/// on button click share image
/// </summary>
void CShareDlg::OnBnClickedButtonShareimage()
{
	// TODO: Add your control notification handler code here
	CString sIP = _T("127.0.0.1");
	GetDlgItemText(IDC_EDIT_SERVERIP, sIP);
	int nPortNumber = 8520;
	GetDlgItemInt(IDC_EDIT_SERVERPORTNUMBER);
	int nConnectionResult = 0;
	if (m_pCommunicationSocket == NULL)
	{
		m_pCommunicationSocket = new CCommunicationSocket();
		m_pCommunicationSocket->CreateCommunicationSocket();
		nConnectionResult = m_pCommunicationSocket->ConnectToServer(sIP, nPortNumber);
	}
	
	CString sImage = _T("");

	CString DataToSend = _T("#PIC") + sImage;

	if (nConnectionResult)
	{
		AfxMessageBox(_T("Connection Successfull"));

		//send Image

		//CBitMap oImageBitMap;
	}
	else
	{
		AfxMessageBox(_T("Connection Failed"));
	}
}

/// <summary>
/// set clinical details of patient
/// </summary>
/// <param name="pPatient"></param>
void CShareDlg::SetClinicalDetails(CPatient* pPatient)
{
	SetDlgItemText(IDC_EDIT_SHAREFNAME, pPatient->GetFirstName());
	SetDlgItemText(IDC_EDIT_SHARESNAME, pPatient->GetSecondName());
	SetDlgItemText(IDC_EDIT_SHAREADDRESS, pPatient->GetAddress());
	SetDlgItemText(IDC_EDIT_SHAREGENDER, pPatient->GetGender());
	SetDlgItemText(IDC_EDIT_SHAREMRN, pPatient->GetMRN());
	SetDlgItemInt(IDC_EDIT_SHAREAGE, pPatient->GetAge());

	CString sDOB = pPatient->GetDOB();
	int nDay = _ttoi(sDOB);
	int nMonth = _ttoi(sDOB.Mid(3, 2));
	int nYear = _ttoi(sDOB.Mid(6, 4));
	CTime DOB(nYear, nMonth, nDay, 0, 0, 0);
	CDateTimeCtrl* pDOB = (CDateTimeCtrl*)GetDlgItem(IDC_EDIT_SHAREDOB);
	pDOB->SetTime(&DOB);

	// // retive data from collection to tree controls
	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)GetDlgItem(IDC_SHARECLINICALTREE);
	// delete all previous details
	pTreeCtrl->DeleteAllItems();
	//travesring in procedure vector
	std::vector<CProcedure*> vProcedures = pPatient->GetProcedureVector();

	for (size_t nCounter1 = 0; nCounter1 < vProcedures.size(); ++nCounter1)
	{
		HTREEITEM hItemPro = pTreeCtrl->InsertItem(vProcedures[nCounter1]->GetProcedureName(), TVI_ROOT);
		pTreeCtrl->SetItemData(hItemPro, 1);
		//travesring in series vector
		std::vector<CSeries*> vSeries = vProcedures[nCounter1]->GetSeriesVector();

		for (size_t nCounter2 = 0; nCounter2 < vSeries.size(); ++nCounter2)
		{
			HTREEITEM hItemSeries = pTreeCtrl->InsertItem(vSeries[nCounter2]->GetSeriesName(), hItemPro);
			pTreeCtrl->SetItemData(hItemSeries, 2);
			//travesring in imagepath vector
			std::vector<CImages*> vImages = vSeries[nCounter2]->GetImagePathVector();
			for (size_t nCounter3 = 0; nCounter3 < vImages.size(); ++nCounter3)
			{
				HTREEITEM hItemImg = pTreeCtrl->InsertItem(vImages[nCounter3]->GetImgPath(), hItemSeries);
				pTreeCtrl->InsertItem(vImages[nCounter3]->GetImgName(), hItemSeries);
				pTreeCtrl->SetItemData(hItemImg, 3);
				GetDlgItem(IDC_STATIC_PICINFO)->ShowWindow(SW_SHOW);
			}

		}

	}

}

/// <summary>
/// Get Details of the patient
/// </summary>
/// <returns> patient pointer</returns>
CPatient * CShareDlg::GetClinicalDetails()
{
	CString sFirstName = _T(" ");
	CString sSecondName = _T(" ");
	CString sAddress = _T(" ");
	CString sMedRecNum = _T(" ");
	CString sGender = _T(" ");
	CString sDob = _T(" ");
	GetDlgItemText(IDC_EDIT_SHAREFNAME, sFirstName);
	GetDlgItemText(IDC_EDIT_SHARESNAME, sSecondName);
	GetDlgItemText(IDC_EDIT_SHAREADDRESS, sAddress);
	GetDlgItemText(IDC_EDIT_SHAREGENDER, sGender);
	GetDlgItemText(IDC_EDIT_SHAREMRN, sMedRecNum);
	int nAge = GetDlgItemInt(IDC_EDIT_SHAREAGE);
	GetDlgItemText(IDC_EDIT_SHAREDOB, sDob);

	CPatient* pPatient = new CPatient(sFirstName, sSecondName, nAge, sAddress, sMedRecNum, sDob, sGender);

	CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_SHARECLINICALTREE);
	HTREEITEM hRootItem = pClinicalTree->GetRootItem();
	HTREEITEM hSeriesItem;
	HTREEITEM hImageItem;

	CProcedure* pProcedure = NULL;
	CSeries* pSeries = NULL;
	CImages* pImages = NULL;

	CString sValue = _T("");

	// loooping in procedures
	while (NULL != hRootItem)
	{
		sValue = pClinicalTree->GetItemText(hRootItem);
		pProcedure = new CProcedure(sValue);
		pPatient->AddProcedure(pProcedure);
		// looping through series
		hSeriesItem = pClinicalTree->GetChildItem(hRootItem);
		while (NULL != hSeriesItem)
		{
			sValue = pClinicalTree->GetItemText(hSeriesItem);
			pSeries = new CSeries(sValue);
			pProcedure->AddSeries(pSeries);
			//looping in image
			hImageItem = pClinicalTree->GetChildItem(hSeriesItem);
			while (NULL != hImageItem)
			{
				sValue = pClinicalTree->GetItemText(hImageItem);
				pImages = new CImages(sValue);
				hImageItem = pClinicalTree->GetNextSiblingItem(hImageItem);
				pImages->SetImgName(pClinicalTree->GetItemText(hImageItem));
				pSeries->AddImagePath(pImages);
				hImageItem = pClinicalTree->GetNextSiblingItem(hImageItem);
			}
			hSeriesItem = pClinicalTree->GetNextSiblingItem(hSeriesItem);
		}
		hRootItem = pClinicalTree->GetNextSiblingItem(hRootItem);
	}

	return pPatient;
}


// dIsplay image on doubleclick image path
void CShareDlg::OnDblclkShareclinicaltree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)GetDlgItem(IDC_SHARECLINICALTREE);

	HTREEITEM hSelection = pTreeCtrl->GetSelectedItem();
	CString sFilePath = pTreeCtrl->GetItemText(hSelection);
	// show the image
	if (pTreeCtrl->GetItemData(hSelection) != 3)
	{
		return;
	}

	m_oPictureControl.SetImgPath(sFilePath);

	Invalidate();


}
