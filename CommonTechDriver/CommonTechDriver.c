#include "ntddk.h"

/**
 * ����������ں˲㳣�ü���ʾ��
 * �����������ء��������ء����ײ��TDI��NDIS������ͨ��
 * �����ļ����������̱���������ǿɱ���ļ�ǿɾ
 */

 /**
  * ��PatchGuard��������
  * ͨ����DRIVER_OBJECT�ṹ��Զ�����в����Ƕ�����������ժ��ʵ����������
  * ��Ҫ�ƹ�PatchGuard������MiProcessLoaderEntryʵ��
  * PatchGuard���ݼ��ϵͳ�ϵ�һЩȫ���������жϹؼ��ڴ��Ƿ񱻸���
  * ��Mi��������ڲ����ժ��һ������ģ��ʱ��ͬʱ������PG��ص�ȫ�����ݣ������Ͳ��ᴥ��PG����������
  * 
  * ������ӻ�����  system thread exception not handled
  * ������dmp������־��������Ϣ�� Unable to load image \SystemRoot\system32\ntoskrnl.exe , Win32 error 0n2
  */
#include "EnumDriver.h"
VOID TESTDRIVERHIDE(PDRIVER_OBJECT pDriverObject)
{
	// ��������ģ��
	EnumDriver(pDriverObject);

	// ����ģ������(Bypass Patch Guard)
	UNICODE_STRING ustrDriverName;
	RtlInitUnicodeString(&ustrDriverName, L"MySYS.sys");
	HideDriver_Bypass_PatchGuard(pDriverObject, ustrDriverName);
}

/**
 * ��PG��������
 * ������������
 * ͨ���������̽ṹEPROCESS�еĻ����˫������ActiveProcessLinks��ʵ��ժ��
 * 
 * Ҳ��һ���Ļ������������ƹ�PG�ķ�ʽ��ʱ�ˣ���ʱ��һ��
 */
#include "EnumProcess.h"
VOID TESTPROCESSHIDE()
{
	// ��������
	EnumProcess();

	// ����ָ������(Bypass Patch Guard)
	HideProcess_Bypass_PatchGuard("InstDrv.exe");
}

/**
 * TDI����ͨ��
 * ������Զ�һЩ��������һ����Ŀ��TDINetDriver
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

	//��������
	//TESTDRIVERHIDE(pDriverObject);
	//���ؽ���
	//TESTPROCESSHIDE();

	DbgPrint("Leave CreateDevice\n");
	return status;
}