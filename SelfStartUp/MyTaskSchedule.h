#ifndef _MY_TASK_SCHEDULT_H_
#define _MY_TASK_SCHEDULT_H_


#include <Atlbase.h>
#include <comdef.h>
#include <taskschd.h>
#pragma comment(lib, "taskschd.lib")


class CMyTaskSchedule
{
private:

	ITaskService* m_lpITS;
	ITaskFolder* m_lpRootFolder;

public:

	CMyTaskSchedule(void);
	~CMyTaskSchedule(void);

public:

	// ɾ��ָ������ƻ�
	BOOL Delete(const char* lpszTaskName);
	BOOL DeleteFolder(const char* lpszFolderName);

	// ��������ƻ�
	BOOL NewTask(const char* lpszTaskName, const char* lpszProgramPath, const char* lpszParameters, const char* lpszAuthor = "");

	// �ж�ָ������ƻ��Ƿ����
	BOOL IsExist(const char* lpszTaskName);

	// �ж�ָ������ƻ�״̬�Ƿ���Ч
	BOOL IsTaskValid(const char* lpszTaskName);

	// ����ָ������ƻ�
	BOOL Run(const char* lpszTaskName, const char* lpszParam);

	// �ж�ָ������ƻ��Ƿ�����
	BOOL IsEnable(const char* lpszTaskName);

	// ����ָ������ƻ��Ƿ��������ǽ���
	BOOL SetEnable(const char* lpszTaskName, BOOL bEnable);

};


#endif