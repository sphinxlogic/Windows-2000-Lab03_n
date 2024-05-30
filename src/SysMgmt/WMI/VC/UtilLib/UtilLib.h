// **************************************************************************
// Copyright (c) 1999 Microsoft Corporation.
//
// File:  utillib.h
//
// Description:
//    Set of sample routines
//
// History:
//
// **************************************************************************

#define MAXITOA  19
#define FWPRINTF myFWPrintf
#define CLASSPROP L"__CLASS"
#define SERVERPROP L"__SERVER"
#define PATHPROP L"__PATH"
#define NAMESPACEPROP L"__NAMESPACE"
#define SYSTEMCLASS L"__SystemClass"
#define RELPATHPROP L"__RELPATH"
#define NAMEPROP L"Name"
#define CIMTYPEQUAL L"CIMTYPE"
#define KEYQUAL L"key"
#define SYSTEMPREFIX L"__"
#define CVTFAILED L"WideCharToMultiByte failed\n"
#define RELEASE(a) if (a) { (a)->Release(); (a)=NULL;}
#define BLOCKSIZE (32 * sizeof(WCHAR))
#define CVTBUFSIZE (309+40) /* # of digits in max. dp value + slop  (this size stolen from cvt.h in c runtime library) */
#define PAGESIZE 4096

char *cvt(WCHAR *x, char **y);
double difftime(struct _timeb finish, struct _timeb start);
int myFWPrintf(FILE *f, WCHAR *fmt, ...);
const WCHAR *TypeToString(VARIANT *p);
const WCHAR *TypeToString(VARTYPE v);
const WCHAR *TypeToString(CIMTYPE v);
WCHAR *ValueToString(CIMTYPE dwType, VARIANT *pValue, WCHAR **pbuf, WCHAR *fnHandler(VARIANT *pv) = NULL);
WCHAR *WbemErrorString(SCODE sc);
void PrintErrorAndExit(char *pszFailureReason, SCODE sc = 0);
void PrintErrorAndAsk(char *pszFailureReason, SCODE sc = 0);
void PrintError(char *pszFailureReason, SCODE sc = 0);

#ifndef _BSTRING_H_
#define _BSTRING_H_

class CBString
{
private:
	LPOLESTR	m_pString;

public:
	CBString()
	{
		m_pString = NULL;
	}

	CBString(LPWSTR pwszString) 
	{
		m_pString = SysAllocString(pwszString);
	}

	~CBString()
	{
		if(m_pString) {
			SysFreeString(m_pString);
		}
	}

	operator BSTR()
	{
		return m_pString;
	}
};

#endif _BSTRING_H_

class MyString {
private:
   WCHAR *pwszString;

public:
   MyString::MyString() {pwszString = (WCHAR *)calloc(1, sizeof(WCHAR));}
   MyString::~MyString() {free(pwszString);}
   WCHAR *GetString() {return pwszString;}
   void Empty() {free(pwszString);pwszString = (WCHAR *)calloc(1, sizeof(WCHAR));}
   WCHAR *GetCloneString() {
      WCHAR *buf;
      buf = (WCHAR *)malloc((wcslen(pwszString) + 1) * sizeof(WCHAR));
      wcscpy(buf, pwszString);
      return buf;
   }
   const MyString& operator+=(const WCHAR *arg1) 
      {
         int iHave;
         int iNeed;
         iHave = wcslen(pwszString);
         iNeed = wcslen(arg1);
         pwszString = (WCHAR *)realloc(pwszString, (iHave + iNeed + 1) * sizeof(WCHAR));
         wcscat(&pwszString[iHave], arg1);
         return *this;
      }

};

