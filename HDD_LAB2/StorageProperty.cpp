#include "StorageProperty.h"



StorageProperty::StorageProperty()
{

}

BOOLEAN StorageProperty::isPioUsed()
{
	_STORAGE_ADAPTER_DESCRIPTOR descriptor = {};
	HANDLE hDevice = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	DWORD read;
	ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
	storagePropertyQuery.PropertyId = StorageDeviceProperty;
	storagePropertyQuery.QueryType = PropertyStandardQuery;
	DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
		&storagePropertyQuery,
		sizeof(storagePropertyQuery),
		&descriptor,
		sizeof(descriptor),
		&read,
		NULL);
	CloseHandle(hDevice);
	return descriptor.AdapterUsesPio;
}



int16_t StorageProperty::getSupportedATA()
{
	DWORD dwBytes;
	BOOL  bResult;
	HANDLE hDevice = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	CONST BYTE identifyDataCommandId = 0xEC;
	UCHAR dataBuffer[bufferSize	+ sizeof(ATA_PASS_THROUGH_EX)] = { 0 };

	ATA_PASS_THROUGH_EX &ATA = *(ATA_PASS_THROUGH_EX *)dataBuffer;
	ATA.Length = sizeof(ATA);
	ATA.TimeOutValue = 10;
	ATA.DataBufferOffset = sizeof(ATA_PASS_THROUGH_EX);
	ATA.DataTransferLength = bufferSize;
	
	IDEREGS * ideRegs = (IDEREGS *)ATA.CurrentTaskFile;
	ideRegs->bCommandReg = identifyDataCommandId;
	ideRegs->bSectorCountReg = 1;
	ATA.AtaFlags = ATA_FLAGS_DATA_IN | ATA_FLAGS_DRDY_REQUIRED;

	bResult = DeviceIoControl(hDevice, IOCTL_ATA_PASS_THROUGH, &ATA,
		sizeof(dataBuffer), &ATA,
		sizeof(dataBuffer), &dwBytes, 0);

	if (bResult == FALSE) {
		return bResult;
	}

	WORD *data = (WORD *)(dataBuffer + sizeof(ATA_PASS_THROUGH_EX));
	int16_t ataSupportBits = data[80];
	CloseHandle(hDevice);
	return ataSupportBits;
}



StorageProperty::~StorageProperty()
{
}
