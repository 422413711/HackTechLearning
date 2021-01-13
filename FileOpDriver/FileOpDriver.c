/**
 * �ļ�����һֱ�Ǹ���ǳ���Ҫ�Ĳ���
 * �������Ҳͬ����Ҫ
 * ���������ں��µ��ļ���������һ����һ�����ײ�
 * �ֱ��ǣ�
 * �ں�API
 * ������������������I/O Request Package��������IRP�������ļ�
 * �����ļ�ϵͳ��ʽNTFS������Ӳ�̶���������
 */

 /**
  * Zw��ͷ�ļ�����API
  */
#include "FileManage.h"


VOID TestKernelAPI()
{
	// ����Ŀ¼
	UNICODE_STRING ustrDirectory;
	RtlInitUnicodeString(&ustrDirectory, L"\\??\\C:\\MyCreateFolder"); //��������·����ʽ��������֮ǰ����Դ���������Ƴ�����·��ǰ����Ǵ�������??
	MyCreateFileFolder(ustrDirectory);

	// �����ļ�
	UNICODE_STRING ustrCreateFile;
	RtlInitUnicodeString(&ustrCreateFile, L"\\??\\C:\\MyCreateFolder\\MyCreateFile.txt");
	MyCreateFile(ustrCreateFile);

	// ɾ���ļ�
	UNICODE_STRING ustrDeleteFile;
	RtlInitUnicodeString(&ustrDeleteFile, L"\\??\\C:\\MyCreateFolder\\MyCreateFile.txt");
	MyDeleteFileOrFileFolder(ustrDeleteFile);

	// ɾ����Ŀ¼
	UNICODE_STRING ustrDeleteFilder;
	RtlInitUnicodeString(&ustrDeleteFilder, L"\\??\\C:\\MyCreateFolder\\Test");
	MyDeleteFileOrFileFolder(ustrDeleteFilder);

	// ��ȡ�ļ���С
	UNICODE_STRING ustrFileSize;
	RtlInitUnicodeString(&ustrFileSize, L"\\??\\C:\\MyCreateFolder\\MyCreateFile.txt");
	ULONG64 ullFileSize = MyGetFileSize(ustrFileSize);
	DbgPrint("FileSize = %I64d Bytes\n", ullFileSize);

	// ������Ŀ¼
	UNICODE_STRING ustrOldFilder, ustrNewFilder;
	RtlInitUnicodeString(&ustrOldFilder, L"\\??\\C:\\MyCreateFolder\\Test");
	RtlInitUnicodeString(&ustrNewFilder, L"\\??\\C:\\MyCreateFolder\\TestRename");
	MyRenameFileOrFileFolder(ustrOldFilder, ustrNewFilder);

	// �������ļ�
	UNICODE_STRING ustrOldFile, ustrNewFile;
	RtlInitUnicodeString(&ustrOldFile, L"\\??\\C:\\MyCreateFolder\\MyCreateFile.txt");
	RtlInitUnicodeString(&ustrNewFile, L"\\??\\C:\\MyCreateFolder\\MyCreateFileRename.txt");
	MyRenameFileOrFileFolder(ustrOldFile, ustrNewFile);

	// �����ļ��к��ļ�
	UNICODE_STRING ustrQueryFile;
	RtlInitUnicodeString(&ustrQueryFile, L"\\??\\C:\\MyCreateFolder");
	MyQueryFileAndFileFolder(ustrQueryFile);

	// �ļ�����
	UNICODE_STRING ustrScrFile, ustrDestFile;
	RtlInitUnicodeString(&ustrScrFile, L"\\??\\C:\\MyCreateFolder\\MyCreateFile.txt");
	RtlInitUnicodeString(&ustrDestFile, L"\\??\\C:\\MyCreateFolder\\MyCreateFile-Copy.txt");
	MyCopyFile(ustrScrFile, ustrDestFile);

}

/**
 * �ļ�����֮IRP
 * �û�����ͨ������API�����ļ��������漰Win32API��Native API��File System�Լ�Filter Driver�Ȳ��
 * ɱ��Ͷ�������ڸ�����ζ����ڣ��Բ������й��˺ͼ��
 * ����FSD���ļ�API��������Native API�󵽴�������
 * �����������ģ�����ϵͳ��FSD����IRP�������ļ����ƹ�������FSD�����API HOOK�ȼ�س���
 */
