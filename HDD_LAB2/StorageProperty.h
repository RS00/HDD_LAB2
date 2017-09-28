#pragma once
#include <Windows.h>
#include <atlstr.h>  
#include <ntddscsi.h>
#include <stdint.h>
#include <vector>
#define bufferSize 512

class StorageProperty
{
private:
	HANDLE hDevice;
	STORAGE_PROPERTY_QUERY storagePropertyQuery;
public:
	StorageProperty();
	BOOLEAN isPioUsed();
	int16_t getSupportedATA();
	int16_t getSupportedDMA();
	int16_t getSupportedUltraDMA();
	~StorageProperty();
};

