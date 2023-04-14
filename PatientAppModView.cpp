
// PatientAppModView.cpp : implementation of the CPatientAppModView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PatientAppMod.h"
#endif

#include "PatientAppModDoc.h"
#include "PatientAppModView.h"
#include "ProcedureDlg.h"
#include "SeriesDlg.h"
#include "Procedure.h"
#include "Series.h"
#include "Images.h"
#include "ShareDlgThread.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPatientAppModView

IMPLEMENT_DYNCREATE(CPatientAppModView, CFormView)

BEGIN_MESSAGE_MAP(CPatientAppModView, CFormView)
	
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CPatientAppModView::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPatientAppModView::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CPatientAppModView::OnBnClickedButtonOpen)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONTROL, &CPatientAppModView::OnDblclkListControl)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TREE_ADDPROCEDURE, &CPatientAppModView::OnTreeAddprocedure)
	ON_COMMAND(ID_TREE_ADD_SERIES, &CPatientAppModView::OnTreeAddSeries)
	ON_COMMAND(ID_TREE_ADD_IMAGE, &CPatientAppModView::OnTreeAddImage)
	ON_UPDATE_COMMAND_UI(ID_TREE_ADD_SERIES, &CPatientAppModView::OnUpdateTreeAddSeries)
	ON_UPDATE_COMMAND_UI(ID_TREE_ADD_IMAGE, &CPatientAppModView::OnUpdateTreeAddImage)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_CONTROL, &CPatientAppModView::OnDblclkTreeControl)
	ON_BN_CLICKED(IDC_BTN_SHARE, &CPatientAppModView::OnBnClickedBtnShare)
END_MESSAGE_MAP()

// CPatientAppModView construction/destruction

CPatientAppModView::CPatientAppModView() noexcept
	: CFormView(IDD_PATIENTAPPMOD_FORM)
{
	// TODO: add construction code here

}

CPatientAppModView::~CPatientAppModView()
{
}

void CPatientAppModView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_oPictureCtrl);
}

BOOL CPatientAppModView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPatientAppModView::OnInitialUpdate()
{
	// list controls
	CListCtrl* pListCntrl = (CListCtrl*) GetDlgItem(IDC_LIST_CONTROL);

	// inserting colums
	pListCntrl->InsertColumn(0, _T("Name"), LVCFMT_CENTER, 150);
	pListCntrl->InsertColumn(1, _T("MRN"), LVCFMT_CENTER, 180);

	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CPatientAppModView diagnostics

#ifdef _DEBUG
void CPatientAppModView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPatientAppModView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPatientAppModDoc* CPatientAppModView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPatientAppModDoc)));
	return (CPatientAppModDoc*)m_pDocument;
}
#endif //_DEBUG


// CPatientAppModView message handlers

/// <summary>
/// on button click clear
/// </summary>
void CPatientAppModView::OnBnClickedButtonClear()
{
	// resetting all control fields
	SetDlgItemText(IDC_EDIT_FNAME, _T(" "));
	SetDlgItemText(IDC_EDIT_SNAME, _T(" "));
	SetDlgItemText(IDC_EDIT_ADDRESS, _T(" "));
	SetDlgItemText(IDC_EDIT_MRN, _T(" "));
	SetDlgItemText(IDC_EDIT_GENDER, _T(" "));
	SetDlgItemInt(IDC_EDIT_AGE, 0);

	 // use a CDateTimeCtrl pointer to point to combo box item 
	CDateTimeCtrl * pComBox = (CDateTimeCtrl*) GetDlgItem(IDC_EDIT_DOB); // type cast to datetime cntrl we also use dyanmic cast
	// using getCurrent time 
	CTime CurrentTime = CTime::GetCurrentTime();
	CurrentTime.Format("%H:%M");
	// seting currennt time as default
	pComBox->SetTime(&CurrentTime);

	GetDlgItem(IDC_EDIT_OPENDETAILS)->ShowWindow(FALSE);
	GetDlgItem(IDC_OPEN_DETAILS)->ShowWindow(FALSE);

	// clearing list
	CListCtrl* pListCntrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONTROL);
	pListCntrl->DeleteAllItems();

	//clearing tree
	CTreeCtrl* pTreeCntrlClinicalDetails = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
	pTreeCntrlClinicalDetails->DeleteAllItems();

	GetDlgItem(IDC_STATIC_LISTDETAILS)->ShowWindow(FALSE);
	GetDlgItem(IDC_DISPLAYINFO)->ShowWindow(FALSE);

}