#include "IrpFile.h"
#include "FileManageWithIrp.h"
#define DEV_NAME L"\\Device\\IRP_FILE_DEV_NAME"
#define SYM_NAME L"\\DosDevices\\IRP_FILE_SYM_NAME"
#define IOCTL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
VOID TESTIRP()
{
	// �����ļ�
	UNICODE_STRING ustrCreateFile;
	RtlInitUnicodeString(&ustrCreateFile, L"C:\\TEST.txt");
	IRP_MyCreateFile(ustrCreateFile);
	DbgPrint("Create File OK.\n");

	// ��ȡ�ļ���С
	UNICODE_STRING ustrFileSize;
	RtlInitUnicodeString(&ustrFileSize, L"C:\\TEST.exe");
	ULONG64 ullFileSize = IRP_MyGetFileSize(ustrFileSize);
	DbgPrint("FileSize = %I64d Bytes\n", ullFileSize);

	// �����ļ���������
	UNICODE_STRING ustrHideFile;
	RtlInitUnicodeString(&ustrHideFile, L"C:\\TEST.exe");
	IRP_MyHideFile(ustrHideFile);
	DbgPrint("Hide File OK.\n");

	// �����ļ��к��ļ�
	UNICODE_STRING ustrQueryFile;
	RtlInitUnicodeString(&ustrQueryFile, L"C:\\");
	IRP_MyQueryFileAndFileFolder(ustrQueryFile);
	DbgPrint("Query File OK.\n");

	// �ļ�����д��
	UNICODE_STRING ustrWriteFile;
	LARGE_INTEGER liWriteOffset = { 0 };
	UCHAR szWriteData[256] = "Who Are You? I am Demon`Gan.";
	ULONG ulWriteDataLength = 1 + strlen(szWriteData);
	RtlInitUnicodeString(&ustrWriteFile, L"C:\\TEST.txt");
	IRP_MyWriteFile(ustrWriteFile, liWriteOffset, szWriteData, &ulWriteDataLength);
	DbgPrint("MyWriteFile OK.\n");

	// �ļ����ݶ�ȡ
	UNICODE_STRING ustrReadFile;
	LARGE_INTEGER liReadOffset = { 0 };
	UCHAR szReadData[256] = { 0 };
	ULONG ulReadDataLength = 256;
	RtlInitUnicodeString(&ustrReadFile, L"C:\\TEST.txt");
	IRP_MyReadFile(ustrReadFile, liReadOffset, szReadData, &ulReadDataLength);
	DbgPrint("MyReadFile:[%s]\n", szReadData);
}

/**
 * ����NTFS
 * Ӳ���д洢���Ǵ�����0��1����������
 * �ļ�ϵͳ��Ӳ���������ø�ʽ����
 */
VOID TESTNTFS()
{
	//����һ����Ŀ��FileOpNTFS
}

#include "ntddk.h" // �������Ҫ�ŵ����棬��Ϊ�ļ�������ʹ����ntifs.h����ǰ��Ļ����������ض������
//IRP������Ҫ
NTSTATUS CreateDevice(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Enter CreateDevice\n");
	NTSTATUS status = STATUS_SUCCESS;
	PDEVICE_OBJECT pDevObj = NULL;
	UNICODE_STRING ustrDevName, ustrSymName;
	RtlInitUnicodeString(&ustrDevName, DEV_NAME);
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);

	status = IoCreateDevice(pDriverObject, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateDevice Error[0x%X]\n", status);
		return status;
	}

	status = IoCreateSymbolicLink(&ustrSymName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("IoCreateSymbolicLink Error[0x%X]\n", status);
		return status;
	}

	DbgPrint("Leave CreateDevice\n");
	return status;
}

VOID DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Enter DriverUnload\n");

	if (pDriverObject->DeviceObject)
	{
		IoDeleteDevice(pDriverObject->DeviceObject);
	}
	UNICODE_STRING ustrSymName;
	RtlInitUnicodeString(&ustrSymName, SYM_NAME);
	IoDeleteSymbolicLink(&ustrSymName);

	DbgPrint("Leave DriverUnload\n");
}
//IRP�����õ���
NTSTATUS DriverControlHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	DbgPrint("Enter DriverControlHandle\n");
	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIoStackLocation = IoGetCurrentIrpStackLocation(pIrp);
	ULONG ulInputLen = pIoStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG ulOutputLen = pIoStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG ulControlCode = pIoStackLocation->Parameters.DeviceIoControl.IoControlCode;
	PVOID pBuffer = pIrp->AssociatedIrp.SystemBuffer;
	ULONG ulInfo = 0;

	switch (ulControlCode)
	{
	case IOCTL_TEST:
	{
		break;
	}
	default:
		break;
	}

	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = ulInfo;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	DbgPrint("Leave DriverControlHandle\n");
	return status;
}

NTSTATUS DriverDefaultHandle(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	pIrp->IoStatus.Status = status;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	return status;
}
//�������
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	DbgPrint("Enter DriverEntry\n");
	NTSTATUS status = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE] = DriverDefaultHandle;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverDefaultHandle;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DriverControlHandle;


	//ʹ���ں�API��ʽ�����ļ�
	//TestKernelAPI();

	//����IRP�����ļ�
	status = CreateDevice(DriverObject);
	TESTIRP();

	DbgPrint("Leave DriverEntry\n");
	return status;
}