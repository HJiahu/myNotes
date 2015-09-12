本文摘自：MATLAB® Programming for Engineers 4th
## 注意
-	不要定义和内建函数同名的变量，否则这些内建函数将无法使用。
-  	使用函数whitch来查看是否你所定义打函数或文件名与系统定义打函数或文件重名。		
  
### 常用指令和内建函数 
常用指令和内建函数：          2015-08-06 17:48:32     
#### 指令
-	clc：				清除当前command窗口中的数据。
-	clf：				清除当前绘图窗口。
-	clear：				清除当前workspace保存打变量。
-	abort：				终止当前运行打指令或程序。
-	！：				似于vim，在指令打前面加上！，会执行系统打指令。
-	which：				查看系统中是否已经存在这个名称。例如：which sin，系统会返回sin所处打位置，这样就不能再使用这个名称。
-	addpath				将某个路径添加都系统打搜索目录。
-	path：				显示所有的搜索路径。
-	path2rc：			将当前路径添加到系统搜索目录。
-	rmpath：			从系统中删除某个搜索路径。
#### 内建函数
- 	常用：
	-   ceil(x)				右向取整
	-   floor()				左向取整
	-   fix(x)              朝零取整
	-   round()				取离其最近的整数。
	-	char(x)				 Converts a matrix of numbers into a character string.
	-	double(x) 			Converts a character string into a matrix of numbers.
	-	int2str(x) 			Converts x into an integer character string.
	-	num2str(x) 			Converts x into a character string.
	-	str2num(s) 			Converts character string s into a numeric array.

-	allchild：			查看对象中存在的子对象，其参数是对象的句柄值。
-	allchild(gcf)：		获得当前图像窗口的子对象，其中gcf指当前的绘图窗口中的图像。
-	get：				函数获得对象的属性，其参数是对象的句柄值。虽然说句柄是一个数值，但在get函数中不能直接的使用这个值，一般要将其转化为句柄类型。例如get(ans(1))。
-	set：               函数，设置对象的属性。set函数的参数由左到右分别是上一级的子对象，最后一个参数是赋予对象的值。
-	findobj：           函数用于查找符合要求的对象
-	num2str()           将数值转化为字符串。str = ['the number is 'num2str(pi)]    the number is 3.1415
-	int2str()
-  fprintf             类似于C 中的printf，只不过在matlab中字符串使用单引号包含。fprintf的一个缺陷就是无法显示复数的虚部，故此时使用disp较好。
-	max 
-	abs()
-	acos()
-	angle()             the phase of complex value x ,in radians
-	exp()
-	log()				ln()
-	[value,index] = max(x) Returns the maximum value in vector x, and optionally the location of that value.
-	[value,index] = min(x) Returns the minimum va
-	mod(x,y)			 Remainder or modulo function.

	


### chapter 2：        

matlab 使用小括号来表示坐标，在引用矩阵中的数据时语法类似于：A(2,3)    
matlab中初始化数据的三种方式：        
1. 直接通过赋值的方式。variable = expression
2. 通过规定的格式进行赋值,也可以通过内建打函数进行赋值，也可以在程序运行的时候通过键盘赋值。例如：f = [0:2:10]'，my_val = input('input data')
3. 从文件中读取数据。load -mat x.dat（-mat表示以matlab内建格式读取文件，matalb可以依据文件的后缀名来判断文件的格式。）

matlab内存中数据组织形式：        
1. 对于一个矩阵，matlab会依次的在内存中保存第一列，第二列，第三列...一维向量的每一个数据都可以看成一列。
2. matlab允许我们将一个矩阵以一维的形式进行读写，例如：        
> a = [ 1 2 3; 4 5 6;7 8 9] 	那么a(4)的值就是2,a(8)的值就是6。但是这种特性要少用。

