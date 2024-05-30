/*
*	Copyright (c) 1993 - 1999 Microsoft Corporation
*
*	Implementation of CAcctMgmt class.
*	
*	It offers utility methods for NT account creation/deletion, 
*	conversion between Security Id and user login, generation
*	of Security Descriptor to be used on a mailbox creation in ADSI,
*  and conversion method from BSTR to an array of octets. 
*/



#include "stdafx.h"

#include <windows.h>
#include <lmcons.h>
#include <lmerr.h>
#include <lmapibuf.h>
#include <stdio.h>
#include <stdlib.h>
#include <lmaccess.h>
#include <accctrl.h>
#include <winnt.h>
#include <aclapi.h>


#include "acctcrt.h"
#include "AcctMgmt.h"



/////////////////////////////////////////////////////////////////////////////
// CAcctMgmt

/*
*	Create an NT account, also a LocalGroup if the specified one doesn't exist. 
*
*	Parameters: 
*		bstrDomain: 	domain name, NULL if on local machine.
*		bstrUserLogin: user login(alias), must not be NULL.
*		bstrPassword:	user password to be assigned
*		bstrUserComment: user comment
*		bstrLocalGroup: group name to which the user is assigned to, default to "Domain Users"
*
*/

STDMETHODIMP CAcctMgmt::NtAccountCreate(BSTR bstrDomain, BSTR bstrUserLogin, BSTR bstrPassword,
													 BSTR bstrUserComment, BSTR bstrLocalGroup)
{
	USER_INFO_1 		  user_info;
	LOCALGROUP_INFO_1 	  localgroup_info;
	LOCALGROUP_MEMBERS_INFO_3 localgroup_members;
	LPWSTR					  wszServerName = NULL;
	NET_API_STATUS 		  status = NERR_Success;
	DWORD 				  parm_err = 0;
	HRESULT hr = E_FAIL;
	LPWSTR wszRealGroup;
	
	/* check for validity of siginificant auguments */
	if (!bstrUserLogin || (SysStringLen(bstrUserLogin)==0))
		return E_INVALIDARG;
	
	if (!bstrLocalGroup || (SysStringLen(bstrLocalGroup)==0))
		wszRealGroup = L"Domain Users";
	else wszRealGroup = bstrLocalGroup;

	// check for invalid chars in userLogin
	if (wcspbrk(bstrUserLogin, L"\"/\\[]:;|=,+*?<>"))
		return E_INVALIDARG;

	if (SysStringLen(bstrUserLogin)>20)
		return E_INVALIDARG; 
	
	// userName made only of space or period is not allowed
	if (IsOneCharacter(bstrUserLogin, L' ') || IsOneCharacter(bstrUserLogin, L'.'))
		return E_INVALIDARG;

	/* First get the name of the Primary Domain Controller. */
	if (SUCCEEDED(hr = GetServerFromDomain(bstrDomain, &wszServerName)))
	{
		/* Set up the USER_INFO_1 struct */
		user_info.usri1_name = bstrUserLogin;	 
		user_info.usri1_password = bstrPassword;
		user_info.usri1_priv = USER_PRIV_USER; // must be this value
		user_info.usri1_home_dir = L"";
		user_info.usri1_comment = bstrUserComment;
		user_info.usri1_flags = UF_SCRIPT; // must incl. this flag.
		user_info.usri1_script_path = L"";
		status = NetUserAdd(wszServerName,		 /* PDC name */
			                 1, 				 /* level: USE_INFO_1 */
			                 (LPBYTE)&user_info,	/* input buffer */
			                 &parm_err );		 /* parameter in error */
		
		if ( status == NERR_Success)	
		{				
			/* Set up the LOCALGROUP_INFO_1 struct */
			localgroup_info.lgrpi1_name = wszRealGroup;
			localgroup_info.lgrpi1_comment = L"";
			status = NetLocalGroupAdd(wszServerName,	/* PDC name */
				                        1, 				/* level */
				                     (LPBYTE)&localgroup_info,	/* input buffer */
				                     &parm_err );				/* parm in error */
			
			if (( status == NERR_Success)   || (status == NERR_GroupExists))
			{	 
				/* Now add the user to the local group */
				localgroup_members.lgrmi3_domainandname = bstrUserLogin;
				status = NetLocalGroupAddMembers(wszServerName, 	/* PDC name */
					                              wszRealGroup, /* group name */
					                              3, 	  /* passing in name */
					                              (LPBYTE)&localgroup_members, /* Buffer */
					                              1 );					/* count passed in */
				if (status == NERR_Success) 
				{	 
					hr = S_OK;
				}	 
				
			}
			else if (status == ERROR_INVALID_PARAMETER)
			{
				AtlTrace(L"Invalid Parameter Error adding Local Group: Parameter Index = %d\n", status, parm_err);
				hr=E_INVALIDARG;	
			}
			else hr = HRESULT_FROM_WIN32(status);
			
		}
		else if (status == ERROR_INVALID_PARAMETER)
		{
			AtlTrace(L"Invalid Parameter Error adding user: Parameter Index = %d\n", parm_err);
			hr = E_INVALIDARG;
		}
		else hr = HRESULT_FROM_WIN32(status);
		
		if (wszServerName) NetApiBufferFree( wszServerName );  
		
	}
	
	
	return hr;	  
	
}
   
   
  /* 
   *  Delete an user account. 
   *
   *  Parameters:
   *     bstrDomain:    domain name, NULL if on local machine.
   *     bstrUserLogin: user alias.
   *
   */
