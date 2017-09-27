#pragma once
#include <windows.h>
#include <Wbemidl.h>
#include <comdef.h>
#include <vector>
using namespace std;

#pragma comment(lib, "wbemuuid.lib")
class WMIQuery
{
private:
	IWbemLocator *pLoc = NULL;
	IWbemServices *pSvc = NULL;
	//Init COM library
	BOOL initCOM();
	//Set general COM security levels
	BOOL coInitSecurity();
	//Obtain the initial locator
	BOOL obtainLocator();
	//Connect to WMI
	BOOL connectToWMI();
	//Set proxy security levels
	BOOL setProxySecurity();
public:
	vector<wstring> getInfo(IEnumWbemClassObject*, LPCWSTR req, LPCWSTR property);
	WMIQuery();
	~WMIQuery();
};

