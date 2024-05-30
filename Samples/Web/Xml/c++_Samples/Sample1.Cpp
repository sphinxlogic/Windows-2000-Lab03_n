////////////////////////////////////////////////////////////////////////////
// Sample1.cxx: XML DOM Object Model Sample 1
//
// This sample file just contains a collection of snippets showing how to
// Load and XML document from disk or from a URL, manipulate it in-memory, 
// then save it back out.
//
//--------------------------------------------------------------------------
// Copyright (c) 1999  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//--------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "filestream.h"

#define CHECKHR(x) {hr = x; if (FAILED(hr)) goto CleanUp;}
#define SAFERELEASE(p) {if (p) {(p)->Release(); p = NULL;}}


////////////////////////////////////////////////////////////////////////////
// Helper function: Create an IStream object for reading the specified URL.
////////////////////////////////////////////////////////////////////////////
HRESULT CreateURLStream(char *pszFName, IStream **ppStm)
{
    char        szURL[MAX_PATH];

    if (strncmp(pszFName, "http:", 5) != 0)
    {
        ::GetFullPathNameA(pszFName, MAX_PATH, szURL, NULL);
    }
    else
        strcpy(szURL, pszFName);

    HRESULT hr = URLOpenBlockingStreamA(0, szURL, ppStm, 0, 0);

    return hr;
}


////////////////////////////////////////////////////////////////////////////
// Helper function: Report parsing error information
////////////////////////////////////////////////////////////////////////////
HRESULT ReportError(IXMLDOMParseError *pXMLError)
{
    long line, linePos;
    LONG errorCode;
    BSTR pBURL, pBReason;
    HRESULT hr;

    CHECKHR(pXMLError->get_line(&line));
    CHECKHR(pXMLError->get_linepos(&linePos));
    CHECKHR(pXMLError->get_errorCode(&errorCode));
    CHECKHR(pXMLError->get_url(&pBURL));
    CHECKHR(pXMLError->get_reason(&pBReason));

    fprintf(stderr, "%S", pBReason);
    if (line > 0)
    {
        fprintf(stderr, "Error on line %d, position %d in \"%S\".\n", 
            line, linePos, pBURL);
    }

CleanUp:

    SysFreeString(pBURL);
    SysFreeString(pBReason);

    return E_FAIL;
}

////////////////////////////////////////////////////////////////////////////
// Helper function: Check load results
////////////////////////////////////////////////////////////////////////////
HRESULT CheckLoad(IXMLDOMDocument* pDoc)
{
    // And since we don't have the VARIANT_BOOL from load we
    // need to check the parse Error errorCode property to see
    // if everything went ok.
    IXMLDOMParseError  *pXMLError = NULL;
    LONG errorCode = E_FAIL;
    HRESULT hr;

    CHECKHR(pDoc->get_parseError(&pXMLError));
    CHECKHR(pXMLError->get_errorCode(&errorCode));
    if (errorCode != 0)
    {
        hr = ReportError(pXMLError);
        goto CleanUp;
    }
    else
    {
        fprintf(stderr, "XML document loaded successfully\n");
    }
CleanUp:
    SAFERELEASE(pXMLError);
    return errorCode;
}


////////////////////////////////////////////////////////////////////////////
// Helper function: Create an IDOMNode of the given type
////////////////////////////////////////////////////////////////////////////
IXMLDOMNode * CreateDOMNode(IXMLDOMDocument* pDoc, 
              DOMNodeType type, BSTR bstrName)
{
    IXMLDOMNode * node;
    VARIANT vtype;

    vtype.vt = VT_I4;
    V_I4(&vtype) = (int)type;

    pDoc->createNode(vtype, bstrName, NULL, &node);
    return node;
}

