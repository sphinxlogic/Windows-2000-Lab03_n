//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//
//  Copyright (C) Microsoft Corporation, 1999 - 1999
//
//  File:       newcrypt.h
//
//--------------------------------------------------------------------------

#ifndef X509_AUTHORITY_INFO_ACCESS
#define X509_AUTHORITY_INFO_ACCESS          ((LPCSTR) 32)
#endif


// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#ifndef szOID_PKIX_KP_IPSEC_END_SYSTEM
#define szOID_PKIX_KP_IPSEC_END_SYSTEM  "1.3.6.1.5.5.7.3.5"
#endif

// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#ifndef szOID_PKIX_KP_IPSEC_TUNNEL
#define szOID_PKIX_KP_IPSEC_TUNNEL      "1.3.6.1.5.5.7.3.6"
#endif

// Consistent key usage bits: DIGITAL_SIGNATURE and/or
// (KEY_ENCIPHERMENT or KEY_AGREEMENT)
#ifndef szOID_PKIX_KP_IPSEC_USER
#define szOID_PKIX_KP_IPSEC_USER        "1.3.6.1.5.5.7.3.7"
#endif

// Consistent key usage bits: DIGITAL_SIGNATURE or NON_REPUDIATION
#ifndef szOID_PKIX_KP_TIMESTAMP_SIGNING
#define szOID_PKIX_KP_TIMESTAMP_SIGNING "1.3.6.1.5.5.7.3.8"
#endif


//+-------------------------------------------------------------------------
//  X509_AUTHORITY_INFO_ACCESS
//  szOID_AUTHORITY_INFO_ACCESS
//
//  pvStructInfo points to following CERT_AUTHORITY_INFO_ACCESS.
//
//  For CRYPT_E_INVALID_IA5_STRING, the error location is returned in
//  *pcbEncoded by CryptEncodeObject(X509_AUTHORITY_INFO_ACCESS)
//
//  Error location consists of:
//    ENTRY_INDEX   - 8 bits << 16
//    VALUE_INDEX   - 16 bits (unicode character index)
//
//  See X509_ALTERNATE_NAME for ENTRY_INDEX and VALUE_INDEX error location
//  defines.
//--------------------------------------------------------------------------

#ifndef szOID_PKIX_CA_ISSUERS
typedef struct _CERT_ACCESS_DESCRIPTION {
    LPSTR               pszAccessMethod;        // pszObjId
    CERT_ALT_NAME_ENTRY AccessLocation;
} CERT_ACCESS_DESCRIPTION, *PCERT_ACCESS_DESCRIPTION;


typedef struct _CERT_AUTHORITY_INFO_ACCESS {
    DWORD                       cAccDescr;
    PCERT_ACCESS_DESCRIPTION    rgAccDescr;
} CERT_AUTHORITY_INFO_ACCESS, *PCERT_AUTHORITY_INFO_ACCESS;


//+-------------------------------------------------------------------------
//  PKIX Access Description: Access Method Object Identifiers
//--------------------------------------------------------------------------
#define szOID_PKIX_ACC_DESCR            "1.3.6.1.5.5.7.48"
#define szOID_PKIX_OCSP                 "1.3.6.1.5.5.7.48.1"
#define szOID_PKIX_CA_ISSUERS           "1.3.6.1.5.5.7.48.2"
#endif
