## MinGW ASIO
### ASIO简单说明
-    ASIO一般情况下是header-only，也就是说只要包含ASIO的头文件就可以直接使用了。
-	 ASIO中的对象asio::io_service是线程安全的。
-    在MinGW中使用ASIO是需要定义几个宏，告诉编译器我们使用 ASIO standalone 模式。
    -    以codeblocks为例，在complier flags -> #define 下定义三个宏：
           1.    ASIO_STANDALONE
           2.    BOOST_DATE_TIME_NO_LIB
           3.    BOOST_REGEX_NO_LIB
    -    在linker setting 下的other linker options下添加链接指令：-lws2_32 -lwsock32 
    -    以qtcreater为例在，\*.pro文件中添加下面语句（**一定要放在INCLUDEPATH和SOURCES之前**）： 
```
DEFINES += ASIO_STANDALONE\    
                    BOOST_DATE_TIME_NO_LIB\
                    BOOST_REGEX_NO_LIB\
#LIBS += -lws2_32  -lwsock32 #在windows下要添加这句
#QMAKE_CXXFLAGS+= -std=c++11  #在嵌入式条件下需要这句话告诉编译器使用C++11标准。
```
-    [教程][1]与[参考1][2] [参考2][3] [官方教程][5]

### std::bind （since C++11）
```
using namespace std::placeholders;
void fun(int a , int b);
class C{void fun(int  , int);};
C c;
bind(&fun , 1 , 2)();//方式1
bind(&fun , _1 , _2)( 1 , 2);//与方式1效果相同，using namespace std::placeholders;
bind(&C::fun , &c , _2 , _1)(2 , 1);//绑定类的成员函数，要给出类内成员指针，和指定对象
```
### TIPs
*	ASIO中的spawn协程基于Boost.Coroutine，所以一般想独立使用ASIO时就不使用spawn，使用ASIO原生的协程yield等。
### ASIO overview
*    ASIO支持[同步与异步操作][4]。
*    使用ASIO的程序中至少有一个io_service对象，这个对象是程序与系统I/O之间的接口：`asio::io_service io_service;`
*	 ASIO中的所有IO对象（如socket，deadline_timer等）都要先与io_service这个IO服务对象相关联。
*    以TCP socket为例来说明ASIO的同步概念：
    *    首先建立一个socket（称为I/O对象）并关联到一个io_service上
    *    程序连接目标时IO对象将连接请求提交给io_service对象
    *    io_service对象请求系统执行对应的连接
    *    系统将执行结果反馈给io_service对象
    *    io_service对象将错误信息保存在system::error_code对象中，并将结果反馈给IO对象。
    *    如果代码中没有提供保存错误信息的对象（system::error_code），而且有错误出现则IO对象会抛出异常:
        *    `asio::ip::tcp::socket socket(io_service);` ，因为没有提供保存异常对象的变量，IO对象将把异常抛出。
         *    `socket.connect(server_endpoint, ec);` ，代码中提供了ec来保存异常对象，所以IO对象不会抛出异常。

*    同样以TCP socket为例来说明异步概念：
    *    以异步的方式连接对象：`socket.async_connect(server_endpoint, your_completion_handler);`，第二参数为函数或可执行对象：
        *    `void your_completion_handler(const boost::system::error_code& ec);`
    *    IO对象将请求传递给io_service。
    *    io_service将请求发给系统。
    *    若系统执行完成请求，系统将把执行结果放在一个队列中；io_service将访问这个队列来获取结果。
    *    程序中必须执行io_service::run()成员函数，这样io_service才会检索对应的队列来获取系统的执行结果。
    *    io_service:run()将一直阻塞，直到队列中所有的内容执行完成。io_service会提供一个对应的error_code给handler。

*    有机会看下：The Proactor Design Pattern: Concurrency Without Threads



### 线程和ASIO
*	对于单线程的ASIO，如果有多个异步操作同时完成则ASIO会从中选择一个来运行，然后再运行下一个。所以对于单线程ASIO而言最好不要使异步操作调用的函数执行太长时间，否则会影响其他操作的执行。
*	对于多线程ASIO而言（有多个线程同时调用了函数io_service::run()），如果有多个异步操作同时完成，ASIO会选择空闲的线程来执行这些异步操作所调用的函数。
*	在多线程环境中可能多个线程会调用同一个io_service的run()成员函数，ASIO将平等的对待这些注册到同一个io_service上的handler并以随机的方式唤醒他们。
*	ASIO保证只会在调用io_service::run()的线程中唤醒对应的handler。
*	io_service::strand对象提供了一种互斥方式，所有注册到strand对象中的handler在任意时刻有且只有一个处于运行状态。
    *	普通的互斥量mutex只有在函数运行后才会因互斥而阻塞，而strand会在函数启动前“阻塞”函数。

### io_service
*	post与dispatch的区别：
    *	post将任务放入队列之后就返回了。
    *	dispatch会将任务放入队列，如果当前线程调用了对应io_service中的run()函数，那么dispatch会在任务完成之后再返回。
*	io_service::strand 对象
    *	提供互斥方法，对于“提交”（例如使用strand::wrap方法）到同一个stand对象中的任务而言，同一时刻有且只能有一个在运行。
```
timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));//使用同一个strand
timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
```
    *	当使用strand::post方法将任务提交给strand对象时，所有任务不但互斥，而且执行顺序也是严格按照post顺序来的。


### 一些IO对象
*	较为简单的方式是看：Boost.Asio C++ Network Programming
*	deadline_timer：在创建之时即开始计时。（为了跨平台不使用BOOST库，最好使用steady_timer。）
*	steady_timer：与deadline_timer功能相同，只是其使用的计时器是C++11中的chrono，所以可以更好的跨平台。
	*	有一点需要注意，那就是在创建steady_timer时一定要提供第二个参数，否则异步等待会失效。
*	acceptor：
*	tcp::resolver ,tcp::resolver::query
```
asio::io_service service;
asio::ip::tcp::resolver resolver(service);
asio::ip::tcp::resolver::query query("www.google.com" , "80");
asio::ip::tcp::resolver::iterator ep=resolver.resolve(query);
cout<<(*ep).endpoint()<<endl;
asio::ip::tcp::socket socket(io_service);
asio::connect(socket, endpoint_iterator);
```












[1]:http://www.gamedev.net/blog/950/entry-2249317-a-guide-to-getting-started-with-boostasio/
[2]:http://www.boost.org/doc/libs/1_61_0/doc/html/boost_asio/overview.html
[3]:http://zh.highscore.de/cpp/boost/
[4]:http://www.boost.org/doc/libs/1_61_0/doc/html/boost_asio/overview/core/basics.html
[5]:http://think-async.com/Asio/asio-1.10.6/doc/asio/tutorial.html
