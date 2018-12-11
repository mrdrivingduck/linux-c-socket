#ifndef SOCKET_H_
#define SOCKET_H_

#define CONNECTED 1
#define UNCONNECTED 0

#define ENDIAN_LITTLE 1
#define ENDIAN_BIG 0

#define MAX_BUFFER_SIZE 2048
// char buf[BUFFER_SIZE];

typedef struct Socket
{
    int _fd;
    int _bind;
    char _ipAddr[32];
    int _port;
    int _endian;
} Socket;

int connected(Socket *sock);

int connectAndBind(Socket *sock, char ipAddr[], int port);

void disconnect(Socket *sock);

void setEndian(Socket *sock, int endian);

int readString(Socket *socket, char str[]);
int readInt(Socket *socket, int *val);

int writeString(Socket *socket, char str[]);
int writeInt(Socket *socket, int val);

#endif