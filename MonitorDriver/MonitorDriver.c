
/**
 * ��ؼ���
 * 64λϵͳ�µ�Patch Guardʹ�����ͨ���޸�ϵͳ�ؼ��ڴ����ݵ�HOOK����ʧЧ
 * ΢���ǵ��û�����Ŀ����������˷�����õ�ϵͳ�ص�API����
 * �������ǣ��������̡�ģ����ء�ע�������ص���
 * ������������󣬲��ұ��Լ���HOOK���ӵײ���ȶ�
 */

#include "LoadImageNotify.h" //ģ����

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
 * PsSetLoadImageNotifyRoutine
 * ����������ͨ��ģ����ػص���ʵ�ֽ���ע�룬ͨ���޸�PE�ṹ�ĵ�������DLL��ʵ��DLLע��
 * �����Ծܾ��ض��������أ�����ܾ�ɱ��������������������ļ���
 *
 * ������ص��������յ�������Ϣʱ��ģ�����Ѿ�������ɵģ����Բ���ֱ�ӿ��Ƹù���
 * ������ͨ���Զ��巽��ж���Ѿ����ص�ģ��
 *
 * ж��ģ���˼·��
 * ��������ģ�飬ֱ������ڵ㺯��DriverEntry�з���NTSTATUS�����룬�����Ѽ��ص������ͻ�����˳���������������ʧ��
 * ����DLLģ�飬DllMain��ں����޷�ȷ��DLL�Ƿ���سɹ���ͨ���ں�API����MmUnmapViewOfSection����ж���Ѽ���ģ��
 *
 * ���⣬�����ؽ���ģ���ʱ��ϵͳ����һ���ڲ�����Ϊ�˱������������ػص�����ʱ�����ܽ���ӳ�䡢���䡢��ѯ���ͷŵȲ���
 * ��ж��DLLģ�飬����Ƚ���������ģ�������ϲ��ܲ�����������Ҫ�������߳��ӳٵȴ�
 */
 //#include "LoadImageNotify.h" ��ǰ��
NTSTATUS TESTMODULE()
{
	return SetNotifyRoutine();
}

/**
 * ע�����
 * CmRegisterCallback
 * ����ͨ�����ûص���������ֵ�����п����Ƿ�����ָ�����Ĳ���
 * ����������ΪSTATUS_SUCCESS
 */
#include "NotifyRoutine_Reg.h"
VOID TESTREG()
{
	// ���ûص�����
	SetRegisterCallback();
}

/**
 * ������
 * �����������������������ɱ����û�ǿ�ƽ���
 * �ڽ�������ʱ�����ȶ���Ҫ�򿪵Ľ��̻�ȡ���̾��
 * �Դˣ�����ʹϵͳ��ȡ���ʧ�ܣ�ʵ�ֽ��̱���
 */
#include "NotifyRoutine_Obj.h"
VOID TESTOBJ(PDRIVER_OBJECT pDriverObject)
{
	// ��̷�ʽ�ƹ�ǩ�����
	BypassCheckSign(pDriverObject);

	// ���ý��̻ص�����
	SetProcessCallbacks();

	// �����̻߳ص�����
	SetThreadCallbacks();
}

/**
 * �ļ���غ���������������Ŀ��
 * 
 * �����ļ����ʹ����Minifilter��ܣ�VS�����ֳ�ģ�壬��������Ŀ��MonitorFileDriver
 * 
 * ��������Ҫʹ��WFP��ܣ�VISTA֮���ϵͳ��ϵͳ����ǽ�Ĺ��˹��Ӳ������ã�������WFP
 * ����������ʱWFP�����������������TCP/IP���ݣ���������Ŀ��MonitorNetDriver
 */


VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	// ɾ�����̼�ػص�����
	//RemoveProcessNotifyRoutine();

	// �Ƴ�ģ���ػص�
	//RemoveNotifyRoutine();

	// ɾ��ע����ػص�����
	//RemoveRegisterCallback();

	// ɾ�������ػص�����
	RemoveProcessCallbacks();
	// ɾ�������� �̻߳ص�����
	RemoveThreadCallbacks();
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
	//TESTPROCESS(pDriverObject);

	//ģ����
	//status = TESTMODULE();

	//ע�����
	//TESTREG();

	//������
	TESTOBJ(pDriverObject);

	DbgPrint("Leave DriverEntry\n");
	return status;
}