web编程基础
=====================================================================

有时间读一下build web application with golang的3.2~3.5节
### 协议介绍
#### URL格式
*	`scheme://host[:port#]/path/.../[?query-string][#anchor]`
	*	scheme         指定低层使用的协议(例如：http, https, ftp)
	*	host           HTTP服务器的IP地址或者域名
	*	port#          HTTP服务器的默认端口是80，这种情况下端口号可以省略。如果使用了别的端口，必须指明，例
	*	path           访问资源的路径
	*	query-string   发送给http服务器的数据
	*	anchor         锚

#### DNS工作原理
1. 输入URL，系统首先在本地hosts文件中寻找映射关系（URL->IP），如果没有，则进行2
2. 查找本地DNS解析器缓存，如果没有则3
3. 查找本地DNS（本地DNS一般是指电脑上网时IPv4或者IPv6设置中填写的那个DNS，也有可能是手工指定的或者是DHCP自动分配的）。如果没有，则4
	*	如果要查询的域名，不由本地DNS服务器区域解析，但该服务器已缓存了此网址映射关系，则调用这个IP地址映射，完成域名解析，此解析不具有权威性。
4. 根据本地DNS服务器的设置（是否设置转发器）进行查询，如果未用转发模式，本地DNS就把请求发至  “根DNS服务器”，“根DNS服务器”收到请求后会判断这个域名(.com)是谁来授权管理，并会返回一个负责该顶级域名服务器的一个IP。本地DNS服务器收到IP信息后，将会联系负责.com域的这台服务器。这台负责.com域的服务器收到请求后，如果自己无法解析，它就会找一个管理.com域的下一级DNS服务器地址(qq.com)给本地DNS服务器。当本地DNS服务器收到这个地址后，就会找qq.com域服务器，重复上面的动作，进行查询，直至找到www.qq.com主机。
5. DNS的查询分为两种：递归和转发

#### HTTP协议
*	http建立在TCP协议之上，默认端口为80
	*	TCP攻击一样会影响HTTP的通讯，如SYN Flood
	*	HTTP/1.1之前每进行一次http传送都需要建立一条新的TCP连接，但自HTTP/1.1之后默认都开启了Keep-Alive保持连接特性，即多个http使用同一条TCP连接。Keep-Alive不会永久保持连接，它有一个保持时间，可以在不同服务器软件（如Apache）中设置。
*	HTTP协议是无状态的，它并不知道两个请求是否来自同一个客户端。为了解决这个问题，  Web程序引入了Cookie机制来维护连接的可持续状态。
*	浏览器第一次请求url时服务器端返回的是html页面，然后浏览器开始渲染HTML：当解析到HTML DOM里面的图片连接，css脚本和js脚本的链接，浏览器就会自动发起一个请求静态资源的HTTP请求，获取相对应的静态资源，然后浏览器就会渲染出来，最终将所有资源整合、渲染，完整展现在我们面前的屏幕上。
	*	网页优化方面有一项措施是减少HTTP请求次数，就是把尽量多的css和js资源合并在一起，目的是尽量减少网页请求静态资源的次数，提高网页加载速度，同时减缓服务器的压力。
*	HTTP请求方法（GET、POST、PUT、DELETE）
	*	**一个URL地址用于描述一个网络上的资源，而HTTP中的GET,POST,PUT,DELETE就对应着对这个资源的查，改，增，删4个操作**
	*	get，GET提交的数据会放在URL之后，以?分割URL和传输数据，参数之间以&相连，GET提交的数据大小有限制（因为浏览器对URL的长度有限制）
*	HTTP状态码（HTTP/1.1协议中定义了5类状态码， 状态码由三位数字组成，第一个数字定义了响应的类别）
	*	1XX 提示信息 - 表示请求已被成功接收，继续处理
	*	2XX 成功 - 表示请求已被成功接收，理解，接受
	*	3XX 重定向 - 要完成请求必须进行更进一步的处理
	*	4XX 客户端错误 - 请求有语法错误或请求无法实现
	*	5XX 服务器端错误 - 服务器未能实现**合法**的请求
*	HTTP请求包，Request包分为3部分：请求行、请求头、主体，后两者之间有个空行
	
		GET /domains/example/ HTTP/1.1 //请求行: 请求方法 请求URI HTTP协议/协议版本
		Host：www.iana.org             //服务端的主机名
		User-Agent：Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.4 (KHTML, like Gecko) Chro
		Accept：text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8 
		Accept-Encoding：gzip,deflate,sdch       //是否支持流压缩
		Accept-Charset：UTF-8,*;q=0.5        //客户端字符编码集
		//空行,用于分割请求头和消息体
		//消息体,请求资源参数,例如POST传递的参数
*	HTTP响应包
		
		HTTP/1.1 200 OK                      //状态行
		Server: nginx/1.0.8                 //服务器使用的WEB软件名及版本
		Date:Date: Tue, 30 Oct 2012 04:14:25 GMT        //发送时间
		Content-Type: text/html             //服务器发送信息的类型
		Transfer-Encoding: chunked          //表示发送HTTP包是分段发的
		Connection: keep-alive              //保持连接状态
		Content-Length: 90                  //主体内容长度
		//空行 用来分割消息头和主体
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"... //消息体

### 表单
*	表单是一个包含表单元素的区域。表单元素是允许用户在表单中（比如：文本域、下拉列表、单选框、复选框等等）输入信息的元素。表单使用表单标签（`<form>`）定义。

		<form>
		...
		input 元素
		...
		</form>