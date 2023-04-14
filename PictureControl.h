#pragma once


// CPictureControl

class CPictureControl : public CStatic
{
	DECLARE_DYNAMIC(CPictureControl)
private:
	/// <summary>
	/// variable to store the path name of image file
	/// </summary>
	CString m_sImagePath = _T("");

public:
	/// <summary>
	/// default constructor
	/// </summary>
	CPictureControl();
	/// <summary>
	/// Argument constructor
	/// </summary>
	CPictureControl(CString& sName);
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CPictureControl();

	/// <summary>
	/// variable to set the file path
	/// </summary>
	/// <param name="sName"></param>
	void SetImgPath(CString& sName);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


