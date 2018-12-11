
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

    sock->_bind = connect(sock->_fd, (struct sockaddr *)&dest, sizeof(dest));
    return sock->_bind;
}

void setEndian(Socket *sock, int endian)
{
    if (endian == ENDIAN_BIG)
    {
        sock->_endian = ENDIAN_BIG;
    }
    else
    {
        sock->_endian = ENDIAN_LITTLE;
    }
}

void disconnect(Socket *sock)
{
    close(sock->_bind);
    sock->_bind = -1;
}

int readString(Socket *sock, char str[])
{
    int count = 0;
    char temp = 0;
    while (read(sock->_fd, &temp, 1))
    {
        if (temp == '\0')
        {
            break;
        }
        str[count] = temp;
        count++;
    }
    str[count] = '\0';
    return count;
}

int readInt(Socket *sock, int *val)
{
    int count = 0;
    *val = 0;
    char temp = 0;
    while (read(sock->_fd, &temp, 1))
    {
        if (sock->_endian == ENDIAN_BIG)
        {
            (*val) |= ((temp & 0x0FF) << (8 * (sizeof(int) - 1 - count)));
        }
        else
        {
            (*val) |= ((temp & 0x0FF) << (8 * count));
        }

        count++;
        if (count == sizeof(int))
        {
            break;
        }
    }
    return count;
}

int writeInt(Socket *sock, int val)
{
    int count = 0;
    char temp = 0;
    if (sock->_endian == ENDIAN_BIG)
    {
        temp = ((val >> 24) & 0x0FF);
        count += write(sock->_fd, &temp, 1);
        temp = ((val >> 16) & 0x0FF);
        count += write(sock->_fd, &temp, 1);
        temp = ((val >> 8) & 0x0FF);
        count += write(sock->_fd, &temp, 1);
        temp = (val & 0x0FF);
        count += write(sock->_fd, &temp, 1);
    }
    else 
    {
        temp = (val & 0x0FF);
        count += write(sock->_fd, &temp, 1);
        temp = ((val >> 8) & 0x0FF);
        count += write(sock->_fd, &temp, 1);
        temp = ((val >> 16) & 0x0FF);
        count += write(sock->_fd, &temp, 1);
        temp = ((val >> 24) & 0x0FF);
        count += write(sock->_fd, &temp, 1);
    }
    return count;
}

int writeString(Socket *sock, char str[])
{
    return write(sock->_fd, str, strlen(str));
}