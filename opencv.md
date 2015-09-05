
Notes for opencv .
OpenCV2 cooking book

### 第二章：
introduce opencv2.0
opencv使用的名字空间是cv，例如调用显示image的函数的语法可以是：cv:imshow()
```
	int main( int argc, char** argv ) 
	{
		cv::namedWindow( "Example3", cv::WINDOW_AUTOSIZE );
		cv::VideoCapture cap;
		cap.open( string(argv[1]) );
		cv::Mat frame;
		while( 1 ) {
		cap >> frame;
		if( !frame.data ) break; // Ran out of film
		cv::imshow( "Example3", frame );
		if( cv::waitKey(33) >= 0 ) break;
	}
```
-	cv::Mat img //  Mat is a class 。
> Mat 使用了引用计数和浅复制，为了实现深复制，使用方法img.copyTo()             
> img.size().height                
> img.size().width             
> ***img.data***  是指向图像存储空间的指针，使用这个参数可以测试图片是否被正确读取。         
> we can creat matrix data by Mat :         
> `cv::Mat ima(240,320,CV_8U,cv::Scalar(100));`                   

-	cv::namedWindow("Original Image"); // define the window
-	cv::imshow("Original Image", image); // show the image
-	cv::imread()
-	cv::imwritel(filename , Mat,...)
-	cv::flip(Mat src ,Mat dst,int flipcode)    //if flipcode == 0 vertical if flipcode == 1 horizontal 
-	cv::waitKey(int delay = 0) //default ,this fun will wait for ever if no key is pressed ,if delay is not 0... 

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





