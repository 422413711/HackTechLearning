#ifndef _SSDT_FUNCTION_H_
#define _SSDT_FUNCTION_H_


#include <ntddk.h>
#include <ntimage.h>


#pragma pack(1)
typedef struct _SERVICE_DESCIPTOR_TABLE_32
{
	PULONG ServiceTableBase;		  // SSDT��ַ
	PULONG ServiceCounterTableBase;   // SSDT�з��񱻵��ô���������
	ULONG NumberOfService;            // SSDT�������
	PUCHAR ParamTableBase;		      // ϵͳ����������ַ
}SSDTEntry_32, *PSSDTEntry_32;
#pragma pack()

// ֱ�ӻ�ȡNtoskrnl.exe�������Ż�ȡ SSDT 
extern SSDTEntry_32 __declspec(dllimport) KeServiceDescriptorTable; //32λ���ܱ����

// ��ȡ SSDT ������ַ
PVOID GetSSDTFunction_32(PCHAR pszFunctionName);


#endif