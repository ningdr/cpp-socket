#include <Winsock2.h>
#include "spdlog/spdlog.h"

// 数据长度
const int DATA_LEN = 255;

int main() {
    spdlog::set_level(spdlog::level::debug);
    //加载套接字库
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        spdlog::error("ERROR: Start WAS Failed {}", WSAGetLastError());
        return 0;
    }

    // 创建用于监听的套接字
    SOCKET socketListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketListen == INVALID_SOCKET) {
        spdlog::error("ERROR: Create Listen Failed {}", WSAGetLastError());
        return 0;
    }

    // 实例化一个 sockaddr_in 来存放地址信息
    sockaddr_in sin{};
    // 指定提供服务的IP地址为本机的地址
    sin.sin_family = AF_INET;
    // 转换服务器 IP 地址
//    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    // PORT
    sin.sin_port = htons(8689);

    // 绑定 IP 和 PORT
    if (bind(socketListen, (LPSOCKADDR) &sin, sizeof(sin)) == SOCKET_ERROR) {
        spdlog::error("ERROR: Address Bind Failed {}", WSAGetLastError());
        return 0;
    }

    // 开始监听
    if (listen(socketListen, 5) == SOCKET_ERROR) {
        spdlog::error("ERROR: Start Listen Failed {}", WSAGetLastError());
        return 0;
    }

    SOCKET client;
    sockaddr_in remoteAddress{};
    int remoteAddressLen = sizeof(remoteAddress);
    char recvBuf[DATA_LEN];    //收
    char sendBuf[DATA_LEN];    //发
    char tempBuf[DATA_LEN];    //存储中间信息数据

    while (true) {
        spdlog::debug("Waiting for connection...");
        client = accept(socketListen, (SOCKADDR *) &remoteAddress, &remoteAddressLen);
        if (client == INVALID_SOCKET) {
            spdlog::error("ERROR: Accept Information Failed, Continue");
            continue;
        }
        spdlog::debug("Received {} Info", inet_ntoa(remoteAddress.sin_addr));
        // 解析数据
        int ret = recv(client, recvBuf, DATA_LEN, 0);
        spdlog::debug("Ret value is {:4d}", ret);
        if (ret > 0) {
            recvBuf[ret] = 0x00;
            spdlog::info("Received data is: {}", std::string(recvBuf));
        }
        const char *data = "987654321";
        send(client, data, int(strlen(data)), 0);
        closesocket(client);
    }
    closesocket(socketListen);
    WSACleanup();

    return 0;
}