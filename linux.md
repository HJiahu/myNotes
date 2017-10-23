### CPU分类
*	i386：
*	i586：Intel Pentium MMX与AMD k6年代的CPU
*	i686：intel Celeron与AMD k7年代的**32位CPU**
*	x86_64：目前的64位CPU的统称

### 系统结构
*	由里到外：硬件、核心、系统调用、应用程序

### 基本概念
*	Linux 内的所有数据都是以文件的形态来呈现的
*	在 Linux 系统中，每个装置都被当成一个文件来对待；
	*	几乎所有的硬件装置文件都在/dev 这个目录内；
*	正常的实体机器大概使用的都是  /dev/sd[a-]  的磁盘文件名，至于虚拟机环境底下，为了加速，可能就会使用  /dev/vd[a-p]  这种装置文件名喔！
*	由于 SATA/USB/SAS 等磁盘接口都是使用 SCSI 模块来驱动的，  因此这些接口的磁盘装置文件名都是/dev/sd[a-p]的格式。

#### 磁盘分区
*	MBR（maser boot record)中包含两个部分（MBR只是一个位置的称呼）：主要启动记录区、分区表。其中分区表只有64字节，只能保存4个组分区信息（每个扇区的起始柱号与结束柱号）。但因为可以在每个分区前保存本分区的逻辑分区信息，所以理论上以MBR为例，我们可以把硬盘分无数个分区。MBR中的分区有两种，主分区与逻辑分区，具体的分辨方法很简单。
	*	MBR中每个分区记录只有16字节所以无法获得分区大于2.2T的分区，且MBR方式也无法完全利用大于2.2T的硬盘；
	*	MBR只有一个区块，所以如果被破坏了硬盘难以恢复；
	*	MBR每个分区容量最大为：`2^32 * 512 = 2T`,MBR使用32位地址。
	*	MBR内存放的开机管理程序仅仅446字节；

*	GPT（GUID partition table）:以LBA（Logical Block Address）作为基本划分，LBA的大小可以设定。第一个LBA称为LBA0，GPT使用了34个LBA来记录分区信息，并使用整个磁盘最后33个LBA作为分区信息备份。为了与MBR相容，LBA0作为传统的MBR区域，但LBA0最后几个字节即MBR分区信息记录区内会放入特殊的标志用于区分当前硬盘的分区格式为GPT。（GPT一般可以对磁盘分128个区）
	*	对于GPT，每个LBA中有四个分区记录，所以一般而言每个分区记录可以有不少于512/4=128个字节。因为GPT中有32个LBA用于保存分区信息所以GPT一般最多可以分128个分区。
	*	GPT分区表一个槽最大容量约为`2^64 * 512 = 2^33 T `，GPT使用64位地址；
	*	linux安装时可以强制使用GPT分区方式；

#### 开机过程
##### BIOS（传统）
1.  BIOS：开机主动执行的韧体，会认识第一个可开机的装置； 
2.  MBR：第一个可开机装置的第一个扇区内的主要启动记录区块，内含开机管理程序； 
3.  开机管理程序(boot loader，位于MBR中)：一支可读取核心文件来执行的软件； 
4.  核心文件（由开机管理程序载入内存中）：开始操作系统的功能... 
##### UEFI（为了取代传统的BIOS，UEFI一般使用C语言来开发）
*	UEFI相当于一个小型的操作系统

### 权限管理
*	权限管理内容：

		-rw-r--r--.     1     root     root    1864  May  4 18:01 initial-setup-ks.cfg
        [[文件类型]    [连接数][所有者] [所属群组] [大小] [修改时间]    [文件名]
         [所有者权限]
         [群组权限]
		 [其他使用者权限]]
*	rwx（421）的意义
	*	文件
		*	r：读
		*	w：更改内容
		*	x：如果是可执行文件，则可执行
	*	目录（目录也是一种文件，其中包含了目录中文件或子目录的名称等）
		*	r：具有读取目录结构列表的权限
		*	w：具有改动该目录结构列表的权限（建立、删除、更名、移动。如果没有x权限，左边的动作依旧无法实现。）
		*	x：具有进入该目录成为工作目录的权限（例如cd进入当前文件夹）
