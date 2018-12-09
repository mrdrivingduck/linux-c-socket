#include <stdio.h>

#include "Socket.h"

int main() {
	printf("Hello World\n");
	Socket socket;
	// printf("%d\n", connected(&socket));
	connectAndBind(&socket, "192.168.25.1", 9002);
	if (connected(&socket))
	{
		printf("connected\n");
		char buf[2048];

		readString(&socket, buf);
		printf("%s\n", buf);

		disconnect(&socket);
	}
}