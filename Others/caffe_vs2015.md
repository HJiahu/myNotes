*	首先使用源码按照官方的方式编译Debug版Caffe，我们需要编译后所生成的如下文件：
	*	caffeproto-d.lib
	*	caffe.pb.h
*	编译完caffe后将install文件夹下的include文件夹复制出来与caffe源码（位于根目录中src目录下）一起放在同一个文件夹caffe_src下（这样做是为了方便。只有编译后的include文件夹下才有caffe.pb.h文件）。`caffe_src`的结构如下:
	
		- caffe_src 
			- include
				- caffe
					- layers
					- proto
						- caffe.pb.h
					- util
					...
			- src
				- caffe
					- layers
					- solvers
					- util
					...
*	创建vs控制台空项目（**注意将解决方案平台设置为x64**，而不是x86），将上面caffe_src中所有的代码都添加当前项目中（注意：所有代码包含子目录中的代码，为了方便可以在项目中添加新的筛选器，便于文件的管理）。
*	将对应的依赖文件添加到项目中
	*	依赖的头文件
		*	`I:\learn_caffe\learn_caffe\caffe_src\include`，这个就是上面提到的从install文件夹中复制出来的include目录
		*	`C:\***\.caffe\dependencies\libraries_v140_x64_py35_1.1.0\libraries\include`，这个和下面的内容源于编译caffe时自动下载的依赖包。
		*	`C:\***\.caffe\dependencies\libraries_v140_x64_py35_1.1.0\libraries\include\boost-1_61`
	*	在预处理定义中添加如下内容
			
				CPU_ONLY
				_SCL_SECURE_NO_WARNINGS
				_CRT_SECURE_NO_DEPRECATE
				_CRT_NONSTDC_NO_DEPRECATE
	*	库目录(**将上面提到的caffeproto-d.lib也复制到下面的文件夹中**)
		*	`C:\***\.caffe\dependencies\libraries_v140_x64_py35_1.1.0\libraries\lib`
		*	为了方便，我使用我自己编译的opencv库，因为只要添加一个库就好：opencv_world320d.lib，同样要把对应的库文件夹添加到项目中。
		*	所有依赖库文件如下所示（其实我并不知道哪些是必须的所以就把能加的都加上去了）：
				
				caffeproto-d.lib
				opencv_world320d.lib
				boost_chrono-vc140-mt-gd-1_61.lib
				boost_date_time-vc140-mt-gd-1_61.lib
				boost_filesystem-vc140-mt-gd-1_61.lib
				boost_system-vc140-mt-gd-1_61.lib
				boost_thread-vc140-mt-gd-1_61.lib
				boost_timer-vc140-mt-gd-1_61.lib
				libopenblas.dll.a
				caffehdf5_D.lib
				caffehdf5_cpp_D.lib
				caffehdf5_hl_D.lib
				caffehdf5_hl_cpp_D.lib
				caffezlibd.lib
				caffezlibstaticd.lib
				gflagsd.lib
				glogd.lib
				leveldbd.lib
				libboost_chrono-vc140-mt-gd-1_61.lib
				libboost_system-vc140-mt-gd-1_61.lib
				libboost_timer-vc140-mt-gd-1_61.lib
				libcaffehdf5_D.lib
				libcaffehdf5_cpp_D.lib
				libcaffehdf5_hl_D.lib
				libcaffehdf5_hl_cpp_D.lib
				libprotobufd.lib
				libprotocd.lib
				lmdbd.lib
				snappy_staticd.lib
				snappyd.lib

*	在编译的时候系统会提示无法打开lib*.lib文件，我的系统中主要是boost中的一些lib。其实这些lib在文件夹中是存在的只是命名的方式不对。将库文件夹中对应的lib文件前面加上lib三个字母就可以了。例如我的系统中提示找不到`boost_thread-vc140-mt-gd-1_61.lib`，在同一个文件夹中创建一个副本并重新命名为`libboost_thread-vc140-mt-gd-1_61.lib`就行了。
*	添加一个main函数后就可以一步一步调试caffe代码了（我直接从源代码tools文件夹中把caffe.cpp复制出来作为调试入口文件）。