*	chown、chgrp、chmod
*	umask：用户创建文件夹与文件的默认权限，umask显示的是去除的权限，例如umask返回0002则表示其他用户没有写的权限
*	除了常见的rwx属性，linux在Ext2/3/4传统文件系统上还有其他隐藏的属性，一般使用chattr与lsattr来实现设定与查询，xfs仅支持部分的隐藏属性。
*	特殊权限
	*	set UID：状态：『-rwsr-xr-x』，此时就被称为  Set UID，简称为  SUID  的特殊权限。
		*	SUID  权限仅对二进制程序(binary program)有效； 
		*	执行者对于该程序需要具有  x  的可执行权限； 
		*	本权限仅在执行该程序的过程中有效  (run-time)； 
		*	执行者将具有该程序拥有者  (owner)  的权限。
	*	Set GID：  s  在群组的  x  时则称为  Set GID，其功能与SUID类似，只不过对应的是群组。
		*	SGID  对二进制程序有用； 
		*	程序执行者对于该程序来说，需具备  x  的权限； 
		*	执行者在执行的过程中将会获得该程序群组的支持！
	*	Sticky Bit ：SBIT  目前只针对目录有效
		*	当用户对于此目录具有  w, x  权限，亦即具有写入的权限时
		*	当用户在该目录下建立文件或目录时，仅有自己与  root  才有权力删除该文件
	*	SUID为4、SGID为2、SBIT为1
	*	chmod 4755 filename  //第一个4用于设定SUID，其他的类似
		*	`chmod u=rwxs,go=x test`
		*	`chmod g+s,o+t test`
### FHS文件标准定义的一些目录
*	参加鸟叔的232页
*	usr：unix software resource
#### 环境变量
*	环境变量PATH
	*	系统会依照 PATH 的设定去每个 PATH 定义的目录下搜寻文件名为 ls 的可执行文件，  如果在 PATH 定义的目录中含有多个文件名为 ls 的可执行文件，那么先搜寻到的同名指令先被执行。
	*	echo $PATH 来看看到底有哪些目录被定义出来了（ PATH  前面加的  $  表示后面接的是变量）
	*	不同身份使用者预设的 PATH 不同，默认能够随意执行的指令也不同
	*	添加路径到PATH中：`PATH="${PATH}:/root"`，把路径`/root`添加到PATH中
### 常用软件
*	SAMBA：文件分享软件
*	DHCP

### 常见指令
*	who：查看在线用户
*	netstat：联网状态，例如`netstat -a`
*	ps：显示程序的执行状态，例如：`ps -aux`
*	su - ,获得root权限（centos）
*	sync：将内存中的数据同步到硬盘中。一般的关机与重启指令都会调用sync
*	chmod：
	*	`chmod [u g o a] [+ - =] [r w x] file or dir`
	*	`chmod u=rwx,g=rx,o=r filename`，u：user（ower）、g：group、o：others
	*	`chmod 777 .bashrc `
*	chgrp：`chgrp [-R] users initial-setup-ks.cfg `
*	chown：`chown [-R] 账号名称:组名 文件或目录 `
*	cat：由第一行开始显示文件内容 
*	tac：从最后一行开始显示，可以看出 tac 是 cat 的倒着写！ 
*	nl：显示的时候，顺道输出行号！ 
*	more：一页一页的显示文件内容 
*	less：与 more 类似，但是比 more 更好的是，他可以往前翻页！ 
*	head：只看头几行
*	tail：只看尾巴几行 
*	od：以二进制的方式读取文件内容，od [-t TYPE] 文件
	*	a       ：利用默认的字符来输出； 
    *	c       ：使用 ASCII 字符来输出 
    *	d[size] ：利用十进制(decimal)来输出数据，每个整数占用 size bytes ； 
    *	f[size] ：利用浮点数(floating)来输出数据，每个数占用 size bytes ； 
    *	o[size] ：利用八进制(octal)来输出数据，每个整数占用 size bytes ； 
    *	x[size] ：利用十六进制(hexadecimal)来输出数据，每个整数占用 size bytes ；
*	touch：修改文件中的时间属性，例如修改时间，创建时间等
*	file：获得文件的类型
*	which：搜索脚本文件的位置，`which ls`
*	whereis：`whereis [-bmsu] 文件或目录名 `，在特殊的文件夹中找对应的文件。whereis比find速度快，因为find是寻找一个文件夹下所有的子文件夹，而whereis只查找指定的几个文件夹。当无法使用whereis找到对应文件时再使用find。`whereis -b ls`只会找名为ls的二进制文件而不找文本。
*	locate：依据  /var/lib/mlocate  内的数据库记载，找出用户输入的关键词文件名。不同发行版本的系统会不定时更新一个数据库，这个数据库记录了当前文件系统中所有的文件，所以locate执行的速度很快。因为数据库的更新有很长的时间间隔，所以有时候新的文件使用locate指令是无法找到的，此时可以使用指令`updatedb`更新这个数据库。
*	updatedb：根据  /etc/updatedb.conf  的设定去搜寻系统硬盘内的文件名，并更新  /var/lib/mlocate  内的数据库文件
*	find：最复杂的查找指令，具体用法查看man手册