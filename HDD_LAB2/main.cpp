#include <iostream>
#include "StorageProperty.h"
#include "WMIQuery.h"
#include <string>
using namespace std;


int main()
{
	WMIQuery query;
	IEnumWbemClassObject* pEnumerator = NULL;
	vector<wstring> model = query.getInfo(pEnumerator, L"SELECT * FROM Win32_DiskDrive WHERE Index = '0'", L"Model");
	cout << "HDD Model:\n\t\t";
	for (int i = 0; i < model.size(); i++)
	{
		wcout << model.at(i) << endl;
	}

	vector<wstring> version = query.getInfo(pEnumerator, L"SELECT * FROM Win32_DiskDrive WHERE Index = '0'", L"FirmwareRevision");
	cout << "\nFirmware version:\n\t\t";
	for (int i = 0; i < version.size(); i++)
	{
		wcout << version.at(i) << endl;
	}

	vector<wstring> serial = query.getInfo(pEnumerator, L"SELECT * FROM Win32_DiskDrive WHERE Index = '0'", L"SerialNumber");
	cout << "\nSerial number:\n    ";
	for (int i = 0; i < serial.size(); i++)
	{
		wcout << serial.at(i) << endl;
	}

	vector<wstring> memory = query.getInfo(pEnumerator, L"SELECT * FROM Win32_LogicalDisk", L"Size");
	cout << "\nMemory:\n    ";
	long long total = 0;
	for (int i = 0; i < memory.size(); i++)
	{
		total += stoll(memory.at(i));
	}
	total /= 1048576;
	cout << "\t\tTotal: " << total << " MB";

	vector<wstring> free = query.getInfo(pEnumerator, L"SELECT * FROM Win32_LogicalDisk", L"FreeSpace");
	long long totalFree = 0;
	for (int i = 0; i < free.size(); i++)
	{
		totalFree += stoll(free.at(i));
	}
	totalFree /= 1048576;
	cout << "\n\t\tFree:  " << totalFree << " MB";
	cout << "\n\t\tUsed:  " << total - totalFree << " MB";

	cout << "\nSupported ATA standarts:";
	StorageProperty property;
	int16_t supportedATA = property.getSupportedATA();
	if (supportedATA & 0b00000000010000)
		cout << "\n\t\tATA/ATAPI-4";
	if (supportedATA & 0b00000000100000)
		cout << "\n\t\tATA/ATAPI-5";
	if (supportedATA & 0b00000001000000)
		cout << "\n\t\tATA/ATAPI-6";
	if (supportedATA & 0b00000010000000)
		cout << "\n\t\tATA/ATAPI-7";
	if (supportedATA & 0b00000100000000)
		cout << "\n\t\tATA8-ACS";

	cout << "\nSupported memory access modes:";

	if (property.isPioUsed())
		cout << "\n\t\tPIO\n";
	else
		cout << "\n\t\tDMA\n";
	
	int16_t supportedDMA = property.getSupportedDMA();
	if (supportedDMA & 0b00000000000001)
		cout << "\n\t\tMultiword DMA mode 0 is supported.\n";
	if (supportedDMA & 0b00000000000010)
		cout << "\t\tMultiword DMA mode 1 is supported.\n";
	if (supportedDMA & 0b00000000000100)
		cout << "\t\tMultiword DMA mode 2 is supported.\n";

	int16_t supportedUltraDMA = property.getSupportedUltraDMA();
	if (supportedUltraDMA & 0b00000000000001)
		cout << "\t\tUltra DMA mode 0 is supported.\n";
	if (supportedUltraDMA & 0b00000000000010)
		cout << "\t\tUltra DMA mode 1 is supported.\n";
	if (supportedUltraDMA & 0b00000000000100)
		cout << "\t\tUltra DMA mode 2 is supported.\n";
	if (supportedUltraDMA & 0b00000000001000)
		cout << "\t\tUltra DMA mode 3 is supported.\n";
	if (supportedUltraDMA & 0b00000000010000)
		cout << "\t\tUltra DMA mode 4 is supported.\n";
	if (supportedUltraDMA & 0b00000000100000)
		cout << "\t\tUltra DMA mode 5 is supported.\n";
	if (supportedUltraDMA & 0b00000001000000)
		cout << "\t\tUltra DMA mode 6 is supported.\n";
	system("pause");
	return 0;
}