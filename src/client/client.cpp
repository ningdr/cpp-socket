#include <winsock.h>
#include "spdlog/spdlog.h"
#include <iostream>

int main() {
    spdlog::set_level(spdlog::level::debug);
    //¼ÓÔØÌ×½Ó×Ö¿â
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        spdlog::error("ERROR: Start WAS Failed {}", WSAGetLastError());
        return 0;
    }
    char ip[16];
    int port;
    printf("Please input server ip: ");
    std::cin >> ip;
    printf("Please input server port: ");
    std::cin >> port;
    printf("Got ip is %s, port is %d\n", ip, port);

    while (true) {
        int command;
        printf("Detect Type: 0x11 Corner; 0x22 Edge; Press q to Quit.\n");
        printf("Please input detect type: ");
        std::cin >> std::hex >> command;
        printf("Got detect type is %d, 0x11 == %d\n", command, 0x11 == command);
        char i;
        if (command == 0x11) {
            i = '1';
        } else if (command == 0x22) {
            printf("Please input detect row: ");
            std::cin >> i;
            printf("Got detect row is %c\n", i);
        }
        SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client == INVALID_SOCKET) {
            spdlog::error("ERROR: Create Sock Failed {}", WSAGetLastError());
            return 0;
        }
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);
        serverAddress.sin_addr.S_un.S_addr = inet_addr(ip);
        if (connect(client, (sockaddr *) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
            spdlog::error("ERROR: Connect Server Failed {}", WSAGetLastError());
            closesocket(client);
            return 0;
        }

        char data[10] = {0,};
        int head = 0xFFFD;
        memcpy(&data, &head, 4);
        data[4] = 10;
        // 0x11 ½Çµã
        // 0x22 ±ß
        data[5] = 'q';
        data[6] = i;
        int tail = 0xAA;
        memcpy((data + 7), &tail, 2);
        spdlog::debug("sending...{}", data);
        send(client, data, sizeof(data) / sizeof(char), 0);
        spdlog::debug("finish...");

        char recData[255];
        int ret = recv(client, recData, 255, 0);
        if(ret>0){
            recData[ret] = 0x00;
            spdlog::info("Received data is: {}", std::string(recData));
        }
        short int x = 0;
        short int y = 0;
        short int z = 0;
        memcpy(&x, recData + 5, 2);
        memcpy(&y, recData + 7, 2);
        memcpy(&z, recData + 9, 2);
        spdlog::info("data is x = {}, y = {}, z = {}.", x, y, z);
        closesocket(client);
    }
    WSACleanup();
    return 0;
}