/// <summary>
/// on button
/// </summary>
void CPatientAppModView::OnBnClickedButtonSave()
{
	GetDlgItem(IDC_EDIT_OPENDETAILS)->ShowWindow(FALSE);
	GetDlgItem(IDC_OPEN_DETAILS)->ShowWindow(FALSE);

	// varriable to store the first name of the patient
	CString sFirstName = _T(" ");
	GetDlgItemText(IDC_EDIT_FNAME,sFirstName);
	// Variable to store the second name of the patient
	CString sSecondName = _T(" ");
	GetDlgItemText(IDC_EDIT_SNAME, sSecondName);
	// variable to store age of the patient
	int nAge = GetDlgItemInt(IDC_EDIT_AGE);
	// Variable to store the address of patient
	CString sAddress = _T(" ");
	GetDlgItemText(IDC_EDIT_ADDRESS, sAddress);
	// variablee to store the medical record number of patient
	CString sMedRecNum = _T(" ");
	GetDlgItemText(IDC_EDIT_MRN,sMedRecNum);
	// variablee to store the Gender of patient
	CString sGender = _T(" ");
	GetDlgItemText(IDC_EDIT_GENDER, sGender);
	// variablee to store the DOB of patient
	CString sDob = _T(" ");
	GetDlgItemText(IDC_EDIT_DOB, sDob);

	if (sMedRecNum == _T(" ") || sMedRecNum == _T("") )
	{
		MessageBox(_T("Please enter a medical record number to save file !!!"), _T("Cannot save file"), IDOK);
	}
	else
	{
		// list controls
		CListCtrl* pListCntrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONTROL);
		// item to column
		//int nItem = 0;
		//nItem = pListCntrl->InsertItem(0, m_sFirstName + _T(" ") + m_sSecondName);
		pListCntrl->SetItemText( pListCntrl->InsertItem(0, sFirstName + _T(" ") + sSecondName) ,  1 ,  sMedRecNum);
		GetDlgItem(IDC_STATIC_LISTDETAILS)->ShowWindow(TRUE);

		// copy data from form to patient object
		/*m_oPatient.SetFirstName(sFirstName);
		m_oPatient.SetSecondName(sSecondName);
		m_oPatient.SetAge(nAge);
		m_oPatient.SetAddress(sAddress);
		m_oPatient.SetGender(sGender);
		m_oPatient.SetDOB(sDob);
		m_oPatient.SetMRN(sMedRecNum);*/

		CPatient* pPatient = new CPatient(sFirstName, sSecondName, nAge, sAddress, sMedRecNum, sDob, sGender);
		
		//saving the tree data by traversing in the tree
		CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
		// get the root item
		HTREEITEM hRootItem = pClinicalTree->GetRootItem();
		// to strore the series and image item
		HTREEITEM hSeriesItem ;
		HTREEITEM hImageItem ;

		CProcedure * pProcedure = NULL;
		CSeries * pSeries = NULL;
		CImages * pImages = NULL;
		// text value of each item 
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
					// changing the image item to image file name
					hImageItem = pClinicalTree->GetNextSiblingItem(hImageItem);

					pImages->SetImgName(pClinicalTree->GetItemText(hImageItem));
					pSeries->AddImagePath(pImages);
					// changing the image item to next sibling

					hImageItem = pClinicalTree->GetNextSiblingItem(hImageItem);
				}

				// changing to next series sibling
				hSeriesItem = pClinicalTree->GetNextSiblingItem(hSeriesItem);
			}

			// changing to next procedure sibling
			hRootItem = pClinicalTree->GetNextSiblingItem(hRootItem);
		}


		// also save it in the collection of document also as key value pair using cMap
		
		
		GetDocument()->m_MapPatientCollection[sMedRecNum] = pPatient;


		// file name with extenction it will store in the project folder default 
		// if i want to save it in a folder patient in the project folder add the folder name also
		// and we open app by exe it save the file to
		::CreateDirectory(_T("Patient files\\"), NULL);
		CFile oOutFile(_T("Patient files\\") + sMedRecNum + _T(".pat"), CFile::modeCreate | CFile::modeWrite);
		// to specify the working folder
		//_wgetcwd or use get current directory
		/*TCHAR sCurrentDir[MAX_PATH] = { 0 };
		GetCurrentDirectory(MAX_PATH, sCurrentDir);
		oOutFile.SetFilePath(sCurrentDir);*/

		CArchive oAr(&oOutFile, CArchive::store);
		pPatient->Serialize(oAr);
		//m_oPatient.Serialize(oAr);

		oAr.Close();
		oOutFile.Close();
		// saved succesful message
		MessageBox(_T("Saved Successfully "),_T("Patient Data"),MB_OK);
	}

}

