#include "ntddk.h"
#include "ntstrsafe.h"

/**
 * ����Ȩ�޵�ԭ�򣬴����û���Ķ�������봦���ں˲��ɱ��Կ��д�����Ȼ����
 * ����Ҳ�������ں�������
 * Rootkit��
 * һ������Ķ���������������ڰ�װĿ�������������ָ���ļ������̺��������ӵ�
 * һ��Ͷ��������ʹ�ã�ͨ������������������޸�ϵͳ�ں˴ﵽ����Ŀ��
 */

/**
 * �������ԱȽ��鷳
 * ����bcdedit����Ա����Ի��������ã�������msconfig�и߼�ѡ��򿪵��ԡ�����
 * ��������������ô������ԣ�ƻ��pd��������ò������ʾ�ģ����Լ�������ϣ���ھ��Ǵ�������ֳ����ģ�������ͬһ��com�ڣ��������Ի�Ϊ�ͻ��ˡ����Ի�Ϊ�����
 * һ��Ҫ�ر����˷���ǽ����Ȼ���ú���Ҳһֱ������
 * ���ɺ�ϵͳ�ܹ�Ҫ��Ӧ
 */

VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	if (DriverObject != NULL)
	{
		DbgPrint("[%ws]Driver Upload,Driver Object Address:%p", __FUNCTIONW__, DriverObject);
	}
	return;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	DbgPrint("[%ws]Hello Kernel World, CurrentProcessId = 0x%p , CurrentIRQL = 0x%u\n", __FUNCTIONW__, PsGetCurrentProcessId(), KeGetCurrentIrql());
	if (RegistryPath != NULL)
	{
		DbgPrint("[%ws]Driver RegistryPath:%wZ\n", __FUNCTIONW__, RegistryPath);
	}

	if (DriverObject != NULL)
	{
		DbgPrint("[%ws]Driver Object Address:%p\n", __FUNCTIONW__, DriverObject);
		DriverObject->DriverUnload = DriverUnload;
	}

	return STATUS_SUCCESS;
}