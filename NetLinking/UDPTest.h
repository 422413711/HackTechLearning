#ifndef _UDP_TEST_H_
#define _UDP_TEST_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>

// ��IP��ַ�Ͷ˿�
BOOL Bind(char *lpszIp, int iPort);
// ���ݷ���
void SendMsg(char *lpszText, char *lpszIp, int iPort);
// ���ݽ���
void UDPRecvMsg();
// �������ݶ��߳�
UINT UDPRecvThreadProc(LPVOID lpVoid);


#endif