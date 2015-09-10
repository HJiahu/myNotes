Notes for opencv .
OpenCV2 cooking book

### 第一章：  2015-09-06 07:57:40
introduce opencv2.0
opencv使用的名字空间是cv，例如调用显示image的函数的语法可以是：cv::imshow()
```
int main( int argc, char** argv ) 
{
	cv::Mat img;
	img = cv::imread("../Imags/lena.jpg",1);
	//在opencv的C接口中使用下面这个函数来载入图像，Ipl表示一个intel的库名，P29
	// IplImage* iplImage = cvLoadImage("c:\\img.jpg");     
	//可以很方便的将iplImage指向的C 结构体转化为Mat类：
	//cv::Mat image4(iplImage,false);
	//cvReleaseImage(&iplImage);//必须使用明确的语句来清除IplImage结构
	cv::namedWindow("Image_1",cv::WINDOW_AUTOSIZE);
	while (1) {
		cv::imshow("Image_1", img);  //显式窗口和保存图片的内存是相关联的。
		cv::waitKey(0);
		cv::flip(img, img, 1);
	}
}
```
-	cv::Mat img //  Mat is a class 。
> Mat 使用了引用计数和浅复制，为了实现深复制，使用方法img.copyTo(cv::Mat img_1)             
> img.size().height                
> img.size().width             
> ***img.data***  是指向图像存储空间的指针，使用这个参数可以测试图片是否被正确读取。          
> we can creat matrix data by Mat :         
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

-	cv::namedWindow("Original Image"); // define the window
-	cv::imshow("Original Image", image); // show the image
-	Mat imread( const string& filename, int flags=1 ); 
-	cv::imwrite(filename , Mat,...)
-	cv::flip(Mat src ,Mat dst,int flipcode)    //if flipcode == 0 vertical if flipcode == 1 horizontal 
-	cv::waitKey(int delay = 0) //default ,this fun will wait for ever if no key is pressed ,if delay is not 0... 

### 第二章
-	对于一个灰度图而言，每一个元素代表一个像素的灰度值，其中0表示黑色，255表示白色。
> 利用cv::Mat的构造函数，我们可以创建不同的构造函数来创建不同的的图像，如灰度头，彩色图...
```
	#include <iostream>
	#include <cstdlib>
	#include <ctime>
	#include <opencv2/highgui/highgui.hpp>
	void salt_image(cv::Mat  &img , int n)
	{
		srand(time(NULL));
		for (int i = 0; i < n ; i++) {
			int row_num = rand()%img.rows ; 
			int col_num = rand()%img.cols ; 
			if (img.channels() == 1) {
				img.at<uchar>(row_num , col_num) = 255;
				//cv::Mat_ img_2 = img ; //shallow copy 
				//img(row_num , col_num) = 255;
			}
			else {
				if(img.channels() == 3){
					img.at<cv::Vec3b>(row_num , col_num)[0] = 255;
					img.at<cv::Vec3b>(row_num , col_num)[1] = 255;
					img.at<cv::Vec3b>(row_num , col_num)[2] = 255;
				}
			}
		}		
	}
```

-	cv::Mat::at<typename>(int i , int j) can over load 
> 使用CV::Mat_<typename >类可以简化某些操作，例如在Mat_中重载了运算符 () ：cv::Mat_::operator()(int i , int j);与cv::Mat::at()有相同意思。

-	在opencv中，彩色的三通道图片的像素中三个通道的顺序是：BGR，blue蓝色在第一个字节。
-	***因为到效率问题，图片在内存中存储时其行的像素数可能与图像的实际行的像素数不同，一般在内存中数据对其会增加数据的传输速度。所以我们不能认为图像的存储是连续的。***
> 在Mat类中，rows属性给出图像的真实行数，cols给出真实列数，那么在cols中是不包含系统为了效率额外添加的像素。step变量给出每行的字节数，elemSize给出每个像素的字节数。total()给出图片的像素总数。







page 26
### 第三章：











### some functions structure etc for opencv 
#### functions 
- Mat imread( const string &filename, int flags=1 );
	> return a structure(cv::Mat) to handle images .
	flags Specifies color type of the loaded image:
	>0 the loaded image is forced to be a 3-channel color image
	=0 the loaded image is forced to be grayscale
	<0 the loaded image will be loaded as-is (note that in the current
	implementation the alpha channel, if any, is stripped from the output
	image, e.g. 4-channel RGBA image will be loaded as RGB if f lags ≥ 0).

- bool Mat::empty() const;  
	> check to see if an image was in fact read.

- void cv::namedWindow( const string& winname, int flags ); 
	> winname is the name of new window and Future HighGUI calls that interact
	with this window will refer to it by this name.
	> flag can be 0(the default value) and cv::WINDOW_AUTOSIZE.
	if 0:all images will display in the same size .
	if auto differdnt pictures will show in different size .

- void imshow( const string& winname, const Mat& image );
	> winname Name of the window.
	image Image to be shown.

- int waitKey(int delay=0); 
	> this fun is used to wait a keypress event.if delay if >=0 this functions 
	will wait for infinit .if delay is >0 ,this functions will return if some 
	key is pressed or wait time ivvs more than delay.
	Returns the code of the pressed key or -1 if no key was pressed before the 
	specified time had elapsed.
	*	Note: This function is the only method in HighGUI that can fetch and handle events, so it
	needs to be called periodically for normal event processing, unless HighGUI is used within some
	environment that takes care of event processing.

- void DestroyWindow( const char* name );
	> name is the window's name .




	## structures && classes

	### class :
- cv::Mat:         opencv use this structure to handle all kinds of images .
- cv::VideoCapture Class for video capturing from video files or cameras. 

	### structure :





