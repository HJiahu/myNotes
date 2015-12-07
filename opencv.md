本文摘自：OpenCV2 cooking book
-	目录 <span id="Index"/> 
	-	[第一章 简介](#1)           
	-	[第二章 像素的操作](#2)          
	-	[第三章 用类来处理图片](#3)
	-	[第四章 用直方图来描述像素](#4)



### 第一章：  2015-09-06 07:57:40 <h1 id="1"></h1> 
introduce opencv2.0
opencv使用的名字空间是cv，例如调用显示image的函数的语法可以是：cv::imshow() 
> //在opencv的C接口中使用下面这个函数来载入图像，Ipl表示一个intel的库名，P29                
// IplImage* iplImage = cvLoadImage("c:\\img.jpg");             
//可以很方便的将iplImage指向的C 结构体转化为Mat类：               
//cv::Mat image4(iplImage,false);//false 表示与原变量共享图片数据

-	cv::Mat img //  Mat is a class 。
> Mat 使用了引用计数和浅复制，为了实现深复制，使用方法`void img.copyTo(cv::Mat img_1) const;`或者深度拷贝函数`cv::Mat Mat::clone() const;`         
> ***img.data***  是指向图像存储空间的指针，使用这个参数可以测试图片是否被正确载入。          
> we can create matrix data by Mat :         
> `cv::Mat img(240,320,CV_8U,cv::Scalar(100));`                   
> 为了实现浅偶合，因为Mat类的浅复制问题，最好不要在类中返回一个Mat类，这样和多时侯会造成对像之间的一些影响，增加类代码的复杂度：
> ```
> class Test{
> public:
>	 Mat GetImg(){return img;}   //最好不要直接返回类中的Mat类，可以使用其他函数例如Mat.copyTo(Mat dst);
> private:
> 	Mat img;
> }
> ```

-	cv::Mat_<> matNmae;//cv::Mat_ 是一个类的模板，在已知图像的格式的时候使用这个模板可以简化一些操作。因为在Mat_ 中定义了一些Mat类中没有的操作和重载的运算符。
> cv::Mat_<uchar> img;//可以使用img(x ,  y)来对像素进行赋值。

-	cv::namedWindow("Original Image"); // define the window
-	cv::imshow("Original Image", image); // show the image
-	Mat imread( const string& filename, int flags=1 ); 
-	cv::imwrite(filename , Mat,...)
-	cv::flip(Mat src ,Mat dst,int flipcode)    //if flipcode == 0 vertical if `flipcode > 0` horizontal ,if `flipcode < 0` ,both
-	cv::waitKey(int delay = 0) //default ,this fun will wait for ever if no key is pressed ,if delay is not 0...          
-	cv::Mat::reshape(...)  对图像维度和其他参数的更改。

### 第二章 像素的操作 [\[目录\]](#Index) <span id="2"/> 
-	some functions in this capture
```
cv::Mat::at<cv::Vec3b>(x, y)[];//返回的是一个左值
cv::Mat_<uchar> img;//包含了cv::Mat 中没有的一些成员函数
cv::Mat::isContinues();//是否有padding
cv::Mat::step;//给出每行的字节数（包含padding），而不是像素的个数
uchar cv::Mat::data;//给出保存图片的内存的第一个字节地址，注意返回的指针类型为uchar *
cv::elemSize();//返回每个像素的字节数
cv::Mat::cols;//返回右值
cv::Mat::rows;
uchar *cv::Mat::ptr<uchar>(y);//返回第y行首元素指针
int cv::Mat::channels();
cv::Mat cv::clone(void);//返回深度复制的副本
cv::Mat::create(rows , cols , img.type());//如果当前mat对象中的数据和create中的参数是相同的，则create不做任何的操作。***creat函数创建的图像是continue的·***
itreator<???> cv::MatItreator_<> it;
itreator<> cv::Mat_<>::itreator it;//这两个迭代器都有对应的常量型迭代器。
cv::Mat::begin<>() ;//
cv::Mat::end<>();//很明显Mat中的begin和end迭代器都是模板，但使用cv::Mat_时就可以不使用指明类型。
cv::getTickCount();
cv::getTickFrequency();
static_cast<double> expression;//强制类型转化。

```

-	对于一个灰度图而言，每一个元素代表一个像素的灰度值，其中0表示黑色，255表示白色。
> 利用cv::Mat的构造函数，我们可以用不同的构造函数来创建不同的的图像，如灰度图，彩色图...

-	srand()和rand()在头文件cstdlib中，time()在头文件ctime中。srand(time(NULL))

-	`cv::Mat::at<typename>(int i , int j)`   //效率较差
-	`cv::Mat::at<uchar>(x , y)`
-	`cv::Mat::at<cv::Vec3b>(x , y)[]`
> 使用`cv::Mat_<typename >`类可以简化某些操作，例如在`Mat_`中重载了运算符 () ：`cv::Mat_::operator()(int i , int j);`与`cv::Mat::at()`有相同意思。

-	`uchar * data Mat::ptr<typename>(int i)`   //给出图片第i行的内存首地址。
-	在opencv中，彩色的三通道图片的像素中三个通道的顺序是：***BGR***，blue蓝色在第一个字节。
-	***因为效率问题（内存对齐，增加数据的传输速度），图片在内存中存储时其行的像素数可能与图像的实际行的像素数不同，一般在内存中数据对其会增加数据的传输速度。所以我们不能认为图像的存储是连续的。***
> 在mat类中，***isContinuous()***方法给出了图像在内存中是否连续存储，即是否有padding。rows属性给出图像的真实行数，cols给出真实列数，那么在cols中是不包含系统为了效率额外添加的像素（额外添加的像素时不会显式出来的）。step变量给出每行的字节数（包含padding），elemSize给出每个像素的字节数。total()给出图片的像素总数。

```
	void colorReduce(cv::Mat &image, int div=64) {
		int nl= image.rows; // number of lines
		int nc= image.cols ; // number of columns
		// is it a continous image
		if (image.isContinuous()) {
			// then no padded pixels
			nc= nc*nl;
			nl= 1; // it is now a 1D array
		}
		//div ～= 2^n  约等于 
		int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
		// mask used to round the pixel value
		uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0
		// for all pixels
		for (int j=0; j<nl; j++) {
			// pointer to first column of line j
			//在不考虑效率的情况下，我们可以使用迭代器来访问像素   P49
			uchar* data= image.ptr<uchar>(j);
			for (int i=0; i<nc; i++) {
				// process each pixel ---------------------
				//p_row[j] = p_row[j]/n*n + n/2;//这里的运算不会被编译器优化（化简）
				//p_row[j] = p_row[j] - p_row[j]%n +n/2;  this is slower
				//如果我们限定n的取值是2的整数倍，那么效率最高的方法是位运算：
				*data++= *data&mask + div/2;//&的优先级在关系运算符之后逻辑运算符之前
				*data++= *data&mask + div/2;
				*data++= *data&mask + div/2;
				// end of pixel processing ----------------
			} // end of line
		}
	}

使用运算符重载的版本：
image=(image&cv::Scalar(mask,mask,mask)) + cv::Scalar(div/2,div/2,div/2);

```
上面的函数将直接在源数据上进行操作。为了不在源图进行操作我们可以创建一个新的Mat，例如：
```
cv::Mat img = result;
result.creat(img.rows , img.cols, img.type());//这个函数创建的图像是没有padding的，不考虑效率问题。而且如果result已经有了和参数相同的图片存储区，那么这个函数将什么都不做。
```
P49页讲述了如何使用迭代器来访问像素。

为了测试程序的性能，opencv提供了cv::getTickCount()和cv:getTickFrequency()两个方法，前者获得从开机开始到当前为止cpu的tick数，而后者就获得了cpu的时钟频率。在测试程序前后分别使用getTickCount()来获得一个tick数，两者相减即为间隔tick数，再除以频率即得时间。

像素的临近像素读取：2015-09-13 08:33:34          
-	锐化操作：`sharpened_pixel= 5*current-left-right-up-down;` 具体的操作是对源使用三个指针，对目的图像使用一个指针。P56
-	`cv::saturate_cast<typename>(...) `防制数据的溢出，例如 `cv::saturate_cast<uchar>( data )` 将data的值限制在0～255。
-	cv::Mat::create(cv::Mat::size() , cv::Mat::type()) 要么创建一个新的存储区（无padding），要么就不做任何事情（已存在满足要求的存储区）。
-	cv::Mat::row(int n)::setTo(cv::Scalar(0 , 0 , 0));
-	***使用已经存在的函数来构建锐化函数：***
> `cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0)`            
> `kernel.at<float>(i , j) = ...`         
> `cv::filter2D(img , dst , img.depth() , kernel)`   

***图片的叠加***       
```
	// c[i]= a[i]+b[i];
	cv::add(imageA,imageB,resultC);
	// c[i]= a[i]+k;
	cv::add(imageA,cv::Scalar(k),resultC);
	// c[i]= k1*a[1]+k2*b[i]+k3;
	cv::addWeighted(imageA,k1,imageB,k2,k3,resultC);
	result= 0.7*image1+0.9*image2;  //图像运算非重载
	// c[i]= k*a[1]+b[i];
	cv::scaleAdd(imageA,k,imageB,resultC);
```


在opencv中有很多直接对图像像素进行处理的函数，而且这些函数大部份都有对应的运算符重载函数。在这里不一一列出，具体见API 手册。

***获得有色图像不同的颜色通道***
```
	// create vector of 3 images
	std::vector<cv::Mat> planes;
	// split 1 3-channel image into 3 1-channel images
	cv::split(image1,planes);
	// add to blue channel
	planes[0]+= image2;//add image2 to the blue channel of image1

	// merge the 3 1-channel images into 1 3-channel image
	cv::merge(planes,result);
```

***ROI***
> Region of interset     
> `cv::Mat roi_img = img(cv:Rect(x , y ,length ,height)`            
> `cv::Mat roi_img = img(cv::Rang(from , to) , cv::Rang(from ,to)`        
```
	// define ROI
	imageROI= image(cv::Rect(385,270,logo.cols,logo.rows));
	// load the mask (must be gray-level)
	cv::Mat mask= cv::imread("logo.bmp",0);
	// copy to ROI with mask
	logo.copyTo(imageROI,mask);
```

### 第三章 用类来处理图片  <span id="3"/> [\[目录\]](#Index)  
-	City block distancee ：出租车距离，曼哈顿距离。形像的说“方格距离”
-	Enclidean norm ：欧几里德距离，两点之间的距离。
	-	`cv::norm<int , 3>(...);`
-	***对于库中已经存在的重载运算符，有时侯要注意他们的行为，例如对于两个Vec3u型的数据a和b，c=a-b中减号 - 中已经调用了saturate_cast()函数来防制溢出。这点要注意。***

***设计模式***
1. 策略设计模式（strategy pattern）：简单的说就是将方法封装到类中。
2. 单态模式：
3. MVC模式：modle-view-controler        GUI P84

**颜色空间的转化**
-	The Structure and Properties of Color Spaces and the Representation of Color Images  :a useful book
-	BGR ，BGR  is not a perceptually uniform color space .
-	***CIE L*a*b* 颜色空间是一个对于人眼而言的线性颜色空间。***
	-	L:0~100    a,b:-127 ~ +127
-	cv::cvtColor(tmp, tmp, CV_BGR2Lab);//用于转化颜色空间。
	-	cv::cvtColor(color, gray, CV_BGR2Gray);
	-	CV_BGR2YCrCb


### 第四章 用直方图来描述像素  <span id="4"/> [\[目录\]](#Index) 
-	`void calcHist( const Mat* arrays, int narrays, const int* channels, const Mat& mask, MatND& hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false );`
> 

-	`void calcHist( const Mat* arrays, int narrays, const int* channels, const Mat& mask, SparseMat& hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false );`

-	`cv::threshold(cv::Mat sor_img,cv::Mat threshold_img,60,255,cv::THRESH_BINARY)`a




 
