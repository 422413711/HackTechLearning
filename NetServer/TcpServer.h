#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_


//#include <Winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>

// �󶨶˿ڲ�����
BOOL SocketBindAndListen(const char *lpszIp, int iPort);
// ��������
void SendMsg(const char *pszSend);
// �����������ݶ��߳�
void AcceptRecvMsg();
// �������ݶ��߳�
UINT RecvThreadProc(LPVOID lpVoid);


#endif