#include "StorageProperty.h"



StorageProperty::StorageProperty(LPCTSTR drivePath)
{
	//get handle for device
	hDevice = CreateFile(drivePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	//set input data structure
	ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
	storagePropertyQuery.PropertyId = StorageDeviceProperty;
	storagePropertyQuery.QueryType = PropertyStandardQuery;
}


StorageProperty::~StorageProperty()
{
}
