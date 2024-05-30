#ifndef _ADMINWRAP_H_
#define _ADMINWRAP_H_

#include <comadmin.h>

typedef enum
{
	APPLICATION=0,
	COMPONENT,
	SUBSCRIPTION,
	TRANSIENTSUB,
	PUBPROP,
	TRANSIENTPUBPROP,
} ADMINTYPE, *PADMINTYPE;


class CApp 
{
public:
	CApp();
	CApp(ICOMAdminCatalog*, WCHAR*);
	virtual ~CApp();
	HRESULT SetProperties(ICOMAdminCatalog*, WCHAR*);
	HRESULT CreateApp(BOOL fServer=FALSE, BOOL fQueued=FALSE);
	HRESULT DeleteApp();
	HRESULT InstallComponent(WCHAR* pwzcompdllname);
	HRESULT RemoveComponent(WCHAR* progid);
	HRESULT AddEventClass(WCHAR* pwzdllname, WCHAR* pwztlbpath, WCHAR* pwzCompName, WCHAR* pwzPublisherID,
						  WCHAR* pwzFilterCLSID, BOOL fAllowinproc, BOOL fFireinparallel);
	HRESULT AddSubscription(WCHAR* pwzProgID, WCHAR* pwzSubName, WCHAR* pwzECID, WCHAR* pwzPubID, WCHAR* pwzIID,
							WCHAR* pwzMethod, WCHAR* pwzCriteria, WCHAR* pwzPubProp, WCHAR* pwzPubVal);
	HRESULT RemoveSubscription(WCHAR* pwzProgID, WCHAR* pwzSubName);
	HRESULT AddTransientSubscription(WCHAR* pwzSubName, WCHAR* pwzECID, WCHAR* pwzPubID, WCHAR* pwzIID, IUnknown *punk,
			                         WCHAR* pwzMethod, WCHAR* pwzCriteria, WCHAR* pwzPubProp, WCHAR* pwzPubVal);
	HRESULT RemoveTransientSubscription(WCHAR* pwzName);
	HRESULT SetProperty(ADMINTYPE type, WCHAR* pwztypename, WCHAR* pwztypename2,
						WCHAR* pwzPropName, VARIANT& var);
	WCHAR*  GetAppName() {return m_pwzapp;}

private:
	WCHAR* m_pwzapp;
	ICOMAdminCatalog* m_pcat;
};


// Catalogue access functions
HRESULT GetObjectAndCollection(ICOMAdminCatalog* pICat, BSTR szCollName, BSTR szObjectName, ADMINTYPE type, ICatalogCollection** ppICol, ICatalogObject** ppIObj);
HRESULT GetObjectAndCollection(ICatalogCollection* pIParentColl, ICatalogObject* pIParentObject, BSTR szCollName, BSTR szObjectName, ADMINTYPE type, ICatalogCollection** ppICol, ICatalogObject** ppIObj);
HRESULT RemoveNamedObjectFromCollection(ICatalogCollection* pICol, BSTR szObjectName, ADMINTYPE type);
HRESULT GetNamedObjectFromCollection(ICatalogCollection* pICol, BSTR szObjName, ICatalogObject** ppICatObj, LONG* plIndex, ADMINTYPE type, BSTR bstrName=NULL);
HRESULT GetCollection(ICOMAdminCatalog* pICat, BSTR szCollName, ICatalogCollection** ppICol);
HRESULT GetCollection(ICatalogCollection* pIParentColl, ICatalogObject* pICatObj, BSTR szCollName, ICatalogCollection** ppICol);
HRESULT GetObjectNameProperty(ADMINTYPE type, BSTR* pbstr);
HRESULT SetStringProperty(ICatalogObject *pcat, BSTR bPROP, WCHAR* pval);
HRESULT SetIUnknownProperty(ICatalogObject *pcat, BSTR bPROP, IUnknown* punk);
HRESULT SetBoolProperty(ICatalogObject *pcat, BSTR bPROP, BOOL fFlag);


#if(0)
HRESULT CreateApplication(ICOMAdminCatalog* pICat, WCHAR* pappname);
HRESULT DeleteApplication(ICOMAdminCatalog* pICat, WCHAR* pwzappname);
HRESULT SetObjectProperty(ICOMAdminCatalog* pICat, WCHAR* pwzpropname, VARIANT &var, WCHAR* pwzappname, WCHAR* pwzcompname=NULL, 
						  WCHAR* pwzsubname=NULL, WCHAR* pwzsubpubpropname=NULL, WCHAR* pwzsubsubpropname=NULL);
HRESULT UninstallSubscription(ICOMAdminCatalog* pICat, WCHAR* pwzappname, WCHAR* pwzsubscribername, WCHAR* pwzsubscriptionname);
HRESULT InstallEventClass(ICOMAdminCatalog* pcat, WCHAR* pwzappname, WCHAR* pwztypelib);
HRESULT UninstallEventClass(ICOMAdminCatalog* pICat, WCHAR* wzApp, WCHAR* wzeventclassname);
HRESULT InstallSubscription(ICOMAdminCatalog* pICat, WCHAR* pwzappname, WCHAR* pwzsubscribername, 
							WCHAR* pwzsubdllname, WCHAR* pwzsubscriptionname, WCHAR* wzPubId, 
							WCHAR* wzEcID, WCHAR* wzIID, WCHAR* wzMethod, WCHAR* wzCriteria, 
							WCHAR* wzPubpropname, VARIANT &varpub);
HRESULT InstallTransientSubscription(ICOMAdminCatalog* pICat, WCHAR* pwzsubscriptionname, WCHAR* wzPubId, WCHAR* wzEcID, WCHAR* wzIID, 
									 WCHAR* wzMethod, IUnknown* punk, WCHAR* wzCriteria, WCHAR* wzPubpropname, VARIANT &varpub);

#endif




#endif
