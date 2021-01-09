// HideProcess_ZwQuerySystemInformation_Test.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "pch.h"


extern HMODULE g_hModule;

#pragma data_seg("s_data")
	HHOOK g_hHook = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:s_data,RWS")


// ��Ϣȫ�ֹ��ӻص�����
LRESULT CALLBACK GetMsgProc(
	int code,       // hook code
	WPARAM wParam,  // removal option  
	LPARAM lParam   // message
	)
{
	// �������κβ���������ȫ�ֹ��ӵ�Ŀ�ľ��ǽ���DLLע����ѣ���Ҫ������ڽ��е�API�ҹ�

	return ::CallNextHookEx(g_hHook, code, wParam, lParam);
}

//��Ҫdef�ļ���ʽ��������

// ����ȫ�ֹ���
HHOOK SetHook()
{
	// ����ȫ�ֹ���
	HHOOK hHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hModule, 0);
	if (NULL == hHook)
	{
		return NULL;
	}
	g_hHook = hHook;
	return hHook;
}


// ж��ȫ�ֹ���
BOOL UnsetHook(HHOOK hHook)
{
	if (FALSE == ::UnhookWindowsHookEx(hHook))
	{
		return FALSE;
	}
	return TRUE;
}