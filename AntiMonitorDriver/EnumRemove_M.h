#ifndef _ENUM_REMOVE_M_H_
#define _ENUM_REMOVE_M_H_


#include <ntddk.h>


// �����ص�
BOOLEAN EnumNotifyRoutine_M();

// �Ƴ��ص�
NTSTATUS RemoveNotifyRoutine_M(PVOID pNotifyRoutineAddress);

// ��ȡ PspLoadImageNotifyRoutine �����ַ
PVOID GetPspLoadImageNotifyRoutine();

// �����������ȡ PspLoadImageNotifyRoutine �����ַ
PVOID SearchPspLoadImageNotifyRoutine(PUCHAR pSpecialData, ULONG ulSpecialDataSize);

// ָ���ڴ������������ɨ��
PVOID SearchMemory_M(PVOID pStartAddress, PVOID pEndAddress, PUCHAR pMemoryData, ULONG ulMemoryDataSize);


#endif