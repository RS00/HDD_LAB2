#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "StorageProperty.h"
#include "WMIQuery.h"
using namespace std;

class HDDInfoPrinter
{
	WMIQuery query;
	IEnumWbemClassObject* pEnumerator = NULL;
public:
	void printModel();
	void printFirmwareVersion();
	void printSerialNumber();
	void printMemoryInfo();
	void printSupportedATAStandarts();
	void printSupportedMemoryAccessModes();
	HDDInfoPrinter();
	~HDDInfoPrinter();
};

