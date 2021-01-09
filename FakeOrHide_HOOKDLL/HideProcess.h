#ifndef _HIDE_PROCESS_H_
#define _HIDE_PROCESS_H_


#include <Windows.h>
#include <Winternl.h>

//HOOK��������Ҫ��WINAPI������Ĭ��ʹ��C���Ե���Լ���������ں������ع����У����ջ��ƽ�������
typedef NTSTATUS(WINAPI* typedef_ZwQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);


NTSTATUS New_ZwQuerySystemInformation(
	SYSTEM_INFORMATION_CLASS SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
);


void HookApi();

void UnhookApi();

#endif