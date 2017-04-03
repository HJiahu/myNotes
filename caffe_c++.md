caffe C++接口使用配置
===============================================

用vs2013创建caffe工程
-----------------------------------------------
### 编译windows caffe [参考][0]

我选择的是 Visual Studio 2013, CPU only, Python 2.7 Caffe Debug，而且要在自己的电脑上[编译][0]成功。从网页上下载的caffe Debug包中缺少一些依赖包。

我也试过vs2015但最后失败了（可能是因为我的系统同时存在vs2015和vs2013，后来还原系统并只安装vs2013 with update 5，然后就一切正常了）

我使用的pyton是Anaconda 4.2.0 (64-bit)[下载地址][1]

修改build\_win.cmd中大概68~96行之间的内容：CPU\_ONLY=1、CMAKE\_CONFIG=Debug、RUN_INSTALL=1；  
因为我已经下载了依赖包，所以注释download\_prebuilt\_dependencies.py中48行：

    # Download binaries
    print("Downloading dependencies ({}). Please wait...".format(dep_filename))
    #urllib.request.urlretrieve(url, dep_filename, reporthook) #注释这一行，不再重复下载
    if not model_checks_out(dep_filename, sha1):
        print('ERROR: dependencies did not download correctly! Run this again.')
        sys.exit(1)
    print("\nDone.")

执行 scripts/build_win.cmd， 几分钟就好了

我的caffe根目录是：`C:\CNNs\caffe`
### 创建vs2013项目
*	首先创建一个vs2013 C++ win32控制台应用程序的空项目；
*	在配置管理器中将活动解决方案平台改为`x64`
*	将`C:\CNNs\caffe\build\install`中的include文件夹拖至vs2013 解决方案中（上面建立的空项目中）；
*	将caffe根目录下src文件夹中的caffe文件夹（`C:\CNNs\caffe\src`）拖至解决方案（因为我不需要test，所以将caffe文件夹中的test文件夹删除了）；
*	因为文件太多了，可以在vs解决方案的头文件和源文件下新建筛选器并将文件拖进对应的筛选器中；
*	复制caffe根目录tools文件夹下的caffe.cpp 到vs项目文件夹中并以添加现有项的方式将其添加到解决方案（我将使用vs编译caffe.cpp）；

### 修正vs2013项目中的错误
在预处理器定义中定义下面的宏（第一个是caffe中定义的，余下的是可以百度其意义）：

	CPU_ONLY
	_SCL_SECURE_NO_WARNINGS
	_CRT_SECURE_NO_DEPRECATE
	_CRT_NONSTDC_NO_DEPRECATE

在当前vs项目中随便打开一个头文件，有些头文件vs是找不到的，在VC++目录下的包含目录中添加下面内容

	C:\CNNs\caffe\build\libraries\include
	C:\CNNs\caffe\build\libraries\include\boost-1_61
	C:\CNNs\caffe\build\install\include
	C:\CNNs\caffe\src

点击vs2013的编译按钮，可以发现错误：`无法打开文件“libboost_thread-vc120-mt-gd-1_61.lib”`。添加下面的库目录：

	C:\CNNs\caffe\build\libraries\lib

在目录`...\libraries\lib`中我们可以发现`boost_thread-vc120-mt-gd-1_61.lib`但没有`libboost_thread-vc120-mt-gd-1_61.lib`，将前者的名字改为后者即可。下面的lib也一样：

	boost_date_time-vc120-mt-gd-1_61.lib
	boost_filesystem-vc120-mt-gd-1_61.lib

再次编译我们会发现更多的 `无法解析的外部符号` 这都是依赖库没有配置好的原因（添加下面的库目录到vs）：

	C:\CNNs\caffe\build\install\lib
	C:\CNNs\caffe\build\libraries\lib
	C:\CNNs\caffe\build\libraries\x64\vc12\lib

在vs附加依赖项中添加添加下面的库名（这里的opencv库我只添加了必需的，其他opencv库请手动添加）：

	caffe-d.lib
	proto-d.lib
	libprotobufd.lib
	libprotobuf-lited.lib
	libprotocd.lib
	libopenblas.dll.a
	gflagsd.lib
	glogd.lib
	caffehdf5_cpp_D.lib
	caffehdf5_D.lib
	caffehdf5_hl_cpp_D.lib
	caffehdf5_hl_D.lib
	libcaffehdf5_cpp_D.lib
	libcaffehdf5_D.lib
	libcaffehdf5_hl_cpp_D.lib
	libcaffehdf5_hl_D.lib
	opencv_core310d.lib
	opencv_highgui310d.lib
	opencv_imgcodecs310d.lib
	opencv_imgproc310d.lib

将下面的目录添加到系统的环境变量中：

	C:\CNNs\caffe\build\install\bin
	C:\CNNs\caffe\build\libraries\bin

caffe中使用的gtest版本比较低，如果想在自己的系统中使用gtest，要同时把`gtest-all.cpp`和	`gtest.h`放入到工程中

可能需要重新启动电脑使环境变量生效



[0]:https://github.com/BVLC/caffe/tree/windows
[1]:https://repo.continuum.io/archive/Anaconda2-4.3.0.1-Windows-x86_64.exe