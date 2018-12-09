
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "Socket.h"

int connected(Socket *sock)
{
    if (sock->_fd < 0 || sock->_bind < 0)
    {
        return UNCONNECTED;
    }
    else
    {
        return CONNECTED;
    }
}

int connectAndBind(Socket *sock, char ipAddr[], int port)
{
    strcpy(sock->_ipAddr, ipAddr);
    sock->_port = port;
    sock->_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (sock->_fd < 0)
    {
        return sock->_fd;
    }

    struct sockaddr_in dest;
    memset(&dest, 0, sizeof(struct sockaddr_in));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);
    dest.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_aton(ipAddr, &(dest.sin_addr));

    sock->_bind = connect(sock->_fd, (struct sockaddr *) &dest, sizeof(dest));
    return sock->_bind;
}

void disconnect(Socket *sock)
{
    close(sock->_bind);
    sock->_bind = -1;
}

int readAll(Socket *sock, char buf[])
{
    return read(sock->_fd, buf, MAX_BUFFER_SIZE);
}

int readString(Socket *sock, char str[])
{
    int count = 0;
    char temp;
    while (read(sock->_fd, &temp, 1))
    {
        str[count] = temp;
        count++;
        printf("%c\n", temp);
        if (temp == '\0')
        {
            break;
        }
    }
    return count;
}