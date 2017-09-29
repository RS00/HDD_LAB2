#include <iostream>
#include <string>
#include "StorageProperty.h"
#include "WMIQuery.h"
#include "HDDInfoPrinter.h"
using namespace std;


int main()
{	
	HDDInfoPrinter printer;
	printer.printModel();
	printer.printSerialNumber();
	printer.printFirmwareVersion();
	printer.printMemoryInfo();
	printer.printSupportedATAStandarts();
	printer.printSupportedMemoryAccessModes();
	system("pause");
	return 0;
}