STDMETHODIMP CAcctMgmt::NtAccountDelete(BSTR bstrDomain, BSTR bstrUserLogin)
{
	NET_API_STATUS status = NERR_Success;
	LPWSTR wszServerName=NULL;
	HRESULT hr = S_OK;
	
	if (!bstrUserLogin || (SysStringLen(bstrUserLogin)==0))
		return E_INVALIDARG;
	
	if (SUCCEEDED(hr = GetServerFromDomain(bstrDomain, &wszServerName)))
	{
		
      PUSER_MODALS_INFO_0 umi0;   
      NET_API_STATUS nas;   

      // make a local call to flush the cached SAM handle. It updates
      // the cached SAM handle to point at the local machine. This has the
      // side-effect of closing the active context associated with the
      // possible previous remote call.
      nas = NetUserModalsGet( NULL, // target local machine
                              0,           
                              (LPBYTE *)&umi0); 
      if(nas == NERR_Success) NetApiBufferFree(umi0);

		status = NetUserDel( wszServerName, bstrUserLogin);
		if (wszServerName) NetApiBufferFree( wszServerName );  
		
		if (status != NERR_Success) hr = HRESULT_FROM_WIN32(status);
	}
	
	return hr;
	
}

/* 
 *
 *
 *
 *
 *
 *
 */

STDMETHODIMP CAcctMgmt::VARIANT2Struct(VARIANT varOctetString, void** ppStruct)
{
   BYTE *it;
   int sidLeng, i;
	long lLowerBound, lUpperBound;
   BYTE *pRes;
   char *pszdata;
   HRESULT hr = E_FAIL;

   if (!ppStruct ) return E_INVALIDARG;
   *ppStruct = NULL;

   if (varOctetString.vt != (VT_ARRAY | VT_UI1 ) ) 
	{
		return E_INVALIDARG;
	}
	
	
	if (SUCCEEDED(hr = SafeArrayGetLBound(varOctetString.parray, 1, &lLowerBound)))
	{
		if (SUCCEEDED(hr = SafeArrayGetUBound(varOctetString.parray, 1, &lUpperBound)))
		{
			sidLeng = lUpperBound - lLowerBound+1;
			
			it = pRes = new BYTE[sidLeng/2+1]; 
			
			if (pRes) 
			{
				if (SUCCEEDED(hr = SafeArrayAccessData(varOctetString.parray,(void**) &pszdata)))
				{
					
					for (i= 0; i< sidLeng; i+=2)
					{	
						if (sscanf(pszdata, "%2hx", it)==EOF) break;
						pszdata += 2;
						it++;
					}

					SafeArrayUnaccessData(varOctetString.parray);
					
					if (i >= sidLeng)  // check against invalid pRes format, which causing break
               {
                  *ppStruct = pRes;
               }
            }
           
         }
         else hr = E_OUTOFMEMORY;
      }
      else hr = E_INVALIDARG;
   }
   else hr = E_INVALIDARG;

   return hr;
}
 
 /* 
	*	Internal method: convert a structure to a SAFEARRAY of octet string, to be able to pass
	*					to VB or VBScript.
	*
	*	Parameters:
	*		buf: pointer to the struct
	*		ulLeng: the bytecount of the struct
	*		saOT: returned pointer to SAFEARRAY of octet string
	*
*/
STDMETHODIMP CAcctMgmt::StructToOctetString(byte* buf, unsigned long ulLeng, SAFEARRAY **saOT)
{
	unsigned long i;
	
	SAFEARRAY* pArr; 
	SAFEARRAYBOUND rgsabound[1];	
	char elm[3];
	long dim[1];
	HRESULT hr = S_OK;
	
	if (!ulLeng) return E_INVALIDARG;
	if (!saOT) return E_INVALIDARG;
	
	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = 2*ulLeng;
	
	pArr = SafeArrayCreate(VT_UI1, 1, rgsabound);
	
	if (pArr) 
	{
		for (i=0; i<ulLeng; i++)
		{
			sprintf(elm, "%02hx", buf[i] );
			dim[0]=i*2;
			SafeArrayPutElement(pArr, dim, elm);
			dim[0]=i*2+1;
			SafeArrayPutElement(pArr, dim, &(elm[1]));
		}
		
	   *saOT = pArr;
		
	}
	else hr = E_OUTOFMEMORY;
	
	return hr;
}


