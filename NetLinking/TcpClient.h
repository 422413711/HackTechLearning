#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>


// ���ӵ�������
BOOL Connection(const char* lpszServerIp, int iServerPort);
// ��������
void SendMsg(const char* pszSend);
// �����������ݶ��߳�
void RecvMsg();
// �������ݶ��߳�
UINT RecvThreadProc(LPVOID lpVoid);


#endif