# TCP-
一个客户端一个服务器   UI是qt做的 代码部分大多数也是用qt c++
<img width="688" height="693" alt="image" src="https://github.com/user-attachments/assets/08206fe1-0296-4540-99cd-62601db50f3e" />
主要就是一个简单的对话
<img width="990" height="396" alt="image" src="https://github.com/user-attachments/assets/8bc1e1a6-6942-44b7-a4ef-65fece5ea526" />

TCPServer类关于监听，连接，发送，接受的API
TCPServer在网络通信中常用的信号
TCPScoket在QT实现Socket常用的API
TCPScoket在QT实现Socket常用的信号
EditText的内容读取方法，内容写入方法，在特定行写入特点颜色的方法

| 类别            | 功能               | API/方法                                                      | 描述                                                   |
|-----------------|--------------------|---------------------------------------------------------------|--------------------------------------------------------|
| TCPServer       | 监听               | `bool listen(const QHostAddress& address, quint16 port)`      | 在指定的 IP 地址和端口上开始监听传入的连接。           |
| TCPServer       | 连接               | `void close()`                                                | 停止服务器监听传入的连接。                             |
| TCPServer信号   | 连接               | `QTcpSocket *nextPendingConnection()`                         | 返回下一个待处理连接的 QTcpSocket 指针。               |
| TCPServer信号   |                    | `newConnection()`                                             | 当有新连接时发出。                                     |
| TCPSocket       | 发送               | `void connectToHost(const QString &host, quint16 port)`       | 连接到指定的主机和端口。                               |
| TCPSocket       | 发送               | `qint64 write(const QByteArray &data)`                        | 向连接的套接字写入数据。                               |
| TCPSocket       | 接收               | `QByteArray readAll()`                                        | 读取可用的所有数据。                                   |
| TCPSocket       | 断开               | `void disconnectFromHost()`                                   | 断开与主机的连接。                                     |
| TCPSocket信号   | 连接               | `connected()`                                                 | 成功连接到主机时发出。                                 |
| TCPSocket信号   | 连接               | `disconnected()`                                              | 从主机断开连接时发出。                                 |
| TCPSocket信号   | 连接               | `readyRead()`                                                 | 当有可读数据时发出。                                   |
| TCPSocket信号   | 连接               | `byteswritten(qint64 bytes)`                                  | 成功写入数据时发出。                                   |
| EditText        | 读取内容           | `string getText()`                                            | 获取 EditText 的内容。                                 |
| EditText        | 写入内容           | `void setText(string text)`                                   | 设置 EditText 的内容。                                 |
| EditText        | 使用光标改变文本颜色 | `void changeTextColor(int start, int end, int color)`         | 使用光标改变 EditText 中 start 到 end 位置的文本颜色为 color。 |


