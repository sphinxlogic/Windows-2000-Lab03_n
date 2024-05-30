// --formdata.h---------------------------------------------------------------
//
//	Declaration of the CFormData class
//
//	Copyright (C) Microsoft Corporation, 1986-1996. All rights reserved.
//
// ---------------------------------------------------------------------------

#define MAX_STRING          64
#define MAX_DEV_BY          (2*64)
#define MAX_LOCATION        (5*64)
#define MAX_INTRODUCTION    (20*64)

class CFormData
{
public:
	CFormData();
	~CFormData();

	// The form specific data.  These will map to the controls in the form.
	char m_szTopic    [MAX_STRING];
	char m_szToolName [MAX_STRING];
	char m_szToolType [MAX_STRING];
	char m_szPlatform [MAX_STRING];
	char m_szOS       [MAX_STRING];
	char m_szDevelopedBy  [MAX_DEV_BY];
	char m_szLocation     [MAX_LOCATION];
	char m_szIntroduction [MAX_INTRODUCTION];	
};
