### 一些专有名词
IIS: Internet信息服务。      
URL: uniform resource locator 统一资源定位器。
### 环境的配置
可以不配置任何的环境，直接在VS2008中写网页并在其中调试，一般而言将vs中调试过的网页直接复制到网站服务器中就可以了。     
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

### 第二章 web开发基础
HTML 
-	HTML hyper text markup language  html 是纯文本

HTML标签(标记)
> 使用< 和> 括起来的标识符   ***标记是不区分大小写的***
> 标记分为单标记和成对标记，其中单标记有`<p>`。其他标记类似于`<html>...</html>`
> 标签都有自己的属性和属性值，属性的表示形式是标记中的参数选项。例如：        
> `<body text = "blue"  link = "red"...> .... </body>`              

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

CSS和div：
-	CSS
	-	css是一种网页外观设计语言，是对HTML的一种补充。css可以实现对html中的元素或者其中的标签进行外观上的更改。虽然说html可以设置标签的一些属性，但相对而css更全面而且可以实现一条css语句控制某一种属性的所有标签。        
	-	css语言可以嵌入到html中，也可以像头文件那样被某一个html文档所引用。
	-	一个html文档中可以嵌入css语句，也可以引用其他的css文件，故一个文档中可能会有位于不同的位值的css语句同时对某一种标签的外观进行控制，故css有复盖原则：以最近的css语句为主。
	-	css的模型就是将所有将更改的对像看作是一个方框，而这个方框也有一些属性。
	-	css定位，显式css方框的位置设置。
-	DIV层
	-	可以认为div层就是一个块，这个块中的显式可以由一个独立的html文件进行控制。***这些层不一定是堆叠关系，更多的是并列***


	
