#pragma once
#ifndef __NETWORK_H__
#define __NETWORK_H__
#include <WinSock2.h>
#include <Ws2tcpip.h>

int SetUpUdpVoipNetwork(char* hostname, unsigned short localport, unsigned short remoteport);
void SetUpUdpVoipReceiveEventForThread(void);
int SendUdpVoipData(const char* buf, int len);
int RecvUdpVoipData(char* buf, int len, sockaddr* from, int* fromlen);
void ShutdownUdpVoipNetwork(void);
int WaitForVoipData(void);
void SignalUdpThreadEnd(void);
#endif