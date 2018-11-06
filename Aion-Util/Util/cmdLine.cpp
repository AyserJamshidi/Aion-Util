#include <windows.h>
#include <stdio.h>
#include <qdebug.h>
#include <Wbemidl.h>
#include <assert.h>

#include "cmdLine.h"

#pragma comment(lib, "wbemuuid.lib")

HRESULT hr = 0;
IWbemLocator         *WbemLocator = NULL;
IWbemServices        *WbemServices = NULL;
IEnumWbemClassObject *EnumWbem = NULL;

typedef NTSTATUS(NTAPI *_NtQueryInformationProcess)(
	HANDLE ProcessHandle,
	DWORD ProcessInformationClass,
	PVOID ProcessInformation,
	DWORD ProcessInformationLength,
	PDWORD ReturnLength
	);

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _PROCESS_BASIC_INFORMATION {
	LONG ExitStatus;
	PVOID PebBaseAddress;
	ULONG_PTR AffinityMask;
	LONG BasePriority;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR ParentProcessId;
} PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;

PVOID GetPebAddress(HANDLE ProcessHandle) {
	_NtQueryInformationProcess NtQueryInformationProcess =
		(_NtQueryInformationProcess)GetProcAddress(
			GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
	PROCESS_BASIC_INFORMATION pbi;

	NtQueryInformationProcess(ProcessHandle, 0, &pbi, sizeof(pbi), NULL);

	return pbi.PebBaseAddress;
}

cmdLine::cmdLine(void) {
	qDebug() << "Constructor init.";
	hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&WbemLocator);
	hr = WbemLocator->ConnectServer(L"ROOT\\CIMV2", NULL, NULL, NULL, 0, NULL, NULL, &WbemServices);
	hr = CoSetProxyBlanket(WbemServices, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
}

cmdLine::~cmdLine(void) {
	qDebug() << "Destructor init.";
}

std::vector<std::wstring> cmdLine::GetCommandLines() {
	/*HRESULT hr = 0;
	IWbemLocator         *WbemLocator = NULL;
	IWbemServices        *WbemServices = NULL;
	IEnumWbemClassObject *EnumWbem = NULL;*/

	hr = WbemServices->ExecQuery(L"WQL", L"SELECT ProcessId,CommandLine FROM Win32_Process WHERE name = \"Aion.bin\"", WBEM_FLAG_FORWARD_ONLY, NULL, &EnumWbem);

	qDebug() << "WE IN THERE.";

	std::vector<std::wstring> returnData;
	if(EnumWbem != NULL) {
		IWbemClassObject *result = NULL;
		ULONG returnedCount = 0;
		int currentCount = 0;



		while(hr = EnumWbem->Next(WBEM_INFINITE, 1, &result, &returnedCount) == S_OK) {
			VARIANT ProcessId;
			VARIANT CommandLine;

			// access the properties
			hr = result->Get(L"ProcessId", 0, &ProcessId, 0, 0);
			hr = result->Get(L"CommandLine", 0, &CommandLine, 0, 0);
			if(!(CommandLine.vt == VT_NULL)) {
				//wprintf(L"%u  %s \r\n", ProcessId.uintVal, CommandLine.bstrVal);
				//assert(CommandLine.bstrVal != nullptr);
				std::wstring ws(CommandLine.bstrVal, SysStringLen(CommandLine.bstrVal));

				//qDebug() << "id = " << ProcessId.uintVal << " and cmd = " << ws;

				returnData.push_back(std::to_wstring(ProcessId.uintVal));
				returnData.push_back(ws);

				SysReleaseString((BSTR)CommandLine.bstrVal); // Leave this here to prevent memory leak.  Need to release CommandLine as BSTR.
				currentCount++;
			}

			result->Release();
		}
	}

	// Cleanup
	// ========*/
	//WbemLocator->Release();
	//WbemServices->Release();
	EnumWbem->Release();

	//CoUninitialize();


	//getchar();
	//hr = NULL;
	return returnData;
}

bool cmdLine::cleanUp() {
	try {
		// Cleanup
		WbemLocator->Release();
		WbemServices->Release();

		CoUninitialize();

		//getchar();
		hr = NULL;
		return true;
	} catch(...) {
		qDebug() << "An error has occured.";
	}
	return false;
}

/*BOOL sm_EnableTokenPrivilege(LPCTSTR pszPrivilege) {
	HANDLE hToken = 0;
	TOKEN_PRIVILEGES tkp = {0};

	// Get a token for this process.

	if(!OpenProcessToken(GetCurrentProcess(),
						 TOKEN_ADJUST_PRIVILEGES |
						 TOKEN_QUERY, &hToken)) {
		return FALSE;
	}

	// Get the LUID for the privilege. 

	if(LookupPrivilegeValue(NULL, pszPrivilege,
							&tkp.Privileges[0].Luid)) {
		tkp.PrivilegeCount = 1;  // one privilege to set    

		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		// Set the privilege for this process. 

		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
			(PTOKEN_PRIVILEGES)NULL, 0);

		if(GetLastError() != ERROR_SUCCESS)
			return FALSE;

		return TRUE;
	}

	return FALSE;
}*/