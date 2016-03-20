### 常用指令（基于Ubuntu 14.04 LTS）
-	创建用户：`useradd arm007 -m `，创建用户arm007并为其建立目录。
-	为用户添加密码：`passwd arm007`，为arm007创建密码。
-	查看系统版本：`cat /proc/version`
-	查看磁盘剩余信息：`df -hl`



## 环境搭建
### NFS的配置
-	`sudo apt-get install nfs-kernel-server ` 安装NFS服务
-	`sudo vi /etc/exports` //编辑exports 文件，添加nfs 文件夹目录.
	-	`/home/hjiahu/Desktop/NFS *(rw,subtree_check,no_root_squash,no_all_squash,sync)`注意：在 VMware中与windows共享的硬盘空间无法用于NFS。
	-	` chmod 777 -R /home/hjiahu/Desktop/NFS` //更改权限
-	`sudo vi /etc/default/nfs-kernel-server `//绑定端口
	-	`RPCMOUNTDOPTS=--manage-gids` //改为下面形式
	-	`RPCMOUNTDOPTS="-p 13100" `
-	`sudo service nfs-kernel-server restart `//重启NFS服务，一般会显示4个 ok
-	`sudo mount -t nfs 127.0.0.1:/home/myir/nfs /mnt `//本机测试
-	`mount -t nfs -o nolock,rw 192.168.1.111:/home/hjiahu/Desktop/NFS /mnt/nfs`，使用root权限执行

### Ubuntu配置SSH
-	user:ssh_user pwd:jiahu123

### Ubuntu编译环境的配置
-	安装arm-linux-gcc：`sudo apt-get install arm-linux-gcc*`
-	安装arm-linux-g++：`sudo apt-get install arm-linux-g++*`

## 编译opencv
-	cmake-gui operating system:Linux(大小写也不能错，必须写成Linux,否则cmake无法判断目标系统，版本填写板子上linux系统的版本号如3.12.10，处理器填arm),c:...gcc,c++:...g++,target root:bin （最好是当前系统如ubuntu的/usr）所处的目录。
-	安装x86的工具链
	-	sudo apt-get install build-essential libgl1-mesa-dev 
-	安装Synaptic Package Manager 
	-	启动Synaptic
        -	$sudo synaptic
        -	依次点击Reload, Mark All Upgrades, Apply
		-	安装zlib,png,jpeg
        -	在搜索栏中输入png，mark libpng 12-0 为安装，点击apply,如图，同上，输入jpeg, 安装jpeg62 输入zlib, 安装zlib1g 输入cmake, 安装cmake, cmake-qt-gui
-	 $vim CMakeCache.txt 修改：
	-	CMAKE_C_FLAGS:STRING=-fPIC
    -	CMAKE_EXE_LINKER_FLAGS:STRING=-pthread -lrt
-	opencv支持v4l
	-	sudo apt-get install v4l2ucp v4l-utils libv4l-dev

-	静态编译opencv的指令（静态链接时，库的顺序也是很重要的，放在前面的库一般要依赖其后面的库，库的排列顺序以依赖次序为准，依赖少的放在后面）：
```
arm-linux-gnueabihf-g++ -static  main.cpp -L/home/hjiahu/Desktop/opencv_arm/lib -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_imgproc -lopencv_highgui -lopencv_core  -lopencv_contrib       -lopencv_gpu    -lopencv_legacy  -lopencv_ml  -lopencv_nonfree  -lopencv_objdetect  -lopencv_photo  -lopencv_stitching  -lopencv_superres  -lopencv_video  -lopencv_videostab -pthread -lopencv_ts -llibpng -lzlib -llibjpeg -lrt

```
