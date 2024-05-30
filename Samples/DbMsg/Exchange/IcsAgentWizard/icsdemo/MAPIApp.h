// MAPIApp.h: interface for the CMAPIApp class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "mapix.h"

class CMAPIApp  
{
public:
	CMAPIApp();
	virtual ~CMAPIApp();
	HRESULT Status(){return m_hConstructorResult;};
	LPMAPISESSION Session(){return m_lpMAPISession;};

	LPCSTR						TranslateErrorCode(HRESULT hResult);

private:
	static BOOL					m_bIsInitialized;
	static LPMAPISESSION		m_lpMAPISession;
	HRESULT						m_hConstructorResult;
};
