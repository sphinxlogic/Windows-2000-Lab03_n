/************************************************************************
*                                                                       *
*   $$Root$$MAPIApp.h												*
*                                                                       *
*   Copyright 1998, Microsoft Corp. All rights reserved.				*
*                                                                       *
************************************************************************/


#ifndef $$ROOT$$_MAPIAPP_H
#define $$ROOT$$_MAPIAPP_H
#pragma once

#include "stdafx.h"


class C$$Root$$MAPIApp  
{
public:
	C$$Root$$MAPIApp();
	virtual ~C$$Root$$MAPIApp();
	HRESULT Status(){return m_hConstructorResult;};
	LPMAPISESSION Session(){return m_lpMAPISession;};

	LPCSTR						TranslateErrorCode(HRESULT hResult);

private:
	BOOL				m_bIsInitialized;
	LPMAPISESSION		m_lpMAPISession;
	HRESULT				m_hConstructorResult;
};

typedef C$$Root$$MAPIApp * LP$$ROOT$$MAPIAPP;

#endif  // $$ROOT$$_MAPIAPP_H
