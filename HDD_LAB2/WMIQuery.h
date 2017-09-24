#pragma once
#include <windows.h>
#include <Wbemidl.h>
using namespace std;

#pragma comment(lib, "wbemuuid.lib")
class WMIQuery
{
private:
	//Init COM library
	BOOL initCOM();
public:
	WMIQuery();
	~WMIQuery();
};

