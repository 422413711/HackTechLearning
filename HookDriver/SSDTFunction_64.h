#ifndef _SSDT_FUNCTION_H_
#define _SSDT_FUNCTION_H_


#include <ntddk.h>
#include <ntimage.h>


#pragma pack(1)
typedef struct _SERVICE_DESCIPTOR_TABLE_64
{
	PULONG ServiceTableBase;		  // SSDT��ַ
	PVOID ServiceCounterTableBase; // SSDT�з��񱻵��ô���������
	ULONGLONG NumberOfService;     // SSDT�������
	PVOID ParamTableBase;		  // ϵͳ����������ַ
}SSDTEntry_64, *PSSDTEntry_64;
#pragma pack()


// ��ȡ SSDT ������ַ
PVOID GetSSDTFunction_64(PCHAR pszFunctionName);

// ����������, �� KiSystemCall64 �л�ȡ SSDT ��ַ
PVOID GetSSDTAddress();


#endif