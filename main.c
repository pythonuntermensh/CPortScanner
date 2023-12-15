#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib");

#define MAX_PORT 100

int main()
{
    SOCKET sock;
    struct sockaddr_in conn_addr;

    WSADATA firstsock;
    if (WSAStartup(MAKEWORD(2,0), &firstsock) != 0)  //CHECKS FOR WINSOCK VERSION 2.0
    {
        fprintf(stderr,"WSAStartup() failed");
        exit(EXIT_FAILURE);
    }

    char ip_addr[15];
    printf("Enter ip addr to scan: \n");
    gets(ip_addr);

    conn_addr.sin_family = AF_INET;
    conn_addr.sin_addr.s_addr = inet_addr(ip_addr);

    for (int port = 0; port < MAX_PORT; port++) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            fprintf(stderr, "Error while creating web server.");
            return -1;
        }

        conn_addr.sin_port = htons(port);
        if (connect(sock, (struct sockaddr *)&conn_addr, sizeof(conn_addr)) == SOCKET_ERROR) {
            printf("Port %d on %s addr is closed! %d\n", port, ip_addr, WSAGetLastError());
            fflush(stdout);
        }
        else {
            printf("Port %d on %s addr is opened!\n", port, ip_addr);
            if (shutdown(sock, SD_BOTH) == SOCKET_ERROR) {
                perror("\exit");
                exit(EXIT_FAILURE);
            }
        }

        fflush(stdout);
        closesocket(sock);
    }

    return 0;
}


