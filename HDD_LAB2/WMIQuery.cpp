#include "WMIQuery.h"


//Init COM library
BOOL WMIQuery::initCOM()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	return FAILED(hr);
}

WMIQuery::WMIQuery()
{
}


WMIQuery::~WMIQuery()
{
}
