#include "ntddk.h"

/**
 * ��ؼ���
 * 64λϵͳ�µ�Patch Guardʹ�����ͨ���޸�ϵͳ�ؼ��ڴ����ݵ�HOOK����ʧЧ
 * ΢���ǵ��û�����Ŀ����������˷�����õ�ϵͳ�ص�API����
 * �������ǣ��������̡�ģ����ء�ע�������ص���
 * ������������󣬲��ұ��Լ���HOOK���ӵײ���ȶ�
 */

 /**
  * ���̴������
  * PsSetCreateProccessNotifyRoutineEx
  * ����������������ʱ����Ҫ�����ǿ��������ǩ�����������ʧ��
  * ǿ�������Լ����ȷ�����ڼ��صĶ������ļ��ڼ���ǰ��Ҫǩ���Ĳ���
  * IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY��־������ʱͨ��ʹ��/integritycheck��������־��PE��ͷ�н�������
  * 
  * ���������ÿ���ͨ��VS����ҳ��������������ѡ������/INTEGRITYCHECK
  * 
  * �������ô��������ã�ͨ���о����֣��ں�ͨ��MmVerifyCallbackFunction��֤���ƺ��������Ƿ�Ϸ�
  * ���˺���ֻ�Ǽ���֤��DriverObject->DriverSection->Flagsֵ�Ƿ����0x20
  * ����ֻҪ�Ѹñ�־��λ��0x20����
  */
#include "NotifyRoutine.h"
VOID TESTPROCESS(PDRIVER_OBJECT pDriverObject)
{
	// ��̷�ʽ�ƹ�ǩ�����
	BypassCheckSign(pDriverObject);

	// ���ûص�����
	SetProcessNotifyRoutine();
}

/**
 * ģ����ؼ��
 */
VOID TESTMODULE()
{

}

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	// ɾ�����̼�ػص�����
	RemoveProcessNotifyRoutine();
}


NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");
	NTSTATUS status = STATUS_SUCCESS;
	pDriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		pDriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	//���̼��
	TESTPROCESS(pDriverObject);

	//

	DbgPrint("Leave DriverEntry\n");
	return status;
}