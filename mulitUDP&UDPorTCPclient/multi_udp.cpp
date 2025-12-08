#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 1024
using namespace std;

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
        cerr << "WSAStartup 실패: " << WSAGetLastError() << "\n";
        return 1;
    }

    SOCKET sockfd;
    sockaddr_in local_addr{};

    int local_port = 0;
    int peerCount = 0;
    vector<Peer> peers;

    // 1. 초기 설정 입력

    cout << "[설정] 내(로컬) 포트 번호를 입력하세요: ";
    cin >> local_port;

    cout << "[설정] 통신할 사용자(피어)의 수를 입력하세요: ";
    cin >> peerCount;

    if (local_port <= 0 || local_port > 65535) {
        cerr << "로컬 포트 번호는 1~65535 사이여야 합니다.\n";
        WSACleanup();
        return 1;
    }
    if (peerCount <= 0) {
        cerr << "최소 1명 이상의 피어가 필요합니다.\n";
        WSACleanup();
        return 1;
    }

    {// cin.ignore() 대체 – 입력 버퍼 비우기
        string dummy;
        getline(cin, dummy);
    }

    peers.reserve(peerCount);
    for (int i = 0; i < peerCount; ++i) {
        Peer p{};
        string portStr;

        cout << "\n[피어 설정] #" << (i + 1) << " 이름: ";
        getline(cin, p.name);
        if (p.name.empty())
            p.name = "Peer" + to_string(i + 1);

        cout << "[피어 설정] #" << (i + 1) << " IP 주소: ";
        getline(cin, p.ipStr);

        cout << "[피어 설정] #" << (i + 1) << " 포트 번호: ";
        getline(cin, portStr);
        p.port = stoi(portStr);

        if (p.port <= 0 || p.port > 65535) {
            cerr << "포트 번호는 1~65535 사이여야 합니다.\n";
            WSACleanup();
            return 1;
        }

        memset(&p.addr, 0, sizeof(p.addr));
        p.addr.sin_family = AF_INET;
        p.addr.sin_port = htons((u_short)p.port);

        if (inet_pton(AF_INET, p.ipStr.c_str(), &p.addr.sin_addr) <= 0) {
            cerr << "잘못된 IP 주소: " << p.ipStr << "\n";
            WSACleanup();
            return 1;
        }

        peers.push_back(p);
    }

    int currentPeerIdx = 0;
    string currentTargetName = peers[currentPeerIdx].name;

    // 2. UDP 소켓 생성 및 바인드
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd == INVALID_SOCKET) {
        cerr << "socket() 실패: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons((u_short)local_port);

    if (bind(sockfd, (sockaddr*)&local_addr, sizeof(local_addr)) == SOCKET_ERROR) {
        cerr << "bind() 실패: " << WSAGetLastError() << "\n";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    cout << "\n=== UDP 멀티-유저 채팅 시작 ===\n";
    cout << "로컬 포트: " << local_port << "\n";
    cout << "등록된 피어 목록:\n";

    for (size_t i = 0; i < peers.size(); ++i) {
        cout << "  " << (i + 1) << ") " << peers[i].name
            << " - " << peers[i].ipStr << ":" << peers[i].port << "\n";
    }

    cout << "\n명령어:\n";
    cout << "  /list        : 피어 목록 보기\n";
    cout << "  /use N       : N번째 피어 선택\n";
    cout << "  /all 메시지  : 모든 피어에게 전송\n";
    cout << "  /quit        : 종료\n\n";

    printPrompt(currentTargetName);

    while (true) {// 3. select + _kbhit 루프
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        // select() 대기 시간 설정
        timeval tv{};
        tv.tv_sec = 0;
        tv.tv_usec = 100000; // 0.1초

        int ret = select(0, &readfds, nullptr, nullptr, &tv);

        if (ret == SOCKET_ERROR) {
            cerr << "select() 실패: " << WSAGetLastError() << "\n";
            break;
        }

        // ---------------------------
        // 3-1. 키보드 입력 처리 (_kbhit)
        // ---------------------------
        if (_kbhit()) {
            string line;
            getline(cin, line);

            if (line.empty()) {
                printPrompt(currentTargetName);
                continue;
            }

            if (line[0] == '/') {
                if (line == "/quit") {
                    cout << "종료합니다.\n";
                    break;
                }
                else if (line == "/list") {
                    cout << "\n[피어 목록]\n";
                    for (size_t i = 0; i < peers.size(); ++i) {
                        cout << "  " << (i + 1) << ") " << peers[i].name
                            << " - " << peers[i].ipStr << ":" << peers[i].port;
                        if ((int)i == currentPeerIdx)
                            cout << "  <-- 현재 선택";
                        cout << "\n";
                    }
                }
                else if (line.rfind("/use", 0) == 0) {
                    string numStr = line.substr(4);
                    auto pos = numStr.find_first_not_of(" \t");
                    if (pos != string::npos)
                        numStr = numStr.substr(pos);

                    int idx = stoi(numStr);
                    if (idx >= 1 && idx <= (int)peers.size()) {
                        currentPeerIdx = idx - 1;
                        currentTargetName = peers[currentPeerIdx].name;
                        cout << "현재 송신 대상: " << currentTargetName << "\n";
                    }
                    else {
                        cout << "잘못된 인덱스입니다.\n";
                    }
                }
                else if (line.rfind("/all", 0) == 0) {
                    string msg = line.substr(4);
                    auto pos = msg.find_first_not_of(" \t");
                    if (pos != string::npos)
                        msg = msg.substr(pos);
                    else
                        msg.clear();

                    if (msg.empty()) {
                        cout << "메시지가 비어 있습니다.\n";
                    }
                    else {
                        for (auto& p : peers) {
                            int sent = sendto(
                                sockfd, msg.c_str(), msg.size(), 0,
                                (sockaddr*)&p.addr, sizeof(p.addr));
                            if (sent == SOCKET_ERROR) {
                                cerr << "sendto() 실패: " << WSAGetLastError() << "\n";
                            }
                        }
                        cout << "모든 피어에게 전송됨.\n";
                    }
                }
                else {
                    cout << "알 수 없는 명령어입니다.\n";
                }

                printPrompt(currentTargetName);
                continue;
            }

            // 기본 메시지: 현재 선택된 피어에게 전송
            const Peer& target = peers[currentPeerIdx];
            int sent = sendto(
                sockfd,
                line.c_str(),
                line.size(),
                0,
                (sockaddr*)&target.addr,
                sizeof(target.addr)
            );

            if (sent == SOCKET_ERROR) {
                cerr << "sendto() 실패: " << WSAGetLastError() << "\n";
            }

            printPrompt(currentTargetName);
        }

        // ---------------------------
        // 3-2. 수신 처리
        // ---------------------------
        if (ret > 0 && FD_ISSET(sockfd, &readfds)) {
            char buf[BUF_SIZE + 1];
            sockaddr_in from{};
            int fromLen = sizeof(from);

            int received = recvfrom(
                sockfd, buf, BUF_SIZE, 0,
                (sockaddr*)&from, &fromLen
            );

            if (received == SOCKET_ERROR) {
                cerr << "recvfrom() 실패: " << WSAGetLastError() << "\n";
                break;
            }

            buf[received] = '\0';

            char from_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &from.sin_addr, from_ip, sizeof(from_ip));
            int from_port = ntohs(from.sin_port);

            string fromName = "Unknown";
            for (auto& p : peers) {
                if (p.addr.sin_addr.s_addr == from.sin_addr.s_addr &&
                    p.addr.sin_port == from.sin_port) {
                    fromName = p.name;
                    break;
                }
            }

            cout << "\n[받음 " << fromName
                << " (" << from_ip << ":" << from_port << ")] "
                << buf << "\n";

            printPrompt(currentTargetName);
        }
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}