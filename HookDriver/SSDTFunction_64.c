#include "SSDTFunction_64.h"
#include "SSDTFunctionIndex.h"

// ��ȡ SSDT ������ַ
PVOID GetSSDTFunction_64(PCHAR pszFunctionName)
{
	UNICODE_STRING ustrDllFileName;
	ULONG ulSSDTFunctionIndex = 0;
	PVOID pFunctionAddress = NULL;
	PSSDTEntry_64 pServiceDescriptorTable = NULL;
	ULONG ulOffset = 0;

	RtlInitUnicodeString(&ustrDllFileName, L"\\??\\C:\\Windows\\System32\\ntdll.dll");
	// �� ntdll.dll �л�ȡ SSDT ����������
	ulSSDTFunctionIndex = GetSSDTFunctionIndex(ustrDllFileName, pszFunctionName);

	// ����������, �� KiSystemCall64 �л�ȡ SSDT ��ַ
	pServiceDescriptorTable = GetSSDTAddress();

	// ����������, ��SSDT���л�ȡ��Ӧ����ƫ�Ƶ�ַ�������������ַ
	ulOffset = pServiceDescriptorTable->ServiceTableBase[ulSSDTFunctionIndex] >> 4;
	pFunctionAddress = (PVOID)((PUCHAR)pServiceDescriptorTable->ServiceTableBase + ulOffset);

	// ��ʾ
	DbgPrint("[%s][SSDT Addr:0x%p][Index:%d][Address:0x%p]\n", pszFunctionName, pServiceDescriptorTable, ulSSDTFunctionIndex, pFunctionAddress);

	return pFunctionAddress;
}


// ����������, �� KiSystemCall64 �л�ȡ SSDT ��ַ
PVOID GetSSDTAddress()
{
	PVOID pServiceDescriptorTable = NULL;
	PVOID pKiSystemCall64 = NULL;
	UCHAR ulCode1 = 0;
	UCHAR ulCode2 = 0;
	UCHAR ulCode3 = 0;
	// ע��ʹ���з�������
	LONG lOffset = 0;

	// ��ȡ KiSystemCall64 ������ַ
	pKiSystemCall64 = (PVOID)__readmsr(0xC0000082);
	// ���������� 4C8D15
	for (ULONG i = 0; i < 1024; i++)
	{
		// ��ȡ�ڴ�����
		ulCode1 = *((PUCHAR)((PUCHAR)pKiSystemCall64 + i));
		ulCode2 = *((PUCHAR)((PUCHAR)pKiSystemCall64 + i + 1));
		ulCode3 = *((PUCHAR)((PUCHAR)pKiSystemCall64 + i + 2));
		// �ж�
		if (0x4C == ulCode1 &&
			0x8D == ulCode2 &&
			0x15 == ulCode3)
		{
			// ��ȡƫ��
			lOffset = *((PLONG)((PUCHAR)pKiSystemCall64 + i + 3));
			// ����ƫ�Ƽ����ַ
			pServiceDescriptorTable = (PVOID)(((PUCHAR)pKiSystemCall64 + i) + 7 + lOffset);
			break;
		}
	}

	return pServiceDescriptorTable;
}

