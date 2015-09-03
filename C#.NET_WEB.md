### 一些专有名词
IIS: Internet信息服务。      
URL: uniform resource locator 统一资源定位器。


ASP.NET的代码内联和后台编码：
-	代码内联：将用户界面和实现逻辑放在同一个文件中。
-	后台编码：将实现逻辑和用户界面放在两个不同的文件中（VS默认的方式）。

***注意***：在访问由asp.net编写的网站时，服务器和浏览器两端都会保存一个字符串用来记录当前页面的状态。这样可以记录浏览器断已发生的动作从而使浏览器知道下一个来自浏览器的动作应该如何进行回应。这个字段是由服务器发给浏览器进行保存的。

ASP.NET的执行过程：
1.	服务器根据用户请求的地址和端口号选择目录，控制权交予aspnet_isapi.dll。
2.	aspnet_isapi.dll是一个借口。控制权交予ASP.NET Work Process
3.	...
8.	创建html网页，并返回给用户。

web窗体处理过程：
1.	页面的初始化。由aspx代码生成html网页，重载网页时仅返回已生成的html，不在初始化。
2.	....

服务器控件，在服务器端运行的控件。
-	HTML服务器控件：与html标签一一对应，在每一个html标记中添加runat="sever"属性，其就会变为服务器控件。
-	web服务器控件：在服务器端运行的一些控件，如验证控件，导航控件...

html事件在浏览器端触发，在浏览器端完成处理。而服务器控件事件是在浏览器端触发，在服务器端处理。


一些控件：
-	TextBox：文本框，可以作为单行文本输入，多行文本输入和password输入。
-	panel：可以作为一些控件的容器，从而实现多个控件的同时隐藏。
-	placeholder
-	RadioButton：单选按钮，可以将多个单选按钮的gtoupnmae设置为相同的名称，这样这些按钮只能选定一个。
-	RadioButtonList：如果需要多个单选按钮，为了方便可以直接使用这个。
-	CheckBox：复选框控件，可以选择多个项。
-	DropDown：下拉菜单。
-	ListBox
-	FileUpload：上载文件。
-	BulleteList：
-	xml控件
-	验证控件，验证用户输入的数据是否合法。

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




### 第七章：ADO.NET初步


### 第九章：成员资格、角色管理与登录控件
ASP.NET的验证方式
-	Windows验证
-	Forms验证（最常用）
-	Passport验证
-	None验证

Forms验证：
> 表单验证（forms验证），通过Forms验证之后服务器会返回一个类似cookie形式的标记来作为用户的身份证明，这样就可以不用重复的输入密码。此时要在web.config中做相关的配置。

```
<configuration>

    <system.web>
      <authentication mode="Forms"/>    <!--启用form身份验证要添加这行-->
      <compilation debug="true" targetFramework="4.0" />
    </system.web>

  <location path="accessableTest">  <!--需要进行权限管理的目录或文件位置-->
    <system.web>   <!--这一行是必须的-->
      <authorization>
        <allow roles="admin"/>   <!--允许读取本文件夹或文件的用户-->
        <deny roles="*"/>   <!--默认情况下所有人是可读取所有文件的，如果不加这一行，未登陆用户易可读取-->
      </authorization>
    </system.web>
  </location>
</configuration>``
```
具体的角色与授权管理见337~339

使用form验证方法的原理：
1.	form验证相当于基于文件，一般是在web.config中配置哪些文件或文件夹是需要进行权限管理的，就像上面的那段代码。
2.	按照一定的步骤来创建角色和用户。

