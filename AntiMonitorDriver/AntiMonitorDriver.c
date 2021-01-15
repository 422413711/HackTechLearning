#include "ntddk.h"

/**
 * ����ؼ���
 * ��������ɱ�����м�ز���
 * ���໥�Կ��У����Ա���ժ���Է��ļ�ػص�
 */

 /**
  * �����̼��
  * PsSetCreateProcessNotifyRoutine�ص�����������һ����ΪPspCreateProcessNotifyRoutine��������
  * �������¼�����н��̴����ص������ļ��ܵ�ַ����Ҫ���ܺ��ȡ��ȷ�ĺ�����ַ
  */
#include "EnumRemove.h"
VOID TESTANTIPROCESS()
{
	//�����ص�����
	EnumNotifyRoutine();
}

/**
 * ���̼߳��
 * �뷴��������
 */
#include "EnumRemove_T.h"
VOID TESTANTITHREAD()
{
	//�����̻߳ص�
	EnumNotifyRoutine_T();
}

/**
 * ��ģ����
 * �뷴��������
 */
#include "EnumRemove_M.h"
VOID TESTANTIMODULE()
{
	EnumNotifyRoutine_M();
}

/**
 * ��ע�����
 * ע���ص������洢��һ����ΪCallbackListHead��ͷ��˫������ṹ��
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

	//�����̼��
	TESTANTIPROCESS();

	//


	DbgPrint("Leave CreateDevice\n");
	return status;
}