// load file worker thread
UINT LoadFileThread(LPVOID pParam)
{
	CMutex oThreadMutex(TRUE, _T("FILELOAD"));
	oThreadMutex.Lock();
	//Creating the File data object to browse through a folder
	WIN32_FIND_DATA oFileData;
	//I want to get all the files with extension .pat - Relative path
	CString sFileToFind = _T("Patient files\\*.pat");
	CString sFilePathName = _T("");
	CString sFileName = _T("");
	// file object pointer
	CFile* pFile = NULL;
	// patient object pointer
	CPatient* pPatient = NULL;
	// shared document pointer retived from pParam
	CPatientAppModDoc* pDoc = (CPatientAppModDoc*)pParam;

	//Find the first file in the Folder with the specified name
	HANDLE oHandle = ::FindFirstFile(sFileToFind, &oFileData);

	do
	{
		//  E:\MyProjects\PACSClientApp\PatientFiles\*.pat - Absolute path

		if (NULL == oHandle) return 0; //LRESULT(); //If no files find with the specified extention

		sFileName = oFileData.cFileName; //cFilename?

		sFilePathName = _T("Patient files\\") + sFileName; //Get the complete file name - Relative Path
		//Create file object
		pFile = new CFile();
		if (!pFile->Open(sFilePathName, CFile::modeRead)) //Open the file for reading 
		{
			//MessageBox( GetDesktopWindow(), _T("Cannot Open the file ") + sFileName + _T(" For writing."));
			return 0;//LRESULT();
		}

		CArchive oArchive(pFile, CArchive::Mode::load);  //Create a Serialize object

		pPatient = NULL;
		pPatient = new CPatient();
		pPatient->Serialize(oArchive);
		//Add object to the Map//Patient name is given as key,and Patient object as value
		CPatientAppModDoc* pDoc = (CPatientAppModDoc*)pParam;
		pDoc->m_MapPatientCollection[pPatient->GetMRN()] = pPatient;

		oArchive.Close();
		pFile->Close();

	} while (FindNextFile(oHandle, &oFileData));

	oThreadMutex.Unlock();

	return 1;
}

