#ifndef _FILE_MANAGE_WITH_IRP_H_
#define _FILE_MANAGE_WITH_IRP_H


#include <ntifs.h>
#include <ntstatus.h>

// ע��: ·������Ҫ�� \??\ ��Ϊǰ׺


// ��������ļ�
BOOLEAN IRP_MyCreateFile(UNICODE_STRING ustrFilePath);

// ��ȡ�ļ���С
ULONG64 IRP_MyGetFileSize(UNICODE_STRING ustrFileName);

// �����ļ���������
BOOLEAN IRP_MyHideFile(UNICODE_STRING ustrFileName);

// �����ļ��к��ļ�
BOOLEAN IRP_MyQueryFileAndFileFolder(UNICODE_STRING ustrPath);

// ��ȡ�ļ�����
BOOLEAN IRP_MyReadFile(UNICODE_STRING ustrFileName, LARGE_INTEGER liOffset, PUCHAR pReadData, PULONG pulReadDataSize);

// ���ļ�д������
BOOLEAN IRP_MyWriteFile(UNICODE_STRING ustrFileName, LARGE_INTEGER liOffset, PUCHAR pWriteData, PULONG pulWriteDataSize);


#endif