本文摘自：unix 高级环境编程
-	目录 <span id="Index"/>
-	[第十六章 网络IPC：套接字](#16)


### 第十六章 网络IPC 套接字 [\[Index\]](#Index) <span id="16"/>      
-	linux socket编程思想
> 在类Berkeley socket编程中，socket 的最顶层是一个整型的socket描述符fd，所有关于数据的操作都是通过这个描述符完成。fd是整个系统的最高抽象层。这个fd就是客户软件与服务器端的“数据终端”，这个终端隐藏了网络的底层，使我们像操作文件一样来进行数据的传输。         
> <br/>
> 要使这个fd可用，在使用前要先对其进行一定的设置：fd要和“数据管道进行关联”。在网络中ip与端口号可以唯一的确定一个“数据终端”，两个ip端口对就可以唯一的确定一条数据“管道”，所以要将每一个socket fd和一个ip端口对相关联，从而实现数据的端对端传输。           
> <br/>
> 对于客户端：使用connect函数将本地的fd和远程的ip端口对相关联，组成一条“数据管道”，从而实现数据的传输（本地客户端的socket可以不用特意的设置端口号和ip，系统会自动的分配。当然了，也可以手动的分配）。              
> 对于服务器端：使用bind函数和本地的一个ip和端口号相关联，使得服务器可以监控管道的一段，等待接收数据。          
> <br/>
> 因为网络上有不同的网络协议，所以ip可以是ipv4 也可以是IPv6，而数据报的传输可以是tcp也可以是udp，故sockfd的设置要依据不同的环境做不同的配置。        
> <br/>
> 注意事项：因为网络上传输的数据使用的是大端法，故所有应用于socket的数据都要转化为网络上传输的格式，一般使用htons等函数对数据进行转化。***这一步是必不可少的。`htonl(INADDR_ANY);htons(port);`，sin_family不用转化字节序是因为sin_family用于系统的判断，而sin_addr与sin_port是取自IP和UDP协议层的。***

-	使用socket通信的一般流程（[参考](http://www.linuxhowtos.org/C_C++/socket.htm)）：
-	客户端
	-	Create a socket with the socket() system call
	-	Connect the socket to the address of the server using the connect() system call
	-	Send and receive data. There are a number of ways to do this, but the simplest is to use the read() and write() system calls.（不建议使用这两个函数）
-	服务器端
	-	Create a socket with the socket() system call
	-	Bind the socket to an address using the bind() system call. For a server socket on the Internet, an address consists of a port number on the host machine.
	-	Listen for connections with the listen() system call
	-	Accept a connection with the accept() system call. This call typically blocks until a client connects with the server.
	-	Send and receive data
-	创建一个套接字：

#### 常用函数

-	`int socket(int domain , int type ,int protocol);//#include<sys/socket.h>`return -1 if failed and set errno
-	`uint32_t htonl(uint32_t hostint32);//#include<arpa/inet.h>`
-	`uint16_t htonl(uint16_t hostint16);//#include<arpa/inet.h>`
-	ntohl and ntohs
-	`const char *inet_ntop(int domain , const void *restrict addr , char *restrict str ,socklen_t size);//#include<arpa/inet.h>`//return NULL if failed 
-	`int inet_pton(int domain , const *restrict str , void *restrict add);//in arpa inet.h`return 1 if  successed ,return -1 if failed and 0 if the formate is illegal
-	`in_addr_t inet_addr(const char *strptr) `//直接将数字和点表示的ip（192.168.1.1）转化为无符号长整型，而且不用使用htonl就可以赋予sockaddr。
-	`struct hostent *gethostent(void);//#include<netdb.h>`//return NULL if failed , 使用网络字节序
-   `int shutdown(int sockfd , int how);//#include<sys/socket.h> `//return -1 if failed,0 if successed
-   `int bind(int sockfd , const struct sockaddr *addr ,socklen_t len);//#include<sys/socket.h>`//return -1 if failed ,return 0 if successed 
-   `int getsockname(int sockfd , struct sockaddr *restrict addr , socklen_t *restrict alenp);//#include <sys/socket.h>`//return 0 if successed ,return -1 if failed 
-   `int getpeername(int sockfd , struct sockaddr *restrict addr , socklen_t *restrict alenp)`
-   `int connect(int sockfd , const struct sockaddr *addr , socklen_t len);//socket.h`return 0 if successed return -1 if failed

```
#include<sys/socket.h>
int socket(int domain , int type, int protocol);
//创建一个套接字只是确定了套接字的类型，套接字的很多信息需要使用其他的函数进行设置，如套接字的地址。
```
	-	参数解释：
	-	domain：通信的域(相同的域和相同的类型的socket之间才可通信)
	```
		-	af_inet    ipv4网域
		-	af_inet6   ipv6网域
		-	af_unix    unix域
		-	af_upspec  未指定
	```
	-	type：套接字的类型，不是传输层数据传输的协议，指的是套接字传输数据的类型。
	```
		-	sock_dgram     固定长度的，无连接的，不可靠的文件传输。
		-	sock_raw       跳过传输层，直接与网络层的数据进行通信。必须有超级用户权限
		-	sock_seqpacket 固定长度的，有序的，可靠的，面向连接的报文传输
		-	sock_stream    有序的，可靠的，双向的，面向连接的字节流。sock_seqpacket 和 sock_stream 的区别在于前者的数据长度是固定的。前者读取一次套接字就可以获得另一端发来的完整数据，而后者可能需要多次的读取。
	```
	-	protocol 指定传输层的协议，这个参数要与前两个参数对照选取，因为某一个域下的套接字类型可能只支持一种传输层协议，此时protocol的值为0
	```
		-	ipproto_ip   ipv4网际协议
		-	ipproto_ipv6 ipv6 网际协议
		-	ipproto_icmp 因特网控制报文协议
		-	ipproto_raw  原始的数据包协议
		-	ipproto_tcp  传输控制协议
		-	ipproto_udp  用户数据报文协议
	```

-	限定一个套接字的动作
```
#include <sys/socket.h>
int shutdown(int sockfd , int how);
```
	-	参数解释：
	-	sockfd 套接字描述符
	-	how 选择函数的动作
	```
		-	SHUT_RD   关闭读端，可以写套接字，但不能读
		-	SHUT_WR   关闭写
		-	SHUT_RDWR 关闭读写
	```
	-	虽然可以使用close来关闭一个套接字，但shutdown可以有更多的作用。
-	网络字节序
	-	***TCP/IP协议栈使用的是大端字节序***
	-	大端字节序：高位有效字节放在低位地址的内存内
	-	小端字节序：高位有效字节放在高位地址的内存内（这是比较常见的方式）
	-	网络字节序与本地字节序的相互转化`#include<arpa/inet.h>`：
	```
		-	uint32_t  htonl(uint32_t hostint32);//host to network long int 
		-	uint16_t  htons(uint16_t hostint316);//host to network short int 
		-	同理有ntohl和htons
	```
-	socket 中的地址格式（在头文件netinet/in.h中定义）***在不同系统下，socket地址成员可能是不同的，下面以unix或linux为例***
	-	socket中有几种不同的地址格式用于存放不同域的地址，但这些地址最终都会被强制转化为socket中使用的地址格式struct sockaddr。
	```
	//在linux下，sockaddr的格式为
	struct sockaddr {
		sa_family_t sa_family;//address family
		char 		sa_data[14];//可变长的地址
	};
	```
	-	ipv4域中的地址格式:sockaddr_in（***端口号是16位无符号整型（unsigned short 或in_port_t）***）
	```
	struct in_addr{
		in_addr_t   s_addr;//ipv4 address 	
	};
	struct sockaddr_in       {
		sa_family_t     sin_family;
		in_port_t       sin_port;//网络字节序
		struct in_addr  sin_add;
	};
	```
	-	ipv6域中的地址格式：sockadd_in6
	```
	struct in6_addr{
		uint8_t  s6_addr[16];
	};
	struct sockaddr_in16{
		sa_family_t			sin_family ;
		in_port_t			sin6_port;
		uint32_t			sin6_flowinfo;
		struct in6_addr		sin6_addr;
		uint32_t			sin6_scope_id;
	};
	```
	-	地址格式的转换（机器表示与便于人读的格式之间的转换）头文件 arpa/inet.h
		-	`const char *inet_ntop(int domain , cosnt void *restrict addr, char *restrict str , socklen_t size);`//成功则返回字符串地址，否则返回NULL。
		-	`int inet_pton(int domain ,cosnt char *restrict str , void *restrict addr);`//成功则返回1,格式无效返回0,错误返回-1
		-	domain只支持两个值：AF_INET， AF_INET6 ;字符串的长度可以使用INET_ADDRSTRLEN和INET6_ADDRESTRLEN来表示;对于IPV4而言addr指向的空间要能放下32位整数，而对于IPv6 其要放得下128位整数。
-	地址查寻？？？？？？？？？？？？？？

-	套接字与地址关联
	-	在没有特殊要求的情况下在连接套接字时没必要指定本地套接字的地址和端口号，系统会自动分配。
	-	当服务器监听端口时，其必须绑定地址和端口号：
	```
	#include<sys/socket.h>
	int bind(int sockfd , cosnt struct sockaddr *addr , socklen_t len);//成功返回0,出错返回-1
	//注意在绑定时，端口号要大于1024,否则是需要root权限的
	//一般只能将一个套接字绑定在一个地址上，尽管有些协议允许多重绑定
	```
	-	对于因特网网域，如果IP地址为INADDR_ANY（`<netinet/in.h>`），则socket可以接收系统中所有网卡的所有数据包。
	-	获得指定socket所绑定的地址：
	```
	#include<sys/socket.h>
	int getsockname(int sockfd , struct sockaddr *restrict addr, socklen_t *restrict alenp);//成功则返回0,出错返回-1
	//alenp开始指向的整数表示addr缓冲区的大小，函数执行之后将其置为返回地址的大小，如果返回地址和给定的缓冲区大小不匹配，返回地址会被截断，但函数不会报错。
	```
	-	获得与套接字相连的套接字的地址
	```
	#include<sys/socket.h>
	int getpeername(int sockfd , struct sockaddr *restrict addr, socklen_t *restrict alenp);//成功则返回0,出错返回-1
	```

-	建立连接
	-	对于面向连接的网络服务（如SOCK_STREAM和SOCK_SEQPACKET ），要先建立连接：
	```
	#include<sys/socket.h>
	int connect(int sockfd , const struct sockaddr *add, socklen_t len);//成功则返回0,出错返回-1
	//在这里需要注意的是如果我们没有为sockdf这个socket指定地址，则系统会自动的为其分配地址和端口
	```
	-	为了使程序具有可移植性，在连接失败之后，要关闭使用过的套接字描述符，再重新建立一个，这是历史遗留问题。