/// <summary>
/// on button click open
/// </summary>
void CPatientAppModView::OnBnClickedButtonOpen()
{
	CString sOpenDetials = _T(" ");
	// display hidden windows
	GetDlgItem(IDC_EDIT_OPENDETAILS)->ShowWindow(TRUE);
	GetDlgItem(IDC_OPEN_DETAILS)->ShowWindow(TRUE);

	// Begin the load file thread
	AfxBeginThread(LoadFileThread, GetDocument());

	CMutex oMutex(FALSE/*Ownership*/, _T("FILELOAD")/*Name*/); //creating a named mutex
	// suspend this thread for making sure the mutex is owned by worker thread
	Sleep(3000);
	// wait main thread, so the worker thread is completed working with the named mutex
	DWORD dwResult = WaitForSingleObject(oMutex.m_hObject, INFINITE/*Wait until it completes*/); //signaling

	if (dwResult < 0) return;//failure

	// iterating through CMap in document to add name to list control
	CString sKey = _T(" ");
	CPatient* pPatient = NULL;
	POSITION pos = GetDocument()->m_MapPatientCollection.GetStartPosition();
	while (pos)
	{
		GetDocument()->m_MapPatientCollection.GetNextAssoc(pos, sKey, pPatient);

		// adding to list control
		CListCtrl* pListCntrl = (CListCtrl*)GetDlgItem(IDC_LIST_CONTROL);
		pListCntrl->SetItemText(pListCntrl->InsertItem(0, pPatient->GetFirstName() + _T(" ") + pPatient->GetSecondName()), 1, pPatient->GetMRN());
		GetDlgItem(IDC_STATIC_LISTDETAILS)->ShowWindow(TRUE);

		sOpenDetials += pPatient->GetAllDetails();
		GetDlgItem(IDC_EDIT_OPENDETAILS)->SetWindowText(sOpenDetials);
	}
	

	/*//// filter on opening a file
	//LPCTSTR lpstrFilter = _T("Patient(*.patient) | *.pat");
	//// save as dialouge box
	//CFileDialog oFileDlg(TRUE, _T("Patient"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, lpstrFilter, AfxGetMainWnd());
	//if (oFileDlg.DoModal() == IDOK)
	//{
	//	CFile oInputFile(oFileDlg.GetPathName(), CFile::modeRead);
	//	CArchive oAr(&oInputFile, CArchive::load);
	//	m_oPatient.Serialize(oAr);
	//	oAr.Close();
	//	oInputFile.Close();
	//}
	// copy data to detail
	/*sOpenDetials = m_oPatient.GetAllDetails();
	GetDlgItem(IDC_EDIT_OPENDETAILS)->SetWindowTextW(sOpenDetials);*/

}


// on double click name list item
void CPatientAppModView::OnDblclkListControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CListCtrl* pListCntrl = (CListCtrl * ) GetDlgItem(IDC_LIST_CONTROL);
	int nSelection = pListCntrl->GetSelectionMark();

	if (nSelection < 0) return;

	// get the mrn number from the selected list
	CString sFileNameMRN = pListCntrl->GetItemText(nSelection,1);

	CPatient * pPatient = GetDocument()->m_MapPatientCollection[sFileNameMRN];

	// retive data from collection to edit controls
	SetDlgItemText(IDC_EDIT_ADDRESS, pPatient->GetAddress());
	SetDlgItemText(IDC_EDIT_GENDER, pPatient->GetGender());
	SetDlgItemText(IDC_EDIT_FNAME, pPatient->GetFirstName());
	SetDlgItemText(IDC_EDIT_SNAME, pPatient->GetSecondName());
	SetDlgItemText(IDC_EDIT_MRN, pPatient->GetMRN());
	SetDlgItemInt(IDC_EDIT_AGE, pPatient->GetAge());

	// setting dob to control
	CString sDOB =  pPatient->GetDOB();
	int nDay = _ttoi( sDOB);
	int nMonth = _ttoi( sDOB.Mid(3, 2) );
	int nYear = _ttoi( sDOB.Mid(6, 4) );
	CTime DOB(nYear, nMonth, nDay, 0, 0, 0);
	CDateTimeCtrl* pDOB = (CDateTimeCtrl*)GetDlgItem(IDC_EDIT_DOB);
	pDOB->SetTime(&DOB);


	// // retive data from collection to tree controls
	CTreeCtrl* pTreeCtrl = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
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

		for (size_t nCounter2 = 0; nCounter2 < vSeries.size() ; ++nCounter2)
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
				GetDlgItem(IDC_DISPLAYINFO)->ShowWindow(TRUE);
			}	
		}
	}

	// on double click the item in list show them in edit control
	// 2 ways retivr from stored file or by create a colllection in document which stire the details in primary memory
	//CFile oFile(_T("Patient files\\") + sFileNameMRN + _T(".pat"), CFile::modeRead);
	//CArchive oAr(&oFile, CArchive::load);
	//m_oPatient.Serialize(oAr);
	//oAr.Close();
	//oFile.Close();
	//// seting each control
	//SetDlgItemText(IDC_EDIT_ADDRESS, m_oPatient.GetAddress());
	//SetDlgItemText(IDC_EDIT_GENDER, m_oPatient.GetGender());
	//SetDlgItemText(IDC_EDIT_FNAME, m_oPatient.GetFirstName());
	//SetDlgItemText(IDC_EDIT_SNAME, m_oPatient.GetSecondName());
	//SetDlgItemText(IDC_EDIT_MRN, m_oPatient.GetMRN());
	//SetDlgItemInt(IDC_EDIT_AGE, m_oPatient.GetAge());
	//SetDlgItemText(IDC_EDIT_DOB, m_oPatient.GetDOB());

}

