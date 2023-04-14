// PictureControl.cpp : implementation file
//

#include "pch.h"
#include "PatientAppMod.h"
#include "PictureControl.h"


// CPictureControl

IMPLEMENT_DYNAMIC(CPictureControl, CStatic)

/// <summary>
/// default constructor
/// </summary>
CPictureControl::CPictureControl()
{
	m_sImagePath = _T("");
}

/// <summary>
/// Argument constructor
/// </summary>
CPictureControl::CPictureControl(CString& sName)
{
	m_sImagePath = sName;
}
/// <summary>
/// destructor
/// </summary>
CPictureControl::~CPictureControl()
{
}


BEGIN_MESSAGE_MAP(CPictureControl, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()




/// <summary>
/// variable to set the file path
/// </summary>
/// <param name="sName"></param>
void CPictureControl::SetImgPath(CString& sName)
{
	m_sImagePath = sName;
}

void CPictureControl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// image object
	CImage oImage;
	// loading photo
	HRESULT hResult = oImage.Load(m_sImagePath);

	if (FAILED(hResult))
	{
		return;
	}
	// gering client rectangle
	CRect oClientRect;
	GetClientRect(&oClientRect);
	// drawing image
	oImage.Draw(dc, oClientRect);
	
}
