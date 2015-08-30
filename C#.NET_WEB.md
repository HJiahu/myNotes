### 一些专有名词
IIS: Internet信息服务。
URL: uniform resource locator 统一资源定位器。
### 环境的配置
一些问题：
-	[http://jingyan.baidu.com/article/00a07f38ab4f5682d028dcd2.html](http://jingyan.baidu.com/article/00a07f38ab4f5682d028dcd2.html)	

### 第一章 概述
C#和java类似都不是编译语言，都将源代码转化为中间语言在相应的虚拟机（C#的虚拟机是CLR）上运行。    
-	托管代码：在CLR上运行的代码被称为托管代码。
-	托管应用程序：在CLR上运行的程序。

动静态网页：
-	静态网页：只有HTML标记没有程序代码，所有人的访问结果都是一样的。
-	动态网页：含有HTML文本和程序代码，不同的请求服务器会执行代码来生成不同的HTML返回给不同的用户。

B/S和C/S：
-	C/S:client/Server 缺点是当服务器端升级时，客户端也要升级。
-	B/S:browser/server 

动态网页制作技术：
-	ASP  淘汰  微软
-	JSP  sun公司的基于java
-	PHP  免费
-	ASP.NET 微软开发的动态网页制作技术，与ASP没什么关系。

ASP.NET WEB	程序组成：
> 页面后缀为.aspx      
> 

### 第二章 web开发基础
#### HTML 
HTML
> hyper text markup language        
> html 是纯文本

HTML标签(标记)
> 使用< 和> 括起来的标识符   ***标记是不区分大小写的***
> 标记分为单标记和成对标记，其中单标记只有<p>。其他标记类似于<html>...</html>         
> 标签都有自己的属性和属性值，属性的表示形式是标记中的参数选项。例如：        
> `<body text = "blue"  link = "red"...> .... </body>              

HTML文档头和文档体
```
	<html>      <!--使用html包含文件表示这是一个html文档-->
		<head>  <!--整个网页的一些信息，不显示在浏览器正文-->
			<title> ... </title>
		...
		</head>

	<!--网页的主要内容，文档的正文-->
		<body text = "color red or #FF0000" link = "link color" vlink = "link color after view" ...>  
		...
		</body>
	</html>
```

html中颜色可以使用两种表示方法：
-	常量，如  red  black ...
-	RGB表示，如  #FF0000 ...

***常用的heml标记***
-	`<title>...</title>`          位于<head>...</head>之间，显示在浏览器标题栏
-   `<p align=”对齐方式”>`用在段落的开始
-   `<br>` 换行标记
-   `<hr>` 插入水平线
-   `<hn>标题内容</hn>` n用1~6中的数字代替。   例如`<h1>这是最大的标题</h1>`
-	`<font ...>显示的文字 </font>` 
-	`<b>..</b>   <i>..</i>  <u>..</u>  ` 粗体 斜体 下划线

