/*
 * helpers.cpp - Native methods.
 *
 * (C) Copyright 1996 Microsoft Corporation
 */


/* Headers
 **********/

#include "project.hpp"
#pragma hdrstop

#include "com_ms_debug_RemoteBooleanObjectHelper.h"
#include "com_ms_debug_RemoteDoubleObjectHelper.h"
#include "com_ms_debug_RemoteFloatObjectHelper.h"
#include "com_ms_debug_EnumRemoteBooleanValueHelper.h"
#include "com_ms_debug_EnumRemoteDoubleValueHelper.h"
#include "com_ms_debug_EnumRemoteFloatValueHelper.h"
#include "com_ms_debug_ConstantPoolHelper.h"
#include "com_ms_debug_LockBytesHelper.h"


/***************************** Exported Functions ****************************/


/*
 *  Native method "helpers" are needed to marshal the following debugger interface methods:
 *
 *  	IJavaEnumRemoteBooleanValue::GetNext()
 *  	IRemoteBooleanObject::GetValue()
 *  	IRemoteBooleanObject::SetValue()
 *  	
 *  	IJavaEnumRemoteFloatValue::GetNext()
 *  	IRemoteFloatObject::GetValue()
 *  	IRemoteFloatObject::SetValue()
 *  	
 *  	IJavaEnumRemoteDoubleValue::GetNext()
 *  	IRemoteDoubleObject::GetValue()
 *  	IRemoteDoubleObject::SetValue()
 *  	
 *  	IRemoteMethodField::GetBytes()
 *  	
 *  	IRemoteClassField::GetConstantPoolItem()
 */


