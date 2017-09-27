#include "WMIQuery.h"


//Init COM library
BOOL WMIQuery::initCOM()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	return !FAILED(hr);
}

//Set general COM security levels
BOOL WMIQuery::coInitSecurity()
{
	HRESULT hres = CoInitializeSecurity(
		NULL,
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
	);
	BOOL failed = FAILED(hres);
	if (failed)
	{
		CoUninitialize();
	}
	return !failed;
}
//Obtain the initial locator
BOOL WMIQuery::obtainLocator()
{
	HRESULT hres = CoCreateInstance(CLSID_WbemLocator, 0,
		CLSCTX_INPROC_SERVER, IID_IWbemLocator, 
		(LPVOID *)&pLoc);
	BOOL failed = FAILED(hres);
	if (failed)
	{
		CoUninitialize();
	}
	return !failed;
}
//Connect to WMI
BOOL WMIQuery::connectToWMI()
{
	HRESULT hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
		NULL,                    // Current user
		NULL,                    // Current password
		0,                       // Locale. NULL indicates current
		NULL,                    // Security flags.
		0,                       // Authority
		0,                       // Context object 
		&pSvc                    // pointer to IWbemServices proxy
	);
	BOOL failed = FAILED(hres);
	if (failed)
	{
		pLoc->Release();
		CoUninitialize();
	}
	return !failed;
}

BOOL WMIQuery::setProxySecurity()
{
	HRESULT hres = CoSetProxyBlanket(
		pSvc,                        // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
		NULL,                        // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
		NULL,                        // client identity
		EOAC_NONE                    // proxy capabilities 
	);
	BOOL failed = FAILED(hres);
	if (failed)
	{
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
	}
	return !failed;
}

LPCWSTR WMIQuery::getInfo(IEnumWbemClassObject *pEnumerator, LPCWSTR req, LPCWSTR property)
{
	if (!initCOM() || !coInitSecurity() || !obtainLocator() || !connectToWMI() || !setProxySecurity())
		return NULL;
	HRESULT hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(req),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hres))
		return NULL;
	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;
	HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

	if (uReturn == 0)
	{
		return NULL;
	}

	VARIANT vtProp;

	// Get the value 
	hr = pclsObj->Get(property, 0, &vtProp, 0, 0);
	VariantClear(&vtProp);
	pclsObj->Release();
	return 	vtProp.bstrVal;

}

WMIQuery::WMIQuery()
{
}


WMIQuery::~WMIQuery()
{
}