3. 从已存在矩阵中获得子矩阵，列出需要选取的元素就可以获得子矩阵：array=[6,5,4,3,2,1] ,array(1)就是6,array([1 3])就是[6 4],注意在这里[1 3]所表示的意义，这就是有两个元素的向量，array(1:2:5)的值是[1 4 2] a(:,3)的值是列向量[3 6 9]结合matlab的数据在内存中的分布，a([1 , 8])的值是[1  6]
4. end 函数，end在向量和矩阵中表示下标的最大值，例如a(end)的值是9,array(3:end)的值是[4 3 2 1]
5. array(1:2,[1 4])可以作为左值也可以作为右值，当其来为左值时，array必须事先以被定义。这样才能作为左值被赋值。array(1:2,[1 4])表示array的1到2行的1和4列的数据。当向量作为左值时，其右侧的赋值向量必须和其维度相同。但当其右侧是标量时则左值矩阵可以是任意维度。选定的值都会与右侧标量相同。

特殊值：    
-  	pi 		3.141592...        
-  	i  j    sqrt(-1)        
-  	inf     infinity        
-  	nan  	not a number        
-  	clock   current time.ans = 2015.0000      8.0000     10.0000     17.0000     57.0000     52.1319        
-  	date	current data.ans = 10-Aug-2015        
-  	eps 	epsilon.the smallest number between two numbers that the computer can reprent.this computer is : ans =    2.2204e-16   
-  	ans 	        

数据的显式格式：    
默认情况下matlab只会显示小数点后4位，但可以使用format long/short/bank/rat/+ 指令改变格式，+表示只显示符号。        
-  	format long 14 digits after decimal 12.34567890123457        
-  	format short e 5 digits plus exponent 1.2346e+001        
-  	format short g 5 total digits with or without exponent 12.346        
-  	format long e 15 digits plus exponent 1.234567890123457e+001        
-  	format long g 15 total digits with or without exponent 12.3456789012346        
-  	format bank “dollars and cents” format 12.35        
-  	format hex hexadecimal display of bits 4028b0fcd32f707a        
-  	format rat approximate ratio of small integers 1000/81        
-  	format compact suppress extra line feeds format loose restore extra line feeds format + Only signs are printed.         

保存和读取文件数据：        
-	save filename var1 var2 var3 ...   save var to filename.默认情况下保存的文件不是文本格式，为了保存为文本格式可在save后添加指令  -acsii ：save -acsii filename var...文件后缀可选.dat
-	load filename。从已知的文件中读取数据，一般情况下matlab会以文件的后缀来载入文件，但可以强制要求matlab以某种格式载入数据：        load -mat xx.txt  或load -acsii xx.mat 

***矩阵的左除***
> 对于由矩阵表示的线性方程组，如Ax = B，一般而言x = A^-1 *B 。而左除的意义就是inv(A)*B，x = A \ B ;

**向量操作和矩阵操作**
> 一般而言如果操作符前有点如：.*  ./等表示向量操作，一般就是对应元素之间的操作。当运算符前没有点且操作对像是矩阵时，此时就要使用矩阵的运算法则。o

Matlab的内建函数：
> matlab的内建函数一般返回多个参数，例如max 一般会返回一个列表中最大的值和这个值的下标。matlab的内建函数会根据右值的类型来决定返回几个值：x = max(A)，返回一个值，[maxval  index] = max(A) 会返回两个值。	

从matlab中导出图片：
> page59     
> -deps Creates a monochrome encapsulated postcript image.    
> -depsc Creates a color encapsulated postcript image.    
> -djpeg Creates a JPEG image.    
> -dpng Creates a Portable Network Graphic color image.   
> -dtiff Creates a compressed TIFF image.   

matlab 图像设置：(marker 用于标记关健点，一般就是绘图的取值点）：       
一般matlab可以设置曲线的三个特性：颜色，marker style和line style。
```
Color 		Marker Style 		Line Style
y yellow 	. point				- solid
m magenta 	o circle 			: dotted
c cyan 		x x-mark 			-. dash-dot
r red 		+ plus 				-- dashed
g green 	* star 				<none> no line
b blue		s square
w white 	d diamond
k black 	v triangle (down)
			^ triangle (up)
			< triangle (left) 
			> triangle (right)
			p pentagram
			h hexagram
			<none> no marker 
```
图像説明（legend）可以放在不同的位置。page63

坐标的尺度：
1. The plot function plots both x and y data on linear axes.
2. The semilogx function plots x data on logarithmic axes and y data on linear axes.
3. The semilogy function plots x data on linear axes and y data on loga- rithmic axes.
4. The loglog function plots both x and y data on logarithmic axes.

### 分枝语句和程序设计


