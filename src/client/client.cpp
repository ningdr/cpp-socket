#include <winsock.h>
#include "spdlog/spdlog.h"

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

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client == INVALID_SOCKET) {
        spdlog::error("ERROR: Create Sock Failed {}", WSAGetLastError());
        return 0;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7474);
    serverAddress.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    if (connect(client, (sockaddr *) &serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
        spdlog::error("ERROR: Connect Server Failed {}", WSAGetLastError());
        closesocket(client);
        return 0;
    }

    char data[] = {0x11, 0x01};
    spdlog::debug("sending...");
    send(client, data, sizeof(data) / sizeof(char), 0);
    spdlog::debug("finish...");

    char recData[255];
    int ret = recv(client, recData, 255, 0);
    if(ret>0){
        recData[ret] = 0x00;
        spdlog::info("Received data is: {}", std::string(recData));
    }
    int x = 0;
    int y = 0;
    memcpy(&x, recData, sizeof(int));
    memcpy(&y, recData + sizeof(int), sizeof(int));
    spdlog::info("data is x = {}, y = {}.", x, y);
    closesocket(client);
    WSACleanup();
    return 0;
}
