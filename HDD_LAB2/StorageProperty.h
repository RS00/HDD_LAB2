#pragma once
#include <Windows.h>
#include <atlstr.h>  

class StorageProperty
{
private:
	HANDLE hDevice;
	STORAGE_PROPERTY_QUERY storagePropertyQuery;
public:
	StorageProperty(LPCTSTR drivePath);
	BOOLEAN isPioUsed();
	~StorageProperty();
};

