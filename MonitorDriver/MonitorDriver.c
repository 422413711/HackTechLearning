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
  */

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegPath)
{
	DbgPrint("Enter DriverEntry\n");
	NTSTATUS status = STATUS_SUCCESS;

	//

	DbgPrint("Leave DriverEntry\n");
	return status;
}