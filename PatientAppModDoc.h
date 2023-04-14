
// PatientAppModDoc.h : interface of the CPatientAppModDoc class
//


#pragma once
#include "Patient.h"
class CPatient;
class CPatientAppModDoc : public CDocument
{
protected: // create from serialization only
	CPatientAppModDoc() noexcept;
	DECLARE_DYNCREATE(CPatientAppModDoc)

// Attributes
public:
	// map collection to store patient details
	CMap <CString, LPCWSTR , CPatient*, CPatient*> m_MapPatientCollection;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPatientAppModDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
