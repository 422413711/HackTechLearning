#include "ntddk.h"
#include "ntstrsafe.h"

/**
 * ����Ȩ�޵�ԭ�򣬴����û���Ķ�������봦���ں˲��ɱ��Կ��д�����Ȼ����
 * ����Ҳ�������ں�������
 * Rootkit��
 * һ������Ķ���������������ڰ�װĿ�������������ָ���ļ������̺��������ӵ�
 * һ��Ͷ��������ʹ�ã�ͨ������������������޸�ϵͳ�ں˴ﵽ����Ŀ��
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

	WCHAR strBuf[128] = { 0 };

	UNICODE_STRING uFirstString = { 0 };
	RtlInitEmptyUnicodeString(&uFirstString, strBuf, sizeof(strBuf));
	RtlUnicodeStringCopyString(&uFirstString, L"Hello,Kernel\n"); //ֻ����PASSIVE_LEVEL��ʹ��
	DbgPrint("String:%wZ", &uFirstString);

	return STATUS_SUCCESS;
}