// --formdata.cpp-------------------------------------------------------------
//
//   Implementation of the CFormData class
//
// Copyright (C) Microsoft Corp. 1986-1996.  All Rights Reserved.
// ---------------------------------------------------------------------------

#include "stdafx.h"
#include "formdata.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

//$--CFormData::CFormData-----------------------------------------------------
//
//	Purpose:
//		This is the constructor for the CFormData class.  This will set all the
//	    default values for the form.
//
// ---------------------------------------------------------------------------
CFormData::CFormData()
{	
	ZeroMemory(&m_szTopic, sizeof(m_szTopic));
	ZeroMemory(&m_szToolName,  sizeof(m_szToolName));
	ZeroMemory(&m_szToolType, sizeof(m_szToolType));
	ZeroMemory(&m_szPlatform, sizeof(m_szPlatform));
	ZeroMemory(&m_szOS, sizeof(m_szOS));
	ZeroMemory(&m_szDevelopedBy, sizeof(m_szDevelopedBy));
	ZeroMemory(&m_szLocation, sizeof(m_szLocation));
	ZeroMemory(&m_szIntroduction, sizeof(m_szIntroduction));
} 

//$--CFormData::~CFormData----------------------------------------------------
//
//	Purpose:
//		This is the destructor for the CFormData class.  This will be useful to
//	    deallocate any allocated memory.
//
// ---------------------------------------------------------------------------
CFormData::~CFormData()
{
} 
