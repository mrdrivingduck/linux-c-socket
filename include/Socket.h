#ifndef SOCKET_H_
#define SOCKET_H_

#define CONNECTED 1
#define UNCONNECTED 0

#define MAX_BUFFER_SIZE 2048
// char buf[BUFFER_SIZE];

typedef struct Socket
{
    int _fd;
    int _bind;
    char _ipAddr[32];
    int _port;
} Socket;

int connected(Socket *sock);

int connectAndBind(Socket *sock, char ipAddr[], int port);

void disconnect(Socket *sock);

int readAll(Socket *socket, char buf[]);
int readString(Socket *socket, char str[]);
int readInt(Socket *socket, int *val);

#endif