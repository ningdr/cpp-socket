#include <Winsock2.h>
#include "spdlog/spdlog.h"

// ���ݳ���
const int DATA_LEN = 255;

int main() {
    spdlog::set_level(spdlog::level::debug);
    //�����׽��ֿ�
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD(2, 2);
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        spdlog::error("ERROR: Start WAS Failed {}", WSAGetLastError());
        return 0;
    }

    // �������ڼ������׽���
    SOCKET socketListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketListen == INVALID_SOCKET) {
        spdlog::error("ERROR: Create Listen Failed {}", WSAGetLastError());
        return 0;
    }

    // ʵ����һ�� sockaddr_in ����ŵ�ַ��Ϣ
    sockaddr_in sin{};
    // ָ���ṩ�����IP��ַΪ�����ĵ�ַ
    sin.sin_family = AF_INET;
    // ת�������� IP ��ַ
//    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    // PORT
    sin.sin_port = htons(8689);

    // �� IP �� PORT
    if (bind(socketListen, (LPSOCKADDR) &sin, sizeof(sin)) == SOCKET_ERROR) {
        spdlog::error("ERROR: Address Bind Failed {}", WSAGetLastError());
        return 0;
    }

    // ��ʼ����
    if (listen(socketListen, 5) == SOCKET_ERROR) {
        spdlog::error("ERROR: Start Listen Failed {}", WSAGetLastError());
        return 0;
    }

    SOCKET client;
    sockaddr_in remoteAddress{};
    int remoteAddressLen = sizeof(remoteAddress);
    char recvBuf[DATA_LEN];    //��
    char sendBuf[DATA_LEN];    //��
    char tempBuf[DATA_LEN];    //�洢�м���Ϣ����

    while (true) {
        spdlog::debug("Waiting for connection...");
        client = accept(socketListen, (SOCKADDR *) &remoteAddress, &remoteAddressLen);
        if (client == INVALID_SOCKET) {
            spdlog::error("ERROR: Accept Information Failed, Continue");
            continue;
        }
        spdlog::debug("Received {} Info", inet_ntoa(remoteAddress.sin_addr));
        // ��������
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