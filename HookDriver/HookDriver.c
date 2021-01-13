
/**
 * ��32λϵͳ�У�RootKit���ʾ���Hook���������������ɱ��Կ�������ҹ����ײ�ĺ���������
 * ��64λϵͳ�У�Patch Guard�������ϵͳ�ؼ��ڴ���м�⣬������ڴ����ݱ��������򴥷���������
 * �����HOOK���ǻ����޸�ϵͳ�ڴ棬��������64λϵͳ�������ƹ�����
 * �ں���HOOK�����ࣺܶ
 * SSDT������������IAT��EAT��GDT��
 */

 /**
  * SSDT HOOK
  * System Services Descriptor Table ϵͳ������������
  * �����ǰ��û���Ring3��Win32API�������ں˲�Ring0���ں�API������ϵ����
  * Ring3��һЩ�������ն�Ӧ��ntdll.dll��һ��NtXXX����
  * ����CreateFile������NtCreateFile����ϵͳ����ŷ���EAX��Ȼ�����ϵͳ����ַ�����KiSystemServices�����ں�
  * ������Ring0��ͨ�������EAXϵͳ����ţ����������ţ��õ���Ӧϵͳ�����ں˵�ַ
  *
  * ͨ���޸������ַ������ĺ�����ַ���ԶԳ��ú������йҹ����Ӷ����˻���һЩ����ϵͳ����
  */

#include "SSDTHook.h" //ʹ����ntifs.h��Ҫ������ǰ������
VOID TESTSSDT_HOOK()
{
	SSDTHook();
}

#include "SSDTFunctionIndex.h"
  //��ȡSSDT����������
VOID TESTSSDT_INDEX()
{
	// �� ntdll.dll �л�ȡ SSDT ����������
	UNICODE_STRING ustrDllFileName;
	RtlInitUnicodeString(&ustrDllFileName, L"\\??\\C:\\Windows\\System32\\ntdll.dll");
	ULONG ulSSDTFunctionIndex = GetSSDTFunctionIndex(ustrDllFileName, "ZwOpenProcess");
	DbgPrint("ZwOpenProcess[%d]\n", ulSSDTFunctionIndex);
}
//��ȡ SSDT ������ַ
#ifdef _WIN64
#include "SSDTFunction_64.h"
#else
#include "SSDTFunction_32.h"
#endif
VOID TESTSSDT_FUNC()
{
#ifdef _WIN64
	GetSSDTFunction_64("NtOpenProcess");
#else
	GetSSDTFunction_32("NtOpenProcess");
#endif
}
//ͷ�ļ������ŵ���ǰ��ȥ�ˣ���Ȼ�����ض����ͻ
VOID TESTSSDT()
{
	//TESTSSDT_INDEX();
	//TESTSSDT_FUNC();
	TESTSSDT_HOOK();
}

/**
 * ��������
 * �ں˲��£����԰Ѱ�����¼���ķǳ��ײ㣬�����ƹ����������������¼��������
 * ����ѧϰһ�����̹�������������IRP HOOK
 */
VOID TESTFILTER()
{
	//����϶࣬��һ����Ŀ��Ū������HookKeyBoardDriver
}



VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	//ȡ��SSDTHOOK
	SSDTUnhook();
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

	//SSDT HOOK
	//TESTSSDT();

	//����
	TESTFILTER();

	DbgPrint("Leave DriverEntry\n");
	return status;
}