// Context menu on tree control
void CPatientAppModView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	// specifing th
	CTreeCtrl* pClinicalTree = (CTreeCtrl *) GetDlgItem ( IDC_TREE_CONTROL );
	if (pWnd != pClinicalTree)
	{
		return;
	}
	pClinicalTree->ScreenToClient(&point);
	pClinicalTree->ClientToScreen(&point);
	HTREEITEM hItemClicked = pClinicalTree->HitTest(point);
	if (NULL != hItemClicked)
	{
		pClinicalTree->SelectItem(hItemClicked);
	}

	// creating the menu
	CMenu oMainMenu ;
	oMainMenu.LoadMenu(IDR_MENU_CONTEXT);
	// geting the submenu from the context menu 
	CMenu* pSubMenu = oMainMenu.GetSubMenu(0);
	// making the submenu as popup
	pSubMenu->TrackPopupMenu(TPM_CENTERALIGN, point.x, point.y, this);

}
// adding a procedure to tree control
void CPatientAppModView::OnTreeAddprocedure()
{
	// TODO: Add your command handler code here
	CProcedureDlg oProcedurDlg;
	CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
	CString sMultipleProcedures = _T(" ");
	CString sProcedureName = _T(" ");
	bool bIsMultiValue = true;
	int nCommaIndex = 0;
	if (oProcedurDlg.DoModal() == IDOK)
	{
		sMultipleProcedures = oProcedurDlg.GetProcedureName();

		// adding new series
		//CProcedure * pProcedure = new CProcedure();
		//pProcedure->SetProcedureName(oProcedurDlg.m_sProcedureName);
		//// Adding the procedure to the map
		//m_ProcedureMap[oProcedurDlg.m_sProcedureName] = pProcedure;
		//// adding the procedure to the patient
		//m_oPatient.AddProcedure(pProcedure);
		
	}
	while (bIsMultiValue)
	{
		sMultipleProcedures.Trim();
		nCommaIndex = sMultipleProcedures.Find(_T(","));

		if (nCommaIndex == -1)
		{
			if ( sMultipleProcedures == _T("") || sMultipleProcedures == _T(" ") )
			{
				bIsMultiValue = false;
			}
			else
			{
				HTREEITEM hItemPro = pClinicalTree->InsertItem(sMultipleProcedures, TVI_ROOT);
				// settint the procedure item as 1
				pClinicalTree->SetItemData(hItemPro, 1);
				bIsMultiValue = false;
			}
		}
		else
		{
			sProcedureName = sMultipleProcedures.Mid(0, nCommaIndex);
			sProcedureName.Trim();

			if (sProcedureName == _T("") || sProcedureName == _T(" ") )
			{
				bIsMultiValue = false;
			}

			HTREEITEM hItemPro = pClinicalTree->InsertItem(sProcedureName, TVI_ROOT);
			// settint the procedure item as 1
			pClinicalTree->SetItemData(hItemPro, 1);
			sMultipleProcedures = sMultipleProcedures.Mid(nCommaIndex + 1);

		}

	}

}
// adding a series to a procedure
void CPatientAppModView::OnTreeAddSeries()
{
	CSeriesDlg oSeriesDlg;
	// getting  selecting item details from tree
	CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
	HTREEITEM hItemSelected = pClinicalTree -> GetSelectedItem();
	// if no item selected
	if (hItemSelected == NULL ) return;

	CString sMultipleSeries = _T(" ");
	CString sSeriesName = _T(" ");
	bool bIsMultiValue = true;
	int nCommaIndex = 0;

	if (oSeriesDlg.DoModal() == IDOK)
	{
		sMultipleSeries = oSeriesDlg.GetSeriesName();
		/*//// adding a series
		//CSeries * pSeries = new CSeries();
		//pSeries->SetSeriesName(oSeriesDlg.m_sSeriesName);

		//// adding the series with the correct procedure
		//m_ProcedureMap[sProcedureName]->AddSeries(pSeries);

		//// adding the new series to the series map
		//m_SeriesMap[oSeriesDlg.m_sSeriesName] = pSeries;*/
	}
	while (bIsMultiValue)
	{
		sMultipleSeries.Trim();
		nCommaIndex = sMultipleSeries.Find(_T(","));

		if (nCommaIndex == -1)
		{
			if (sMultipleSeries == _T("") || sMultipleSeries == _T(" "))
			{
				bIsMultiValue = false;
			}
			else
			{
				// adding series to the selected item tree procedure
				HTREEITEM hItemSeries = pClinicalTree->InsertItem(sMultipleSeries, hItemSelected);
				// setting the series item as 2
				pClinicalTree->SetItemData(hItemSeries, 2);
				bIsMultiValue = false;
			}
		}
		else
		{
			sSeriesName = sMultipleSeries.Mid(0, nCommaIndex);
			sSeriesName.Trim();

			if (sSeriesName == _T("") || sSeriesName == _T(" "))
			{
				bIsMultiValue = false;
			}

			HTREEITEM hItemSeries = pClinicalTree->InsertItem(sSeriesName, hItemSelected);
			// setting the series item as 2
			pClinicalTree->SetItemData(hItemSeries, 2);
			sMultipleSeries = sMultipleSeries.Mid(nCommaIndex + 1);

		}

	}

}
// for disabling add series when series and image is selected
void CPatientAppModView::OnUpdateTreeAddSeries(CCmdUI* pCmdUI)
{
	CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
	HTREEITEM hItem = pClinicalTree-> GetSelectedItem();

	if (hItem == NULL) return;

	// making add series only enable when selected item is a procedure item
	if ( pClinicalTree -> GetItemData(hItem) == 1 )
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}
// addd a tree item to a series
void CPatientAppModView::OnTreeAddImage()
{
	CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
	// filter for .jpg and .png
	LPCTSTR lpstrFilter = _T( "JPEG(*.jpg) | *.jpg");

	//// save as dialouge box
	CFileDialog oOpenFileDlg(TRUE, _T("JPEG"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, lpstrFilter, AfxGetMainWnd());

	HTREEITEM hItemSelected = pClinicalTree->GetSelectedItem();
	// return when no item selected
	if (hItemSelected == NULL) return;

	//CString sSeriesName = pClinicalTree->GetItemText(hItemSelected);

	if (oOpenFileDlg.DoModal() == IDOK)
	{
		HTREEITEM hItemImage = ((CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL))->InsertItem(oOpenFileDlg.GetPathName(),hItemSelected);
		pClinicalTree->InsertItem(_T("File Name : ") + oOpenFileDlg.GetFileName(), hItemSelected);
		pClinicalTree->SetItemData(hItemImage, 3);

		//// adding new imagepath
		//   CImages * pImages = new CImages();
		//pImages->SetImgPath(_T("File Path : ") + oOpenFileDlg.GetPathName());
		//pImages->SetImgName(_T("File name : ") + oOpenFileDlg.GetFileName());

		//// adding the image path to correct Series item 
		//m_SeriesMap[sSeriesName]->AddImagePath(pImages);
		
	}
	GetDlgItem(IDC_DISPLAYINFO)->ShowWindow(TRUE);
}
// for disabling add image when image procedure is selected
void CPatientAppModView::OnUpdateTreeAddImage(CCmdUI* pCmdUI)
{
	CTreeCtrl* pTreeCntrl = (CTreeCtrl *) GetDlgItem(IDC_TREE_CONTROL);
	HTREEITEM hItem = ((CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL))->GetSelectedItem();
	if (hItem == NULL) return;
	// making add image only enable when selected item is a series item
	//DWORD_PTR nData = pTreeCntrl->GetItemData(hItem);
	if (pTreeCntrl->GetItemData(hItem) == 1)
	{
		pCmdUI->Enable(FALSE);
	}
	else if (pTreeCntrl->GetItemData(hItem) == 3)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

// on double click image item in the tree control
void CPatientAppModView::OnDblclkTreeControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CTreeCtrl * pClinicalTree = (CTreeCtrl*) GetDlgItem (IDC_TREE_CONTROL) ;

	HTREEITEM hSelectedItem = pClinicalTree->GetSelectedItem();

	CString sFilePath = pClinicalTree->GetItemText(hSelectedItem);
	// show the image
	if (pClinicalTree->GetItemData(hSelectedItem) != 3)
	{
		return;
	}
	m_oPictureCtrl.SetImgPath(sFilePath);
	Invalidate();
}

// ui thread showing the share dlg 
void CPatientAppModView::OnBnClickedBtnShare()
{
	CShareDlgThread * pThread = new CShareDlgThread();
	
	CString sFirstName = _T(" ");
	GetDlgItemText(IDC_EDIT_FNAME, sFirstName);
	CString sSecondName = _T(" ");
	GetDlgItemText(IDC_EDIT_SNAME, sSecondName);
	int nAge = GetDlgItemInt(IDC_EDIT_AGE);
	CString sAddress = _T(" ");
	GetDlgItemText(IDC_EDIT_ADDRESS, sAddress);
	CString sMedRecNum = _T(" ");
	GetDlgItemText(IDC_EDIT_MRN, sMedRecNum);
	CString sGender = _T(" ");
	GetDlgItemText(IDC_EDIT_GENDER, sGender);
	CString sDob = _T(" ");
	GetDlgItemText(IDC_EDIT_DOB, sDob);
	CPatient* pPatient = new CPatient(sFirstName, sSecondName, nAge, sAddress, sMedRecNum, sDob, sGender);
	CTreeCtrl* pClinicalTree = (CTreeCtrl*)GetDlgItem(IDC_TREE_CONTROL);
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
				// changing the image item to image file name
				hImageItem = pClinicalTree->GetNextSiblingItem(hImageItem);
				pImages->SetImgName(pClinicalTree->GetItemText(hImageItem));
				pSeries->AddImagePath(pImages);
				hImageItem = pClinicalTree->GetNextSiblingItem(hImageItem);
			}
			hSeriesItem = pClinicalTree->GetNextSiblingItem(hSeriesItem);
		}
		hRootItem = pClinicalTree->GetNextSiblingItem(hRootItem);
	}

	pThread->SetPatient(pPatient);
	pThread->CreateThread();
}
