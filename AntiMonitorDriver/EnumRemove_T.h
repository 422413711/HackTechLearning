#ifndef _ENUM_REMOVE_T_H_
#define _ENUM_REMOVE_T_H_


#include <ntddk.h>


// �����ص�
BOOLEAN EnumNotifyRoutine_T();

// �Ƴ��ص�
NTSTATUS RemoveNotifyRoutine_T(PVOID pNotifyRoutineAddress);

// ��ȡ PspCreateThreadNotifyRoutine �����ַ
PVOID GetPspCreateThreadNotifyRoutine();

// �����������ȡ PspCreateThreadNotifyRoutine �����ַ
PVOID SearchPspCreateThreadNotifyRoutine(PUCHAR pFirstSpecialData, ULONG ulFirstSpecialDataSize, PUCHAR pSecondSpecialData, ULONG ulSecondSpecialDataSize);

// ָ���ڴ������������ɨ��
PVOID SearchMemory_T(PVOID pStartAddress, PVOID pEndAddress, PUCHAR pMemoryData, ULONG ulMemoryDataSize);


#endif