STDMETHODIMP CAcctMgmt::GetSidStruct(BSTR bstrDomain, BSTR bstrUserLogin, PSID *pSid, unsigned long *pulSidLeng)
{
   unsigned long sidLeng=0;
	LPWSTR dn = NULL;
	unsigned long dnLeng=0;
	SID_NAME_USE typSid;
	HRESULT hr = E_FAIL;
	LPWSTR wszServerName = NULL;
   PSID psid = NULL;

   if (SUCCEEDED(hr = GetServerFromDomain(bstrDomain, &wszServerName)))
  	{
		
		if (bstrUserLogin && (( SysStringLen(bstrUserLogin)) >0 ))
		{
			
			// only to get the size into sidLeng (dnLeng as a sidekick)
			if (LookupAccountName(wszServerName, bstrUserLogin, psid, &sidLeng, dn, &dnLeng, &typSid)==0)
			{
				psid = (PSID)new char[sidLeng];
				dn = new wchar_t[dnLeng];
				
				if (psid && dn) 
				{
					if (LookupAccountName(wszServerName, bstrUserLogin, psid, &sidLeng, dn, &dnLeng, &typSid)!=0) 
					{
					   *pSid = psid;
                  *pulSidLeng = sidLeng;
					}
               else hr = E_FAIL;
					
					delete [] dn;
					
				}
				
				else hr = E_OUTOFMEMORY;
			}
			
		}
		else 
		{	
			hr = E_INVALIDARG;
		}

		if (wszServerName) NetApiBufferFree( wszServerName );  
	}
	
	return hr;


}
  /* 
	*	Get Sid from user name.
	*
	*	Parameters:
	*		bstrDomain: 	domain name, NULL if on local machine.
	*		bstrUserLogin:  user alias.
	*		varSid:			returned SID
	*
   */
STDMETHODIMP CAcctMgmt::GetSidFromName(BSTR bstrDomain, BSTR bstrUserLogin, VARIANT* varSid)
{
   PSID psid=NULL;
   unsigned long ulSidLeng;
   SAFEARRAY* pArr; 
   HRESULT hr = S_OK;
   
   if (!varSid) return E_INVALIDARG;
   
   if (SUCCEEDED(hr = GetSidStruct(bstrDomain, bstrUserLogin, &psid, &ulSidLeng)))
   {
      
      if (SUCCEEDED(hr = StructToOctetString((byte*)psid, ulSidLeng, &pArr)))
      {
         VariantInit(varSid);
         varSid->vt = VT_ARRAY | VT_UI1;
         varSid->parray = pArr;
      }
      delete [] psid;
   }

   return hr;
}


  /* 
	*	Get user name from a SID. 
	*
	*	Parameters:
	*		bstrDomain: 	domain name, NULL if on local machine.
	*		varSid:			in parameter, the SID
	*		varDomainName:  out parameter, domain name
	*		varUserLogin:	 out parameter, user alias.
	*
	*
   */
