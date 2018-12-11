#include <stdio.h>

#include "Socket.h"

int main() {
	Socket socket;
	setEndian(&socket, ENDIAN_BIG);
	connectAndBind(&socket, "192.168.137.1", 9002);
	if (connected(&socket))
	{
		printf("connected\n");

		writeInt(&socket, 666);
		writeString(&socket, "Hello~\n");

		int val = 0;
		readInt(&socket, &val);
		printf("%d\n", val);

		char buf[2048];
		readString(&socket, buf);
		printf("%s\n", buf);

		disconnect(&socket);
	}
}