//-----------------------------------------------------------------------------
//
// File:		utiltest.cpp
//
// Copyright:	Copyright (c) 1997-1999 Microsoft Corporation
//
// Contents:	Small test program for class CUtil
//
// Comments:
//
//-----------------------------------------------------------------------------

#include <stdio.h>

#define dump(x)  printf("%s = \"",#x); DumpWChar(x); printf("\"\n")


// %S does not work in printf in Win95!
static void DumpWChar(WCHAR * str)
{
	char buf[4096];

	if (WideCharToMultiByte(CP_ACP, 0, str, -1, buf, sizeof(buf), NULL, NULL))
		printf("%s", buf);
	else
		printf("*DumpWChar*");
}


void main(void)
{
	CUtil util;
	WCHAR * conn = L"name1=value1;Data Source=CustomerDatabase;name2=value2";
	WCHAR * sql = L"CustomerById(2)";

	dump(conn);
	dump(sql);
	util.SetConn(conn);
	printf("GetUsername=%s\n", util.GetUsername());
	printf("HasReadAccess=%d\n", util.HasReadAccess());
	printf("HasWriteAccess=%d\n", util.HasWriteAccess());
	util.SetSql(sql);
	dump(util.GetConn());
	dump(util.GetSql());
}
