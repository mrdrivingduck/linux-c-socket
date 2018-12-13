#include <stdio.h>

#include "dksocket.h"

int main() {
    Socket socket;
    setEndian(&socket, ENDIAN_BIG);
    connectAndBind(&socket, "192.168.137.1", 9002, 2);
    if (connected(&socket))
    {
        printf("connected\n");

        writeInt(&socket, 666);
        writeLine(&socket, "Hello~");
        writeFloat(&socket, 3.8f);

        int val = 0;
        readInt(&socket, &val);
        printf("%d\n", val);

        char buf[2048];
        readLine(&socket, buf);
        printf("%s\n", buf);

        float fl = 0.0f;
        readFloat(&socket, &fl);
        printf("%f\n", fl);

        disconnect(&socket);
    }
}