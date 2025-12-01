#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

#define SERVERPORT 9000
#define BUFSIZE    512
#pragma comment(lib, "ws2_32.lib")

int main() {
    //윈속 초기화
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    //UDP 소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

    //목적지 주소 설정(receiver 주소, 내 컴퓨터)
    sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serveraddr.sin_addr);
    serveraddr.sin_port = htons(SERVERPORT);

    int seq = 0;//반복 전송을 위한 변수 준비
    char buf[BUFSIZE];

    cout << "Sender 시작\n";

    while (1) {//반복 송신 루프 시작
        seq++;//시퀀스 번호 증가 + 메시지 문자열 생성
        sprintf_s(buf, BUFSIZE, "SEQ: %d", seq);

        sendto(sock, buf, (int)strlen(buf), 0,//UDP 메시지 전송
            (sockaddr*)&serveraddr, sizeof(serveraddr));

        cout << "[SEND] " << buf << "\n";//송신 내용 출력

        this_thread::sleep_for(chrono::milliseconds(500));//전송 간격(0.5초)
    }

    closesocket(sock);
    WSACleanup();
}