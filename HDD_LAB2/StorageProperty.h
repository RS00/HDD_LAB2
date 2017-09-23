#pragma once
#include <Windows.h>

class StorageProperty
{
private:
	HANDLE hDevice;
	STORAGE_PROPERTY_QUERY storagePropertyQuery;
public:
	StorageProperty(LPCTSTR drivePath);
	~StorageProperty();
};