/* boolean */ long __cdecl com_ms_debug_EnumRemoteBooleanValueHelper_GetNext(Hcom_ms_debug_EnumRemoteBooleanValueHelper *thisptr)
{
    JAVA_BOOLEAN value;
    IJavaEnumRemoteBooleanValue *pierbv;

    pierbv = (IJavaEnumRemoteBooleanValue *)convert_Java_Object_to_IUnknown((HObject *)(thisptr->m_ierbv), &IID_IJavaEnumRemoteBooleanValue);

	if (pierbv)
	{
		HRESULT hr;

		hr = pierbv->GetNext(&value);
	
		switch (hr)
		{
			case S_OK:			// Retrieved next value.
				break;
	
			case S_FALSE:		// No more values.
				SignalError(NULL, "com/ms/com/ComSuccessException", "");
				break;
	
			default:			// Error.
				SignalError(NULL, "com/ms/com/ComFailException", "IJavaEnumRemoteBooleanValue::GetNext");
				break;
		}
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

    return(value);
}


/* boolean */ long __cdecl com_ms_debug_RemoteBooleanObjectHelper_GetValue(Hcom_ms_debug_RemoteBooleanObjectHelper *thisptr)
{
    JAVA_BOOLEAN value;
    IRemoteBooleanObject *pirbo;

    pirbo = (IRemoteBooleanObject *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_irbo, &IID_IRemoteBooleanObject);

	if (pirbo)
	{
		if (pirbo->GetValue(&value) != S_OK)
			SignalError(NULL, "com/ms/com/ComFailException", "IRemoteBooleanObject::GetValue");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

    return(value);
}


void __cdecl com_ms_debug_RemoteBooleanObjectHelper_SetValue(Hcom_ms_debug_RemoteBooleanObjectHelper *thisptr, /* boolean */ long newvalue)
{
    IRemoteBooleanObject *pirbo;

    pirbo = (IRemoteBooleanObject *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_irbo, &IID_IRemoteBooleanObject);

	if (pirbo)
	{
		if (pirbo->SetValue((JAVA_BOOLEAN)newvalue) != S_OK)
			SignalError(NULL, "com/ms/com/ComFailException", "IRemoteBooleanObject::SetValue");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);
}


JAVA_FLOAT __cdecl com_ms_debug_EnumRemoteFloatValueHelper_GetNext(Hcom_ms_debug_EnumRemoteFloatValueHelper *thisptr)
{
    JAVA_FLOAT value;
    IJavaEnumRemoteFloatValue *pierfv;

    pierfv = (IJavaEnumRemoteFloatValue *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_ierfv, &IID_IJavaEnumRemoteFloatValue);

	if (pierfv)
	{
		HRESULT hr;

		hr = pierfv->GetNext(&value);
	
		switch (hr)
		{
			case S_OK:			// Retrieved next value.
				break;
	
			case S_FALSE:		// No more values.
				SignalError(NULL, "com/ms/com/ComSuccessException", "");
				break;
	
			default:			// Error.
				SignalError(NULL, "com/ms/com/ComFailException", "IJavaEnumRemoteFloatValue::GetNext");
				break;
		}
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

    return(value);
}


JAVA_FLOAT __cdecl com_ms_debug_RemoteFloatObjectHelper_GetValue(Hcom_ms_debug_RemoteFloatObjectHelper *thisptr)
{
    JAVA_FLOAT value;
    IRemoteFloatObject *pirfo;

    pirfo = (IRemoteFloatObject *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_irfo, &IID_IRemoteFloatObject);

	if (pirfo)
	{
		if (pirfo->GetValue(&value) != S_OK)
			SignalError(NULL, "com/ms/com/ComFailException", "IRemoteFloatObject::GetValue");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

    return(value);
}


void __cdecl com_ms_debug_RemoteFloatObjectHelper_SetValue(Hcom_ms_debug_RemoteFloatObjectHelper *thisptr, float newvalue)
{
    IRemoteFloatObject *pirfo;

    pirfo = (IRemoteFloatObject *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_irfo, &IID_IRemoteFloatObject);

	if (pirfo)
	{
		if (pirfo->SetValue((JAVA_FLOAT*)&newvalue) != S_OK)
			SignalError(NULL, "com/ms/com/ComFailException", "IRemoteFloatObject::SetValue");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);
}


JAVA_DOUBLE __cdecl com_ms_debug_EnumRemoteDoubleValueHelper_GetNext(Hcom_ms_debug_EnumRemoteDoubleValueHelper *thisptr)
{
    JAVA_DOUBLE value;
    IJavaEnumRemoteDoubleValue *pierdv;

    pierdv = (IJavaEnumRemoteDoubleValue *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_ierdv, &IID_IJavaEnumRemoteDoubleValue);

	if (pierdv)
	{
		HRESULT hr;

		hr = pierdv->GetNext(&value);
	
		switch (hr)
		{
			case S_OK:			// Retrieved next value.
				break;
	
			case S_FALSE:		// No more values.
				SignalError(NULL, "com/ms/com/ComSuccessException", "");
				break;
	
			default:			// Error.
				SignalError(NULL, "com/ms/com/ComFailException", "IJavaEnumRemoteDoubleValue::GetNext");
				break;
		}
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

    return(value);
}


JAVA_DOUBLE __cdecl com_ms_debug_RemoteDoubleObjectHelper_GetValue(Hcom_ms_debug_RemoteDoubleObjectHelper *thisptr)
{
    JAVA_DOUBLE value;
    IRemoteDoubleObject *pirdo;

    pirdo = (IRemoteDoubleObject *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_irdo, &IID_IRemoteDoubleObject);

	if (pirdo)
	{
		if (pirdo->GetValue(&value) != S_OK)
			SignalError(NULL, "com/ms/com/ComFailException", "IRemoteDoubleObject::GetValue");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

    return(value);
}


void __cdecl com_ms_debug_RemoteDoubleObjectHelper_SetValue(Hcom_ms_debug_RemoteDoubleObjectHelper *thisptr, double newvalue)
{
    IRemoteDoubleObject *pirdo;

    pirdo = (IRemoteDoubleObject *)convert_Java_Object_to_IUnknown((HObject *)thisptr->m_irdo, &IID_IRemoteDoubleObject);

	if (pirdo)
	{
		if (pirdo->SetValue((JAVA_DOUBLE *)&newvalue) != S_OK)
			SignalError(NULL, "com/ms/com/ComFailException", "IRemoteDoubleObject::SetValue");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);
}


ClassArrayOfByte * __cdecl com_ms_debug_LockBytesHelper_GetBytes(Hcom_ms_debug_LockBytesHelper *, Hcom_ms_debug_ILockBytes *pjilb)
{
    ClassArrayOfByte *pjabyte = NULL;
	ILockBytes *pilb;

    pilb = (ILockBytes *)convert_Java_Object_to_IUnknown((Hjava_lang_Object *)pjilb, &IID_ILockBytes);

	if (pilb)
	{
		HRESULT hr;
		STATSTG statstg;
	
		// How many bytes can be read?
	
		hr = pilb->Stat(&statstg, STATFLAG_NONAME);
	
		if (hr == S_OK)
		{
			pjabyte = (ClassArrayOfByte *)ArrayAlloc(T_BYTE, statstg.cbSize.LowPart);
	
			if (pjabyte)
			{
				ULARGE_INTEGER ulnOffset;
				ULONG ulcbRead;
	
				ulnOffset.QuadPart = 0;
	
				hr = pilb->ReadAt(ulnOffset, pjabyte->body, statstg.cbSize.LowPart, &ulcbRead);
	
				if (hr != S_OK)
				{
					SignalError(0, "com.ms.com.ComFailException", "ILockBytes::ReadAt");
					pjabyte = NULL;
				}
			}
			else
				SignalError(0, JAVAPKG "OutOfMemoryError", 0);
		}
		else
			SignalError(0, "com.ms.com.ComFailException", "ILockBytes::Stat");
	}
	else
		SignalError(0, JAVAPKG "ClassCastException", 0);

	return(pjabyte);
}


ClassArrayOfByte * __cdecl com_ms_debug_ConstantPoolHelper_GetConstantPoolItem(Hcom_ms_debug_ConstantPoolHelper *thisptr, int niItem)
{
    ClassArrayOfByte *pjabyte = NULL;

    if (thisptr->m_ircf)
	{
		IRemoteClassField *pircf;
	
		pircf = (IRemoteClassField *)convert_Java_Object_to_IUnknown((Hjava_lang_Object *)(thisptr->m_ircf), &IID_IRemoteClassField);
	
		if (pircf)
		{
			HRESULT hr;
			PBYTE pbyteItem;
			ULONG ulcbLen;

			hr = pircf->GetConstantPoolItem(niItem, &pbyteItem, &ulcbLen);

			if (hr == S_OK)
			{
                pjabyte = (ClassArrayOfByte *)ArrayAlloc(T_BYTE, ulcbLen);
		
				if (pjabyte)
					CopyMemory(pjabyte->body, pbyteItem, ulcbLen);
				else
					SignalError(0, JAVAPKG "OutOfMemoryError", 0);

				CoTaskMemFree(pbyteItem);
                pbyteItem = NULL;
			}
			else
				SignalError(0, "com.ms.com.ComFailException", "IRemoteClassField::GetConstantPoolItem");
		}
		else
			SignalError(0, JAVAPKG "ClassCastException", 0);
	}
	else
		SignalError(0, JAVAPKG "IllegalArgumentException", 0);

	return(pjabyte);
}

