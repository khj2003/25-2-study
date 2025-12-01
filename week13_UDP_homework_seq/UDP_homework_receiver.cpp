#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
using namespace std;

#define SERVERPORT 9000
#define BUFSIZE    512
#pragma comment(lib, "ws2_32.lib")

int main() {
    //윈속 초기화
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    
    //소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);


    //bind()
    sockaddr_in localaddr;
    memset(&localaddr, 0, sizeof(localaddr));
    localaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &localaddr.sin_addr);
    localaddr.sin_port = htons(SERVERPORT);

    bind(sock, (sockaddr*)&localaddr, sizeof(localaddr));

    //메시지 수신 준비 변수
    char buf[BUFSIZE + 1];
    sockaddr_in senderaddr;
    int addrlen = sizeof(senderaddr);

    cout << "Receiver 시작\n";

    while (1) {// 메시지 수신 루프, 패킷이 도착할 때까지 무한 대기
        int ret = recvfrom(// ret = 받은 바이트 수
            sock,
            buf,//실제 메시지가 저장됨
            BUFSIZE,
            0,
            (sockaddr*)&senderaddr,
            &addrlen
        );

        if (ret == SOCKET_ERROR)
            continue;

        buf[ret] = 0;

        cout << "[RECV] " << buf << "\n";
    }

    closesocket(sock);
    WSACleanup();
}