////////////////////////////////////////////////////////////////////////////
// Helper function:
////////////////////////////////////////////////////////////////////////////
SetIntegerAttribute(IXMLDOMNode* pNode, BSTR bName, int i)
{
    IXMLDOMElement* pEle = NULL;
    VARIANT v;
    HRESULT hr;

    CHECKHR(pNode->QueryInterface(IID_IXMLDOMElement, (void**)&pEle));

    v.vt = VT_I4;
    V_I4(&v) = i;
    pEle->setAttribute(bName, v);

CleanUp:
    SAFERELEASE(pEle);
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Function: Create an XML DOM Document from Scratch in memory
////////////////////////////////////////////////////////////////////////////
HRESULT BuildDocument(IXMLDOMDocument* pDoc)
{
    IXMLDOMNode *root = NULL;
    IXMLDOMElement *rootElem = NULL;
    VARIANT  after;
    IXMLDOMNode *node = NULL, *p = NULL, *p1 = NULL;
    HRESULT hr = S_OK;
    BSTR rootName = NULL;
    BSTR orderName = NULL;
    BSTR itemName = NULL;
    BSTR idName = NULL;
    int i, j;

    //
    // Create an xml document from scratch
    //
    rootName = ::SysAllocString(L"Root");
    orderName = ::SysAllocString(L"Order");
    itemName = ::SysAllocString(L"Item");
    idName = ::SysAllocString(L"id");

    // Create a root node
    root = CreateDOMNode(pDoc, NODE_ELEMENT, rootName);

    //
    // add children nodes
    //
    after.vt = VT_EMPTY;
    for (i = 0; i < 10; i++)
    {
        node = CreateDOMNode(pDoc, NODE_ELEMENT, orderName);
        SetIntegerAttribute(node, idName, i);
        CHECKHR(root->insertBefore(node, after, &p));
        // The XML Document should now own the node.
        SAFERELEASE(node);

        for (j = 0; j < 10; j++)
        {
            node = CreateDOMNode(pDoc, NODE_ELEMENT, itemName);
            SetIntegerAttribute(node, idName, (i*10) + j);
            CHECKHR(p->insertBefore(node, after, &p1));
            // The XML Document should now own the node.
            SAFERELEASE(node);
            SAFERELEASE(p1);
        }
        SAFERELEASE(p);
    }

    // Now attach this new subtree to the document.
    pDoc->appendChild(root, NULL);

CleanUp:
    SAFERELEASE(root);
    SAFERELEASE(node);
    SAFERELEASE(p);
    SAFERELEASE(p1);
    SysFreeString(rootName);
    SysFreeString(orderName);
    SysFreeString(itemName);
    SysFreeString(idName);
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Function: Return an in-memory encoded version of the XML data which
// we can squirrel away in memory for use later.  This is better 
// and faster than storing the document in a huge BSTR via get_xml.
////////////////////////////////////////////////////////////////////////////
HRESULT PersistInMemory(IXMLDOMDocument* pDoc, PBYTE* ppBuffer, ULONG *pLen)
{
    IPersistStreamInit     *pPSI = NULL;
    LARGE_INTEGER li = {0, 0};
    IStream                *pStm = NULL;
    HGLOBAL                 hGlobal;
    BYTE                  *pbData = NULL;
    ULARGE_INTEGER          uli;
    ULONG                   size;
    HRESULT                 hr;
    //
    // Create stream in global memory and save the xml document to it
    //
    CHECKHR(CreateStreamOnHGlobal(NULL, TRUE, &pStm));

    CHECKHR(pDoc->QueryInterface(IID_IPersistStreamInit, (void **)&pPSI));
    CHECKHR(pPSI->Save(pStm, TRUE));

    // now to get the real size of the stream, we have to use the
    // seek function.  You can't depend on the GlobalSize because
    // the hGlobal might have been rounded up to some paragraph boundary.
    CHECKHR(pStm->Seek(li, STREAM_SEEK_CUR, &uli));
    size = (int)uli.QuadPart;
    *pLen = size;

    pbData = new BYTE[size];
    if (pbData == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto CleanUp;
    }
    *ppBuffer = pbData;

    CHECKHR(GetHGlobalFromStream(pStm, &hGlobal));
    ::memcpy(pbData, (PBYTE)GlobalLock(hGlobal), size);
    GlobalUnlock(hGlobal);


CleanUp:
    SAFERELEASE(pPSI);
    SAFERELEASE(pStm);
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Function: Load the document from in-memory encoded bytes.
////////////////////////////////////////////////////////////////////////////
HRESULT LoadInMemory(IXMLDOMDocument* pDoc, PBYTE pData, ULONG ulLen)
{
    IPersistStreamInit     *pPSI = NULL;
    IStream                *pStm = NULL;
    HRESULT hr;
    ULONG ulWritten;
    LARGE_INTEGER li = {0, 0};

    // Create a stream and write the bytes to it
    CHECKHR(CreateStreamOnHGlobal(NULL, TRUE, &pStm));
    pStm->Write(pData, ulLen, &ulWritten);

    // Reset the stream back to the beginning
    CHECKHR(pStm->Seek(li, STREAM_SEEK_SET, NULL));

    // Now, load the document from the stream
    CHECKHR(pDoc->QueryInterface(IID_IPersistStreamInit, (void **)&pPSI));
    CHECKHR(pPSI->Load(pStm));

CleanUp:
    SAFERELEASE(pPSI);
    SAFERELEASE(pStm);
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Function: Walk all the Elements in a loaded XML document.
////////////////////////////////////////////////////////////////////////////
HRESULT WalkTree(IXMLDOMNode* node, int level)
{
    IXMLDOMNode* pChild, *pNext;
    BSTR nodeName;
    IXMLDOMNamedNodeMap* pattrs;

    node->get_nodeName(&nodeName);
    for (int i = 0; i < level; i++)
        printf(" ");
    printf("%S",nodeName);
    SysFreeString(nodeName);


    if (SUCCEEDED(node->get_attributes(&pattrs)) && pattrs != NULL)
    {
        pattrs->nextNode(&pChild);
        while (pChild)
        {
            BSTR name;
            pChild->get_nodeName(&name);
            printf(" %S='", name);
            ::SysFreeString(name);

            VARIANT value;
            pChild->get_nodeValue(&value);
            if (value.vt == VT_BSTR)
            {
                printf("%S", V_BSTR(&value));
            }
            printf("'");
            VariantClear(&value);
            pChild->Release();
            pattrs->nextNode(&pChild);
        }
        pattrs->Release();
    }
    printf("\n");

    node->get_firstChild(&pChild);
    while (pChild)
    {
        WalkTree(pChild, level+1);
        pChild->get_nextSibling(&pNext);
        pChild->Release();
        pChild = pNext;
    }

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////
// Function: Load an XML Document from the specified file or URL synchronously.
////////////////////////////////////////////////////////////////////////////
HRESULT LoadDocumentSync(IXMLDOMDocument *pDoc, BSTR pBURL)
{
    IXMLDOMParseError  *pXMLError = NULL;
    VARIANT         vURL;
    VARIANT_BOOL    vb;
    HRESULT         hr;

    CHECKHR(pDoc->put_async(VARIANT_FALSE));

    // Load xml document from the given URL or file path
    VariantInit(&vURL);
    vURL.vt = VT_BSTR;
    V_BSTR(&vURL) = pBURL;
    CHECKHR(pDoc->load(vURL, &vb));

    CHECKHR(CheckLoad(pDoc));
                    
CleanUp:
    SAFERELEASE(pXMLError);
   
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Helper Function: Wait for async download to complete
////////////////////////////////////////////////////////////////////////////
HRESULT WaitForCompletion(IXMLDOMDocument *pDoc)
{
    long            ready;
    MSG             msg;
    HRESULT         hr;

    CHECKHR(pDoc->get_readyState(&ready));
    while (ready != READYSTATE_COMPLETE)
    {
        GetMessage(&msg, NULL, 0, 0);
        DispatchMessage(&msg);
        CHECKHR(pDoc->get_readyState(&ready));
    }

    while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
    {
        GetMessage(&msg, NULL, 0, 0);
        DispatchMessage(&msg);
    }

CleanUp:    
    return S_OK;
}

////////////////////////////////////////////////////////////////////////////
// Function: Load an XML Document from the specified file or URL asynchronously.
////////////////////////////////////////////////////////////////////////////
HRESULT LoadDocumentAsync(IXMLDOMDocument *pDoc, BSTR pBURL)
{
    VARIANT_BOOL    vb;
    HRESULT         hr;
    VARIANT         vURL;

    // set asynchronous loading flag
    CHECKHR(pDoc->put_async(VARIANT_TRUE));

    // Load xml document from the given URL
    vURL.vt = VT_BSTR;
    V_BSTR(&vURL) = pBURL;
    pDoc->load(vURL, &vb);

    // Now wait for download to complete !
    WaitForCompletion(pDoc);

    CHECKHR(CheckLoad(pDoc));
                    
CleanUp:
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Function: Load an XML document from a given stream object
////////////////////////////////////////////////////////////////////////////
HRESULT LoadDocumentStream(IXMLDOMDocument *pDoc, IStream* pStm)
{
    IPersistStreamInit *pPSI = NULL;
    HRESULT hr;

    CHECKHR(pDoc->QueryInterface(IID_IPersistStreamInit, (void **)&pPSI));
    hr = pPSI->Load(pStm);

    // Since we don't know whether this was a URLStream or not.
    WaitForCompletion(pDoc);

    CHECKHR(CheckLoad(pDoc));

CleanUp:
    SAFERELEASE(pPSI);
    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Function: Save document out to specified local file.
////////////////////////////////////////////////////////////////////////////
HRESULT SaveDocument(IXMLDOMDocument *pDoc, BSTR pBFName)
{
    HRESULT hr = S_OK;
    VARIANT vName;

    vName.vt = VT_BSTR;
    V_BSTR(&vName) = pBFName;
    CHECKHR(pDoc->save(vName));

CleanUp:

    return hr;
}

////////////////////////////////////////////////////////////////////////////
// Helper Function: Convert ascii string to BSTR
////////////////////////////////////////////////////////////////////////////
BSTR AsciiToBSTR(const char* pszFName)
{
    WCHAR wszURL[MAX_PATH];
    ::MultiByteToWideChar(CP_ACP, 0, pszFName, -1, wszURL, MAX_PATH);
    return SysAllocString(wszURL);
}

////////////////////////////////////////////////////////////////////////////
// Helper Function: Print sample app command line options
////////////////////////////////////////////////////////////////////////////
void PrintUsage(char* exe)
{
    fprintf(stderr, "Usage: %s <options> [filename]\n",exe);
    fprintf(stderr, "Illustrates various load/save combinations of IXMLDOMDocument\n");
    fprintf(stderr, "Options are:\n");
    fprintf(stderr, "-a           Async load of specified URL\n");
    fprintf(stderr, "-s           Load via IStream\n");
    fprintf(stderr, "-u           Load IStream via URLMON\n");
    fprintf(stderr, "-m           Build a document in memory\n");
    fprintf(stderr, "-w           Walk the loaded XML document tree\n");
    fprintf(stderr, "-o <outfile> Saves document to specified file.\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Must have either -m or a filename to load.");
}

////////////////////////////////////////////////////////////////////////////
// Function: Main sample program entry point.
////////////////////////////////////////////////////////////////////////////
int _cdecl 
main(int argc, char *argv[])
{
    HRESULT hr = S_OK;
    IXMLDOMDocument *pDoc = NULL;
    IXMLDOMNode* pNode = NULL;
    BSTR pBURL = NULL;
    BSTR pBOutputName = NULL;
    IStream* pStm = NULL;
    char* pszFileName = NULL;
    bool fStream = false;
    bool fAsync = false;
    bool fLocal = false;
    bool fMem = false;
    bool fWalk = false;
    int i;

    CoInitialize(NULL);

    // Create an empty XML document
    CHECKHR(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
                                IID_IXMLDOMDocument, (void**)&pDoc));

    // parse args.
    if (argc == 1)
    {
        PrintUsage(argv[0]);
        goto CleanUp;
    }

    for (i = 1; i < argc; i++)
    {
        char* arg = argv[i];
        if (arg[0] == '-')
        {
            switch (arg[1])
            {
            case 'a':
                fAsync = true;
                break;
            case 's':
                fStream = true;
                break;
            case 'u':
                fLocal = false;
                break;
            case 'o':
                pBOutputName = AsciiToBSTR(argv[++i]);
                break;
            case 'm':
                fMem = true;
                break;
            case 'w':
                fWalk = true;
                break;
            }
        }
        else
        {
            pszFileName = arg;
        }
    }

    if (pszFileName)
    {  
        pBURL = AsciiToBSTR(pszFileName);

        if (! fStream)
        {
            if (fAsync)
                hr = LoadDocumentAsync(pDoc, pBURL);
            else
                hr = LoadDocumentSync(pDoc, pBURL);
        }
        else
        {
            if (fLocal)
            {
                FileStream* fs = new FileStream();
                pStm = (IStream*)fs;
                CHECKHR(fs->open(pBURL, false));
            }
            else
            {
                // Synchronously create a stream on an URL
                CHECKHR(CreateURLStream(pszFileName, &pStm));
            }
            hr = LoadDocumentStream(pDoc, pStm);
        }
    }
    else
    {
        hr = BuildDocument(pDoc); // load a document from in-memory string.
    }

    // Now walk the loaded XML document dumping the node names to stdout.
    if (fWalk)
    {
        CHECKHR(pDoc->QueryInterface(IID_IXMLDOMNode,(void**)&pNode));
        WalkTree(pNode,0);
    }

    //
    // Try to save it out. 
    // This will fail as designed, because IStream created by using URLOpenBlockingStream() is only used for downloading (ie, Read())
    //
    if (pBOutputName)
    {
        hr = SaveDocument(pDoc, pBOutputName);
    }
    else
    {
        // Test persistence of encoded XML doc in-memory via PBYTE buffer.
        PBYTE pData = NULL;
        ULONG ulLen;

        CHECKHR(PersistInMemory(pDoc, &pData, &ulLen));

        hr = LoadInMemory(pDoc, pData, ulLen);
        delete pData;
    }
    
CleanUp:
    SAFERELEASE(pDoc);
    SysFreeString(pBURL);
    SysFreeString(pBOutputName);
    SAFERELEASE(pStm);
    SAFERELEASE(pNode);

    CoUninitialize();

    return hr == 0 ? 0 : 1;
}
