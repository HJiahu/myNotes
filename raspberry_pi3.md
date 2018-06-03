### 系统相关
#### 修改SSH密码
*	直接在控制台输入`sudo passwd pi`即可修改当前用户的密码

#### 修改hostname
*	`sudo vim /etc/hostname`

### 一些常见软件的安装指令
*	7z，`sudo apt-get install p7zip-full`
*	cmake,`sudo apt-get install cmake cmake-gui`
*	右击打开终端，`sudo apt-get install nautilus-open-terminal`(树莓派无效)

### 远程桌面
#### 使用VNC
*	在树莓派上安装VNC

		sudo apt-get install tightvncserver
		vncserver  # 启动vncserver，记录vnc的端口号，一般从1开始
		sudo ifconfig  #查看地址

*	windows上安装VNC client [TightVNC][1]
*	使用上面获得的端口用tightvnc连接树莓派，例如：`192.168.1.105:1`

### 在树莓派上创建NFS【[参考][2]】
*	树莓派上安装NFS服务

		sudo apt-get install nfs-common nfs-server -y
		sudo mkdir /mnt/nfsserver  # 创建一个共享的文件夹
		sudo chmod a+rw -R NFS #修改权限使得其他人可以读写当前文件夹
		sudo vim /etc/exports  #修改配置
		
		#将下面的一行内容写进exports中
		/mnt/nfsserver *(rw,sync)
		/mnt/nfsserver 192.168.1.34 *(rw,sync)
		/mnt/nfsserver 192.168.1.10/24 *(ro,sync)

		sudo exportfs  # 读取新配置
        # 重启更靠谱

*	windows10下挂载NFS

		mount 192.168.1.105:/mnt/nfsserver X:   # X: 是windows下的盘符

### 安装FTP服务（以centos为例）

	yum -y install vsftpd
	service vsftpd start  # 启动
	service vsftpd stop   # 停止
	service vsftpd restart# 重启


*	添加用户 `vi /etc/vsftpd/vsftpd.conf  # 配置FTP文件`

		#chroot_list_enable=YES
		# (default follows)
		#chroot_list_file=/etc/vsftpd.chroot_list
		
		改为
		chroot_list_enable=YES
		# (default follows)
		chroot_list_file=/etc/vsftpd/chroot_list

		# 添加ftp用户
		useradd -d /home/wwwroot/ftpuser -g ftp -s /sbin/nologin ftpuser
		# 设置用户口令
		passwd ftpuser 

*	编辑文件 `chroot_list` ：`vi /etc/vsftpd/chroot_list`，将用户名写进当前文件，每行一个用户



### caffe依赖库
	
	sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libhdf5-serial-dev protobuf-compiler
	sudo apt-get install libhdf5-mpi-dev
	# sudo apt-get install libopencv-dev 可以额外安装自己编译的版本
	sudo apt-get install --no-install-recommends libboost-all-dev
	sudo apt-get install libatlas-base-dev
	sudo apt-get install libopenblas-dev
	sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev
	sudo apt-get install python-dev

#### 安装caffe-nnpack的问题
*	修改`cmake/Dependencies.cmake`中的内容，将`list(APPEND Caffe_LINKER_LIBS ${HDF5_LIBRARIES})`修改为`list(APPEND Caffe_LINKER_LIBS ${HDF5_LIBRARIES} ${HDF5_HL_LIBRARIES})`
















[1]:http://tightvnc.com/
[2]:https://www.htpcguides.com/configure-nfs-server-and-nfs-client-raspberry-pi/