STDMETHODIMP CAcctMgmt::GetNameFromSid(BSTR bstrDomain, VARIANT varSid, VARIANT *varDomainName , VARIANT *varUserLogin )
{
	
	BYTE *pSid= NULL;

	SID_NAME_USE sidUse;
	BOOL fstatus;
   HRESULT hr = E_FAIL;
	BSTR pbsDomain, pbsUserName;
	LPWSTR wszUserName = NULL;
	LPWSTR wszServerName =NULL;
	LPWSTR wszDomain = NULL;
	unsigned long lDmSize = 0;
	unsigned long lUserSize = 0;
	
	
	if ( !varDomainName || !varUserLogin)
		return E_INVALIDARG;

   if (SUCCEEDED(hr = VARIANT2Struct(varSid, (void**)&pSid)))
   {				
      
		if (SUCCEEDED(hr = GetServerFromDomain(bstrDomain, &wszServerName)))
      {
         
         // only to get the size info into lUserSize and lDmSize
         if (LookupAccountSid(wszServerName, (PSID)pSid, wszUserName, 
            &lUserSize, wszDomain, &lDmSize,  &sidUse) == 0) 
         {
            wszUserName = new wchar_t[lUserSize+1];
            wszDomain = new wchar_t[lDmSize+1];
            
            
            if (wszUserName && wszDomain) 
            {	 
               if ((fstatus = LookupAccountSid(wszServerName, (PSID)pSid, wszUserName, &lUserSize, 
                  wszDomain, &lDmSize,	&sidUse)) != 0)
                  
               {
                  
                  if (wszUserName && wcslen(wszUserName)>0)
                  {
                     pbsDomain = SysAllocString(wszDomain);
                     pbsUserName = SysAllocString(wszUserName);
                     
                     if (pbsDomain && pbsUserName) 
                     {
                        VariantInit(varDomainName);
                        varDomainName->vt = VT_BSTR;
                        V_BSTR(varDomainName) = pbsDomain;
                        
                        VariantInit(varUserLogin);
                        varUserLogin->vt = VT_BSTR;
                        V_BSTR(varUserLogin) = pbsUserName;
                        
                        hr = S_OK;
                        
                     }
                     else hr = E_OUTOFMEMORY;
                  }
                  else hr = E_INVALIDARG; // varSid is not valid
               }
               else 
               {
                  hr = E_FAIL;
               }
               delete [] wszUserName;
               delete [] wszDomain;
            }
            else hr = E_OUTOFMEMORY;
            
         }
         else hr = E_FAIL;
      }
      
      if (wszServerName) NetApiBufferFree( wszServerName );  
                     
      delete [] pSid;
   }
	
	return hr;
}

/* 
*	Obtain a default security descriptor to be used on a mailbox. 
*
*	Parameters:
*		bstrDomain: domain name 
*		bstrUserLogin: normally name of the user who owns the mailbox
*		varSecDes: returned security descriptor
*
*
*/

STDMETHODIMP CAcctMgmt::GenerateSecDescriptor(BSTR bstrDomain, BSTR bstrUserLogin, VARIANT * varSecDes)
{
	
	TRUSTEE ownerTrustee;
	TRUSTEE groupTrustee;
	EXPLICIT_ACCESS expAccess[1]; 
	SECURITY_DESCRIPTOR *newSD;
	ULONG sz;
	HRESULT hr = E_FAIL;
	BSTR bstrDomainLogin;
	bool alloced = false;

	if (!varSecDes || !bstrUserLogin) return E_INVALIDARG;
	
	if (!bstrDomain || (SysStringLen(bstrDomain)==0))
		bstrDomainLogin = bstrUserLogin;
	else 
	{
		CComBSTR resBstr(bstrDomain);

	
		resBstr.Append("\\");
		resBstr.Append(bstrUserLogin);
		bstrDomainLogin = resBstr.Copy();
		if (!bstrDomainLogin)
			return E_OUTOFMEMORY;
		alloced = true;
	}

	
	ownerTrustee.pMultipleTrustee = NULL;
	ownerTrustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
	ownerTrustee.TrusteeForm = TRUSTEE_IS_NAME;
	ownerTrustee.TrusteeType = TRUSTEE_IS_USER;
	ownerTrustee.ptstrName =	bstrDomainLogin;
	
	groupTrustee.pMultipleTrustee = NULL;
	groupTrustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
	groupTrustee.TrusteeForm = TRUSTEE_IS_NAME;
	groupTrustee.TrusteeType = TRUSTEE_IS_GROUP;
	groupTrustee.ptstrName = bstrDomainLogin;
	
	
	expAccess[0].grfAccessPermissions = 0x1a;  // magic number
	expAccess[0].grfAccessMode = SET_ACCESS;
	expAccess[0].grfInheritance = NO_INHERITANCE;
	memcpy(&(expAccess[0].Trustee), &ownerTrustee, sizeof(TRUSTEE));
	expAccess[0].Trustee.ptstrName = bstrDomainLogin;
	
	
	if (BuildSecurityDescriptor(&ownerTrustee, &groupTrustee, 1, expAccess, 0, NULL, NULL, &sz, (void**)&newSD)==ERROR_SUCCESS)
	{
		//conversion to array of octet string
		SAFEARRAY *pArr;
		
		if (SUCCEEDED(hr = StructToOctetString((unsigned char*)newSD, sz, &pArr)))
		{
			VariantInit(varSecDes);
			varSecDes->vt = VT_ARRAY | VT_UI1;
			varSecDes->parray = pArr;
		}
		
		LocalFree(newSD);
	}
	
	if (alloced) SysFreeString(bstrDomainLogin);
	return hr;
}


  /* 
	*	Utility Function, to convert a BSTR to an array of octets.
	*                    handy in VBScript.
	*	Parameters:
	*		bstrInput: input BSTR parameter
	*		varArrayOfOctets: output VARIANT parameter
	*
	*
	*/

