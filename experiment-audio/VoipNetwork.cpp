#include "VoipNetwork.h"
#include "FixedSizeQueue.h"
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

static SOCKET VoipSocket = INVALID_SOCKET;
static struct sockaddr_in RemoteAddr;
static HANDLE hEvent_UdpReceiveData;
static HANDLE hEvent_UdpThreadEnd;
static HANDLE hThreadEvents[2];

int SetUpUdpVoipNetwork(char* hostname, unsigned short localport, unsigned short remoteport)
{
 int clientAddrSize = (int)sizeof(RemoteAddr);
 struct sockaddr_in LocalAddr;

// Initalize to default value to be safe.
VoipSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
if (VoipSocket == INVALID_SOCKET) {
    std::cout << "socket failed with error " << WSAGetLastError() << '\n';
    return 1;
}

LocalAddr.sin_family = AF_INET;
LocalAddr.sin_addr.s_addr = INADDR_ANY;
LocalAddr.sin_port = htons(localport);
if (bind(VoipSocket, (struct sockaddr*)&LocalAddr, sizeof(LocalAddr)) == SOCKET_ERROR)
{
    std::cout << "Bind failed with error code : " << WSAGetLastError() << '\n';
    return 1;
}

RemoteAddr.sin_family = AF_INET;
RemoteAddr.sin_port = htons(remoteport);
if (inet_pton(AF_INET, hostname, &RemoteAddr.sin_addr) <= 0) {
    std::cout << "Invalid address / Address not supported" << '\n';
    return 1;
}
return 0;
}
void SetUpUdpVoipReceiveEventForThread(void)
{
    hEvent_UdpReceiveData = WSACreateEvent();
    WSAEventSelect(VoipSocket, hEvent_UdpReceiveData, FD_READ);
    hEvent_UdpThreadEnd = CreateEvent(NULL, FALSE, FALSE, NULL);   
    hThreadEvents[0] = hEvent_UdpReceiveData;
    hThreadEvents[1] = hEvent_UdpThreadEnd;
}

int SendUdpVoipData(const char* buf, int len)
{
    int res;
    if ((res = sendto(VoipSocket, buf, len, 0, (struct sockaddr*)&RemoteAddr, sizeof(RemoteAddr))) == SOCKET_ERROR)
    {
        std::cout << "Voip sendto() failed with error code : " << WSAGetLastError() << '\n';
        return(SOCKET_ERROR);
    }
     return(res);
}
int RecvUdpVoipData(char* buf, int len, sockaddr* from, int* fromlen)
{
    int res;
    if ((res = recvfrom(VoipSocket, buf, len, 0, from, fromlen)) == SOCKET_ERROR)
    {
        std::cout << "Voip recvfrom() failed with error code : " << WSAGetLastError() << '\n';
        return(SOCKET_ERROR);
    }
    return(res);
}

int WaitForVoipData(void)
{
    DWORD dwEvent;
    dwEvent = WaitForMultipleObjects(
        2,           // number of objects in array
        hThreadEvents,     // array of objects
        FALSE,       // wait for any object
        INFINITE);  // INFINITE) wait
    if (dwEvent == WAIT_OBJECT_0)
    {
        ResetEvent(hThreadEvents[0]);
        return 1;
    }
    else if (dwEvent == WAIT_OBJECT_0 + 1)
    {
        return 0;
    }
    else 
    {
        std::cout << "here 3\n";
        return -1;
    }
}
void SignalUdpThreadEnd(void)
{
    SetEvent(hEvent_UdpThreadEnd);
}
void ShutdownUdpVoipNetwork(void)
{
    closesocket(VoipSocket);
    WSACloseEvent(hEvent_UdpReceiveData);
    CloseHandle(hEvent_UdpThreadEnd);
}