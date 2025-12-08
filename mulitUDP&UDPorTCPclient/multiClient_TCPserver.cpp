#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define BUF_SIZE 1024

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(9000);

    bind(servSock, (sockaddr*)&servAddr, sizeof(servAddr));
    listen(servSock, 5);
    cout << "서버 대기 중 (포트 9000)...\n";

    fd_set readfds, tempfds;
    vector<SOCKET> clients;
    FD_ZERO(&readfds);
    FD_SET(servSock, &readfds);

    while (true) {
        tempfds = readfds;
        int ret = select(0, &tempfds, nullptr, nullptr, nullptr);
        if (ret > 0) {
            if (FD_ISSET(servSock, &tempfds)) {
                sockaddr_in cliAddr{};
                int len = sizeof(cliAddr);
                SOCKET cliSock = accept(servSock, (sockaddr*)&cliAddr, &len);
                clients.push_back(cliSock);
                FD_SET(cliSock, &readfds);
                cout << "클라이언트 접속!\n";
            }

            for (auto it = clients.begin(); it != clients.end();) {
                SOCKET s = *it;
                if (FD_ISSET(s, &tempfds)) {
                    char buf[BUF_SIZE];
                    int recvLen = recv(s, buf, BUF_SIZE, 0);
                    if (recvLen <= 0) {
                        cout << "클라이언트 종료\n";
                        closesocket(s);
                        FD_CLR(s, &readfds);
                        it = clients.erase(it);
                        continue;
                    }
                    buf[recvLen] = '\0';
                    cout << "[메시지 수신] " << buf << "\n";

                    // 모든 클라이언트에게 브로드캐스트
                    for (SOCKET c : clients)
                        if (c != s)
                            send(c, buf, recvLen, 0);
                }
                ++it;
            }
        }
    }

    closesocket(servSock);
    WSACleanup();
}