STDMETHODIMP CAcctMgmt::BstrToArrayOfOctets(BSTR bstrInput, VARIANT * varArrayOfOctets)
{
   SAFEARRAY *pSafeArr;
   SAFEARRAYBOUND rgsaArrayBound[1];
   void *pArr;
   char *szData;
   int cLeng;
   HRESULT hr = S_OK;

   cLeng = SysStringLen(bstrInput);

   if ((cLeng<=0)  || !varArrayOfOctets)
      return E_INVALIDARG;

   rgsaArrayBound[0].lLbound = 0;
   rgsaArrayBound[0].cElements = cLeng;
   
   pSafeArr = SafeArrayCreate(VT_UI1, 1, rgsaArrayBound);
   szData = new char[cLeng];

   if (pSafeArr && szData)
   {
      // no error checking needed since we are the creator of pSafeArr
      SafeArrayAccessData(pSafeArr, &pArr);
      
      wcstombs(szData, bstrInput, cLeng);
      memcpy(pArr, szData, cLeng*sizeof(char));
      
      SafeArrayUnaccessData(pSafeArr);

      varArrayOfOctets->vt = VT_ARRAY | VT_UI1;
      varArrayOfOctets->parray = pSafeArr;

   
   }
   else hr = E_OUTOFMEMORY;
   
   return hr;
}

  /* 
	*	Protected method, to get the domain controller name from given domain name
	*
	*	Parameters:
	*		bstrDomain: domain name (input argument)
	*		wcsServerName: server name (output argument)
	*
	*
	*/
  
STDMETHODIMP CAcctMgmt::GetServerFromDomain(BSTR bstrDomain, LPWSTR* pwszServerName)
{
	
	NET_API_STATUS status;
	
	if (!pwszServerName) return E_INVALIDARG;
	
	if (bstrDomain && (SysStringLen(bstrDomain) > 0 ))
	{
		status = NetGetDCName(NULL,				  /* Local Machine */
	                  		bstrDomain, 			  /* Domain Name */
			                  (LPBYTE *)pwszServerName ); /* returned Primary DC */

		if ( status != NERR_Success )  
		{
			ATLTRACE(L"Error getting DC name: %d\n", status);
			return E_FAIL;
		}
		
	}
	else 
	{
		*pwszServerName = NULL;
	}
	
	return S_OK;
	
}


  /* 
	*	Protected method, to check for if the string is made of the sole character
	*
	*	Parameters:
	*		bstrSrc: the string to be checked against
	*		cMatch: the character to match
	*
	*
	*/


bool CAcctMgmt::IsOneCharacter(BSTR bstrSrc, wchar_t cMatch)
{
	int i, ct; 
	wchar_t *wcsNext = bstrSrc;
	bool isOneChar = false;
	ct = SysStringLen(bstrSrc);

	for (i=0; i<ct; i++)
	{
		if (*wcsNext != cMatch) 
			break;

		wcsNext++;
	}

	if (i>=ct) isOneChar = true;

	return isOneChar;
}



