#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define BUF_SIZE 1024

struct Peer {
    string name;
    string ipStr;
    int port;
    sockaddr_in addr;
};

void printPrompt(const string& targetName) {
    cout << "[송신:" << targetName << "] > ";
    cout.flush();
}

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "WSAStartup 실패\n";
        return 1;
    }

    int mode;
    cout << "[모드 선택] 1: UDP / 2: TCP : ";
    cin >> mode;
    cin.ignore();

    SOCKET sockfd = INVALID_SOCKET;
    sockaddr_in local_addr{}, server_addr{};

    if (mode == 1) {
        // ===============================
        // UDP 모드
        // ===============================
        int local_port, peerCount;
        cout << "[UDP] 내 포트 번호 입력: ";
        cin >> local_port;
        cout << "[UDP] 피어 수 입력: ";
        cin >> peerCount;
        cin.ignore();

        vector<Peer> peers(peerCount);
        for (int i = 0; i < peerCount; ++i) {
            cout << "\n[피어 " << (i + 1) << "] 이름: ";
            getline(cin, peers[i].name);
            cout << "[피어 " << (i + 1) << "] IP: ";
            getline(cin, peers[i].ipStr);
            cout << "[피어 " << (i + 1) << "] 포트: ";
            cin >> peers[i].port;
            cin.ignore();

            memset(&peers[i].addr, 0, sizeof(peers[i].addr));
            peers[i].addr.sin_family = AF_INET;
            peers[i].addr.sin_port = htons(peers[i].port);
            inet_pton(AF_INET, peers[i].ipStr.c_str(), &peers[i].addr.sin_addr);
        }

        sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        local_addr.sin_family = AF_INET;
        local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        local_addr.sin_port = htons(local_port);

        bind(sockfd, (sockaddr*)&local_addr, sizeof(local_addr));

        cout << "\n[UDP 모드 시작]\n";
        printPrompt(peers[0].name);

        while (true) {
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(sockfd, &readfds);

            timeval tv{};
            tv.tv_sec = 0;
            tv.tv_usec = 100000;

            int ret = select(0, &readfds, nullptr, nullptr, &tv);

            // 키보드 입력
            if (_kbhit()) {
                string msg;
                getline(cin, msg);
                if (msg == "/quit") break;
                for (auto& p : peers)
                    sendto(sockfd, msg.c_str(), msg.size(), 0,
                        (sockaddr*)&p.addr, sizeof(p.addr));
                printPrompt(peers[0].name);
            }

            // 수신 처리
            if (FD_ISSET(sockfd, &readfds)) {
                char buf[BUF_SIZE + 1];
                sockaddr_in from{};
                int len = sizeof(from);
                int recvLen = recvfrom(sockfd, buf, BUF_SIZE, 0, (sockaddr*)&from, &len);
                if (recvLen > 0) {
                    buf[recvLen] = '\0';
                    char ip[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &from.sin_addr, ip, sizeof(ip));
                    cout << "\n[받음 " << ip << ":" << ntohs(from.sin_port) << "] " << buf << "\n";
                    printPrompt(peers[0].name);
                }
            }
        }
    }
    else if (mode == 2) {
        // ===============================
        // TCP 모드
        // ===============================
        string server_ip;
        int server_port;
        cout << "[TCP] 서버 IP 입력: ";
        cin >> server_ip;
        cout << "[TCP] 서버 포트 입력: ";
        cin >> server_port;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr);
        server_addr.sin_port = htons(server_port);

        if (connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
            cerr << "서버 연결 실패\n";
            closesocket(sockfd);
            WSACleanup();
            return 1;
        }

        cout << "\n[TCP 모드 시작] 서버에 연결됨.\n";
        printPrompt("서버");

        while (true) {
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(sockfd, &readfds);

            timeval tv{};
            tv.tv_sec = 0;
            tv.tv_usec = 100000;

            int ret = select(0, &readfds, nullptr, nullptr, &tv);

            if (_kbhit()) {
                string msg;
                getline(cin, msg);
                if (msg == "/quit") break;
                send(sockfd, msg.c_str(), msg.size(), 0);
                printPrompt("서버");
            }

            if (FD_ISSET(sockfd, &readfds)) {
                char buf[BUF_SIZE + 1];
                int recvLen = recv(sockfd, buf, BUF_SIZE, 0);
                if (recvLen <= 0) {
                    cout << "\n서버 연결 종료됨.\n";
                    break;
                }
                buf[recvLen] = '\0';
                cout << "\n[서버] " << buf << "\n";
                printPrompt("서버");
            }
        }
    }
    else {
        cout << "잘못된 선택입니다.\n";
    }

    closesocket(sockfd);
    WSACleanup();
    cout << "프로그램 종료.\n";
    return 0;
}
