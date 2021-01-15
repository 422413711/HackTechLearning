#include "ntddk.h"

/**
 * ����������ں˲㳣�ü���ʾ��
 * �����������ء��������ء����ײ��TDI��NDIS������ͨ��
 * �����ļ����������̱���������ǿɱ���ļ�ǿɾ
 */

 /**
  * ��PatchGuard��������
  */


VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
}

NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT pDriverObject, _In_ PUNICODE_STRING RegistryPath)
{
	DbgPrint("Enter CreateDevice\n");
	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	//


	DbgPrint("Leave CreateDevice\n");
	return status;
}