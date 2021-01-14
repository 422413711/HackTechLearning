/**
 * WFP������
 */

#include "WFP_Network.h"

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	// ɾ���ص������͹�����,�ر�����
	WfpUnload();
}

NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING RegistryPath)
{
	DbgPrint("Enter DriverEntry\n");
	NTSTATUS status = STATUS_SUCCESS;

	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	// �����豸
	//CreateDevice(pDriverObject);

	// ����WFP
	WfpLoad(pDriverObject->DeviceObject);

	DbgPrint("Leave DriverEntry\n");
	return status;
}