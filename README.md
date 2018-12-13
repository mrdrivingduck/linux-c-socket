# linux-c-socket

🔗 A TCP wrapper for underlying Linux Socket.

Created by : Mr Dk.

@2018.12.13, Nanjing, Jiangsu, China

The National public memorial day of Nanjing Massacre 🕯️🕯️🕯️

---

### Structure

```c
typedef struct Socket
{
    int _fd;
    int _bind;
    char _ipAddr[32];
    int _port;
    int _endian;
} Socket;
```

The structure contains:

* __IP Address__ to connect
* __port__ to connect
* __File descriptor__ for _read/write_
* __Endian__ to store bytes
  * `ENDIAN_BIG` / `ENDIAN_LITTLE`

### Connector API

* ```c
  int connectAndBind(Socket *sock, char ipAddr[], int port, long timeout_sec);
  ```

  * Parameters
    * `Socket *sock` - Structure of wrapper
    * `char ipAddr[]` - A string-form IP address to connect
    * `int port` - A integer-form port to connect
    * `long timeout_sec` - A long-form timeout time in seconds
  * Return
    * `CONNECTED` if succeed
    * `UNCONNECTED` if failed

* ```c
  void disconnect(Socket *sock);
  ```

* ```c
  void setEndian(Socket *sock, int endian);
  ```

  * Parameter
    * `int endian` - Can be assigned with `ENDIAN_BIG` or `ENDIAN_LITTLE`

* ```c
  int connected(Socket *sock);
  ```

  * Return
    * `CONNECTED` if connected
    * `UNCONNECTED` if unconnected

### I/O API

* ```c
  int readLine(Socket *socket, char str[]);
  int readString(Socket *socket, char str[]);
  int readInt(Socket *socket, int *val);
  int readFloat(Socket *socket, float *val);
  // ......
  ```

* ```c
  int writeLine(Socket *socket, char str[]);
  int writeString(Socket *socket, char str[]);
  int writeInt(Socket *socket, int val);
  int writeFloat(Socket *socket, float val);
  // ......
  ```

Implementing to support more data type......

---