STDMETHODIMP CAcctMgmt::ChangeOwnerOfSecDescriptor(BSTR bstrOldDomain, BSTR bstrOldOwner, BSTR bstrNewDomain, BSTR bstrNewOwner, 
                                                   VARIANT varSecDesp, VARIANT * varNewSecDesp)
{
   PSID psid=NULL; 
   PSID pOldSid= NULL;
   HRESULT hr = E_INVALIDARG;
   PSECURITY_DESCRIPTOR pSecDesp;
   SAFEARRAY* pArr; 
   unsigned long ulSid, ulOldSid;
   unsigned long ulSDLeng=0;
   
   if (SUCCEEDED(hr = GetSidStruct(bstrOldDomain, bstrOldOwner, &pOldSid, &ulOldSid))
      && SUCCEEDED(hr = GetSidStruct(bstrNewDomain, bstrNewOwner, &psid, &ulSid)))
   {
      
      if (SUCCEEDED(hr = VARIANT2Struct(varSecDesp, &pSecDesp)))
      {
         
         PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor=NULL;
         // address of absolute SD
         DWORD dwAbsoluteSecurityDescriptorSize = 0;
         PACL pDacl=NULL;                   // address of discretionary ACL
         DWORD dwDaclSize=0;         // address of size of discretionary ACL
         PACL pSacl=NULL;                   // address of system ACL
         DWORD dwSaclSize=0;         // address of size of system ACL
         PSID pOwner=NULL;                  // address of owner SID
         DWORD dwOwnerSize=0;        // address of size of owner SID
         PSID pPrimaryGroup=NULL ;          // address of primary-group SID
         DWORD dwPrimaryGroupSize=0;  // address of size of group SID);
         
         MakeAbsoluteSD(pSecDesp, 
            pAbsoluteSecurityDescriptor, 
            &dwAbsoluteSecurityDescriptorSize, 
            pDacl,
            &dwDaclSize,
            pSacl, 
            &dwSaclSize,
            pOwner,
            &dwOwnerSize, 
            pPrimaryGroup, 
            &dwPrimaryGroupSize);
         
         
         pAbsoluteSecurityDescriptor = new BYTE[dwAbsoluteSecurityDescriptorSize];
         pDacl = (PACL)new BYTE[dwDaclSize];
         pSacl = (PACL)new BYTE[dwSaclSize];
         pOwner = (PSID)new BYTE[dwOwnerSize];
         pPrimaryGroup = (PSID) new BYTE[dwPrimaryGroupSize];
         
         if (pAbsoluteSecurityDescriptor && pDacl && pOwner && pPrimaryGroup)
         {
            if (MakeAbsoluteSD(pSecDesp, 
               pAbsoluteSecurityDescriptor, 
               &dwAbsoluteSecurityDescriptorSize, 
               pDacl,
               &dwDaclSize,
               pSacl, 
               &dwSaclSize,
               pOwner,
               &dwOwnerSize, 
               pPrimaryGroup, 
               &dwPrimaryGroupSize)!=0)
            {
               
               ReplaceSidInAcl(pDacl, pOldSid, psid, ulSid);                      
               if (SetSecurityDescriptorOwner(pAbsoluteSecurityDescriptor, psid, FALSE)!=0)
               {
                  MakeSelfRelativeSD(pAbsoluteSecurityDescriptor, pSecDesp, &ulSDLeng);
                  delete [] pSecDesp;
                  pSecDesp = new BYTE[ulSDLeng];
                  
                  if (pSecDesp)
                  {
                     if (MakeSelfRelativeSD(pAbsoluteSecurityDescriptor, pSecDesp, &ulSDLeng))
                     {
                        
                        if (SUCCEEDED(hr = StructToOctetString((unsigned char*)pSecDesp, ulSDLeng, &pArr)))
                        {  
                           VariantInit(varNewSecDesp);
                           varNewSecDesp->vt = VT_ARRAY | VT_UI1;
                           varNewSecDesp->parray = pArr;
                        }
                     }
                     
                     
                  }
                  else hr = E_OUTOFMEMORY;
               }
               
            }
            
            delete [] pAbsoluteSecurityDescriptor;
            delete [] pDacl;
            delete [] pSacl;
            delete [] pOwner;
            delete [] pPrimaryGroup;
            
            
         }
         else hr = E_OUTOFMEMORY;
         
         
         delete [] pSecDesp;
      }
   
      delete [] psid;
      delete [] pOldSid;
   }
   return hr;

}

STDMETHODIMP CAcctMgmt::ReplaceSidInAcl(PACL pAcl, PSID pOldSid, PSID pNewSid, int iSidLeng)
{
   unsigned long ulAceNum, i;
   PACCESS_ALLOWED_ACE pTempAce; // type placeholder, actually operates on 4 types of ACEs.
   PSID pSID;

   ulAceNum = pAcl->AceCount;
 

   for (i=0;i<ulAceNum; i++)
   {
      if (GetAce(pAcl, i, (void**)&pTempAce))
      {
            pSID=(PSID)&(pTempAce)->SidStart;  

         if (!memcmp(pSID, pOldSid, iSidLeng))
            memcpy(pSID, pNewSid, iSidLeng);
      }
   }

   return S_OK;
}



