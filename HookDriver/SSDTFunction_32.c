#include "SSDTFunction_32.h"
#include "SSDTFunctionIndex.h"

// ��ȡ SSDT ������ַ
PVOID GetSSDTFunction_32(PCHAR pszFunctionName)
{
	UNICODE_STRING ustrDllFileName;
	ULONG ulSSDTFunctionIndex = 0;
	PVOID pFunctionAddress = NULL;

	RtlInitUnicodeString(&ustrDllFileName, L"\\??\\C:\\Windows\\System32\\ntdll.dll");
	// �� ntdll.dll �л�ȡ SSDT ����������
	ulSSDTFunctionIndex = GetSSDTFunctionIndex(ustrDllFileName, pszFunctionName);

	// ����������, ��SSDT���л�ȡ��Ӧ������ַ
	pFunctionAddress = (PVOID)KeServiceDescriptorTable.ServiceTableBase[ulSSDTFunctionIndex];

	// ��ʾ
	DbgPrint("[%s][Index:%d][Address:0x%p]\n", pszFunctionName, ulSSDTFunctionIndex, pFunctionAddress);

	return pFunctionAddress;
}

