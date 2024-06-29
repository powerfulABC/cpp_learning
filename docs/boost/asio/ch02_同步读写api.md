# Charpter 02 同步读写api

## 2.1 `write_some()` 非阻塞同步写

`write_some()`向写缓冲区写固定字节数，具体写入的长度取决于缓冲区剩余的长度，只写一次，返回实际写入的长度。

```cpp
    void write_to_socket(boost::asio::ip::tcp::socket& sock)
    {
        std::string message("hello, server");
        std::size_t write_len = 0;
        while (write_len < message.size())
        {
            write_len += sock.write_some(boost::asio::buffer(message.c_str() + write_len, message.size() - write_len));
        }
    }
```

## 2.2 `send()` 阻塞同步写

`send()`向写缓冲区写固定字节长度的数据，如果当前缓冲区剩余长度不足以写入全部数据，该函数将会阻塞直到将所有的数据都写入缓冲区。返回写入的数据长度

```cpp
    void write_to_socket(boost::asio::ip::tcp::socket& sock)
    {
        std::string message("hello, server");
        int send_len = sock.send(boost::asio::buffer(message.c_str(), message.size()));
        if (send_len != message_size)
        {
            std::cout << "send error!" << std::endl;
        }
    }
```

## 2.3 `boost::asio::write()` 全局函数，阻塞同步写

和`send()` 函数一样

```cpp
    void write_to_socket(boost::asio::ip::tcp::socket& sock)
    {
        std::string message("hello, server");
        int send_len = boost::asio::write(sock, boost::asio::buffer(message.c_str(), message.size()));
        if (send_len != message_size)
        {
            std::cout << "send error!" << std::endl;
        }
    }
```

## 2.4 `read_some()` 非阻塞同步读

从读缓冲区读取固定长度的数据，只读取一次，不管读没读全都会返回，最后返回实际读取的数据长度。

```cpp
    void read_from_socket(boost::asio::ip::tcp::socket& sock)
    {
        const int message_size = 1024;

        char buf[1024];
        ::memset(buf, 0, sizeof(buf));
        std::size_t read_len = 0;
        while (read_len < message_size)
        {
            read_len += sock.read_some(boost::asio::buffer(buf + read_len, message_size - read_len));
        }
    }
```

## 2.5 `receive()` 阻塞同步读

从读缓冲区读取固定长度的数据，如果读缓冲区没有足够长度的数据，则一直阻塞直到读取所有的数据，返回读取的数据长度

```cpp
    void read_from_socket(boost::asio::ip::tcp::socket& sock)
    {
        const int message_size = 1024;

        char buf[1024];
        ::memset(buf, 0, sizeof(buf));
        int recv_len = sock.receive(boost::asio::buffer(buf, message_size));

        if (recv_len != message_size)
        {
            std::cout << "read error!" << std::endl;
        }
    }
```

## 2.6 `boost::asio::read()` 全局函数，阻塞同步读

和`receive()`一样

```cpp
    void read_from_socket(boost::asio::ip::tcp::socket& sock)
    {
        const int message_size = 1024;

        char buf[1024];
        ::memset(buf, 0, sizeof(buf));
        int recv_len = boost::asio::read(sock,boost::asio::buffer(buf, message_size));

        if (recv_len != message_size)
        {
            std::cout << "read error!" << std::endl;
        }
    }
```

## 2.7 `read_until()` 全局函数

读直到遇到某个特定字符停止

```cpp
    void read_data_by_until(boost::asio::ip::tcp::socket& sock)
    {
        boost::asio::streambuf buf;
        boost::asio::read_until(sock, buf, '\n');
    }
```
