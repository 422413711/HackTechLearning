#include "ntddk.h"

/**
 * ע������
 * ���ļ���������
 * ��ϵͳֱ���ṩ���ں�API����ע�����в����������ױ����
 * Ҳ�и��ײ��HIVE�ļ�����ע���ʽ
 */

 /**
  * �ں�API��ʽ
  */
#include "RegistryManage.h"
VOID TESTAPI()
{
	// ����ע����
	UNICODE_STRING ustrRegistry;
	RtlInitUnicodeString(&ustrRegistry, L"\\Registry\\Machine\\Software\\DemonGan");
	MyCreateRegistryKey(ustrRegistry);

	// ��ע����
	MyOpenRegistryKey(ustrRegistry);

	// ���ע����ֵ
	UNICODE_STRING ustrKeyValueName;
	WCHAR wstrKeyValueData[] = L"I am DemonGan";
	RtlInitUnicodeString(&ustrKeyValueName, L"Name");
	MySetRegistryKeyValue(ustrRegistry, ustrKeyValueName, REG_SZ, wstrKeyValueData, sizeof(wstrKeyValueData));

	// ��ѯע����ֵ
	MyQueryRegistryKeyValue(ustrRegistry, ustrKeyValueName);

	// ɾ��ע����ֵ
	MyDeleteRegistryKeyValue(ustrRegistry, ustrKeyValueName);

	// ɾ��ע����
	MyDeleteRegistryKey(ustrRegistry);
}

/**
 * HIVE�ļ���ʽ
 */
VOID TESTHIVE()
{
	//����һ����Ŀ��RegOpHIVE
}


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

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	DbgPrint("Enter DriverEntry\n");
	NTSTATUS status = STATUS_SUCCESS;
	DriverObject->DriverUnload = DriverUnload;
	for (ULONG i = 0; i < IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = DriverDefaultHandle;
	}

	//�ں�API��ʽ����ע���
	//TESTAPI();

	//HIVE�ļ���ʽ
	TESTHIVE();

	DbgPrint("Leave DriverEntry\n");
	return status;
}