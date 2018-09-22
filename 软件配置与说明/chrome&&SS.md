# SS&Chrome

## 所需软件和插件

*	SwitchyOmega：chrome 使用的代理插件
*	shadowsocks server&client：部署在服务器上的代理软件

## 需求说明

因为某些规定不能在个人电脑上安装VPN，所以退而求其次在chrome浏览器上安装VPN插件。换汤不换药，这也是无奈之举

## 软件说明

### shadowsocks server

按照[官网][1]的说明在服务器上安装SS。这是使用VPN进行FQ的核心，请在国外搭建SS服务

这里对安装进行一个简单提示（仅支持python2.6 &2.7）：

	pip install shadowsocks

随意在一个位置创建一个文件，这里以config.json为例，写入余下内容：

	{
		"server":"0.0.0.0",
	
		"port_password":{
			"your port":"your pwd",
			"your port":"your pwd"
		},
	
		"timeout":300,
		"method":"aes-256-cfb"
	}     

这里只说明`por_password`字段中的内容进行说明：

ss server每一个端口支持client的个数是有限的，所以如果你有多个client需要连接ss server，那就设置多个ss server 端口和密码

使用指令启动ss server：

	ssserver -d start -c config.json

ssserver指令的使用可以键入`ssserver --help`查看

一般而言如果没有特殊规定，直接在自己电脑上安装shadowsocks-client就可以完成WQ大业，所以下面的内容也就不用看了

### shadowsocks client

使用上面的指令（`pip install shadowsocks`）安装ss server之后，client已经安装好了。

ss client命令为sslocal

**请不要在同一台服务上同时启动ss server和ss client**。虽然不知道原因，但有一个奇怪的现象，同时启动client和server之后server将无法提供服务

好在我有两台云服务器，一台国内的，一台国外的 :)

在另一台机器上安装ss server，然后建立一个文件（以ss-client.json为例），写入余下内容：

	{
		"server":"your ss server IP",
		"server_port":***,
		"password":"ss server pwd",
		"method":"aes-256-cfb",
		"local_address":"0.0.0.0",
		"local_port":your socks5 port,
		"timeout":600
	}

前4行就不解释了。chrome进行socks5代理时是无法实现认证的，也就是说不能加密。你只能隐藏自己的socks5代理端口，保佑不要被坏人利用

使用指令启动sslocal：

	sslocal -d start -c ss-client.json

### SwitchyOmega

在chrome中安装SwitchyOmega插件，选择socks5代理，然后输入sslocal的IP和端口号，然后就可以WQ了

## 其他

使用SwitchyOmega进行WQ大业实数无奈，所以我给ss server设定了两个端口，一个用户使用ss client代理，一个使用ss client代理后提供socks5代理

这里使用socks5代理主要原因是：懒......

不想折腾了，希望没有人发现我用的代理端口...... 





[1]:https://shadowsocks.org/en/index.html

