MATLAB
------

MATLAB 也允许另一种写法，叫左除。如果我们要计算 b/a ，我们可以使用反斜杠代替斜杠，表示反过来除，表达式如下a\b

在很多时候，我们并不需要MATLAB 输出结果，这时只需要在表达式后面加上分号（;）即可。

较长的表达式可以在行尾加上三点（...）省略号进行续行输入

要得到x 的自然对数，输入log(x) 

**MATLAB中数组的下标从 _1_ 开始**
## 注意
-	不要定义和内建函数同名的变量，否则这些内建函数将无法使用。   
-  	使用函数whitch来查看是否你所定义打函数或文件名与系统定义打函数或文件重名。  
  
### 常用指令和内建函数 

#### 特殊值：    
-  	pi 		3.141592...        
-  	i  j    sqrt(-1)        
-  	inf     infinity        
-  	nan  	not a number        
-  	clock   current time.ans = 2015.0000      8.0000     10.0000     17.0000     57.0000     52.1319        
-  	date	current data.ans = 10-Aug-2015        
-  	eps 	epsilon.the smallest number between two numbers that the computer can reprent.this computer is : ans =    2.2204e-16   
-  	ans 	        

#### 数据的显式格式：    
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

#### 指令
-	clc：				清除当前command窗口中的数据。
-	clf：				清除当前绘图窗口。
-	clear：				清除当前workspace保存的变量（clear x y z）。
-	abort：				终止当前运行打指令或程序。
-	！：				似于vim，在指令打前面加上！，会执行系统打指令。
-	formate long [short,rat]
-	which：				查看系统中是否已经存在这个名称。例如：which sin，系统会返回sin所处打位置，这样就不能再使用这个名称。
-	who: 显示所有变量的名称
-	whos:显示所有变量与其详细信息。
-	addpath				将某个路径添加都系统打搜索目录。
-	path：				显示所有的搜索路径。
-	path2rc：			将当前路径添加到系统搜索目录。
-	rmpath：			从系统中删除某个搜索路径。

#### 运算符
-	'	在MATLAB 中，我们用单引号（'）代表转置操作
-	x = [xi : q: xe] 或x = xi : q: xe   创建一个首元素为xi，末元素为xe 差值向量，差值q为一个实数。x = [0:2:10] ：0     2     4     6     8    10 

#### 内建函数
-   ceil(x)				右向取整
-   floor()				左向取整
-   fix(x)              朝零取整
-   round()				取离其最近的整数。
-	char(x)				Converts a matrix of numbers into a character string.
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
-   fprintf             类似于C 中的printf，只不过在matlab中字符串使用单引号包含。fprintf的一个缺陷就是无法显示复数的虚部，故此时使用
-   较好。
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
#### matlab中初始化数据的三种方式：        
*	直接通过赋值的方式。variable = expression
*	通过规定的格式进行赋值,也可以通过内建打函数进行赋值，也可以在程序运行的时候通过键盘赋值。例如：f = [0:2:10]'，my_val = input('input data')
*	从文件中读取数据。load -mat x.dat（-mat表示以matlab内建格式读取文件，matalb可以依据文件的后缀名来判断文件的格式。）

matlab内存中数据组织形式：        
1. 对于一个矩阵，matlab会依次的在内存中保存第一列，第二列，第三列...一维向量的每一个数据都可以看成一列。
2. matlab允许我们将一个矩阵以一维的形式进行读写，例如：        
> a = [ 1 2 3; 4 5 6;7 8 9] 	那么a(4)的值就是2,a(8)的值就是6。但是这种特性要少用。

3. 从已存在矩阵中获得子矩阵，列出需要选取的元素就可以获得子矩阵：array=[6,5,4,3,2,1] ,array(1)就是6,array([1 3])就是[6 4],注意在这里[1 3]所表示的意义，这就是有两个元素的向量，array(1:2:5)的值是[1 4 2] a(:,3)的值是列向量[3 6 9]结合matlab的数据在内存中的分布，a([1 , 8])的值是[1  6]
4. end 函数，end在向量和矩阵中表示下标的最大值，例如a(end)的值是9,array(3:end)的值是[4 3 2 1]
5. array(1:2,[1 4])可以作为左值也可以作为右值，当其来为左值时，array必须事先以被定义。这样才能作为左值被赋值。array(1:2,[1 4])表示array的1到2行的1和4列的数据。当向量作为左值时，其右侧的赋值向量必须和其维度相同。但当其右侧是标量时则左值矩阵可以是任意维度。选定的值都会与右侧标量相同。


保存和读取文件数据：        
-	save filename var1 var2 var3 ...   save var to filename.默认情况下保存的文件不是文本格式，为了保存为文本格式可在save后添加指令        
`-acsii ：save -acsii filename var... `  文件后缀可选.dat
-	load filename。从已知的文件中读取数据，一般情况下matlab会以文件的后缀来载入文件，但可以强制要求matlab以某种格式载入数据：         
`load -mat xx.txt  或load -acsii xx.mat `

***矩阵的左除***
> 对于由矩阵表示的线性方程组，如Ax = B，一般而言x = A^-1 *B 。而左除的意义就是inv(A)*B，x = A \ B ;

**向量操作和矩阵操作**
> 一般而言如果操作符前有点如：.*  ./等表示向量操作，一般就是对应元素之间的操作。当运算符前没有点且操作对像是矩阵时，此时就要使用矩阵的运算法则。o

Matlab的内建函数：
> matlab的内建函数一般返回多个参数，例如max 一般会返回一个列表中最大的值和这个值的下标。matlab的内建函数会根据右值的类型来决定返回几个值：x = max(A)，返回一个值，[maxval  index] = max(A) 会返回两个值。	       
> ***matlab可以依据返回值来重载函数***

从matlab中导出图片：> page59     

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

### 第三章 分枝语句和程序设计
***Top Down Design***
1. 明确声明需要解决的问题。
2. 定义输入和输出。
3. 定义算法。
4. 编码。
5. 测试。

Page 93

a = true  创建一个logical value

~=  

&&提供短路运算，而&不提供


ischar(a) Returns true if a is a character array and false otherwise.
isempty(a) Returns true if a is an empty array and false otherwise.
isinf(a) Returns true if the value of a is infinite (Inf) and false otherwise.
isnan(a) Returns true if the value of a is NaN (not a number) and false otherwise.
isnumeric(a) Returns true if a is a numeric array and false otherwise.
logical Converts numerical values to logical values: if a value is non-zero, it is converted t


```
switch (switch_expr)
case {case_expr_1, case_expr_2, case_expr_3},   %可以有多个表达式，满足其中一个机会执行
Statement 1 
Statement 2 ...  Block 1

otherwise,    %类似C中的default
Statement 1 Statement 2 ...  Block n
end
```

```
try
Statement 1 Statement 2 ... ⎭ ⎬ ⎫ Try Block
catch
Statement 1 Statement 2 ... ⎭ ⎬ ⎫ Catch Block
end
```

MALTAB 编译器无论什么时
候遇到这个命令，它都能转化为相应的函数。它把命令直接当作函数来用，而不是应用命令
语法。下面的两个语句是等价的：
axis on;
axis ('on');

while expr
...
...
...
end


for ii = 1:10
Statement 1
...
Statement n
end

for ii = 1:2:10
Statement 1
...
Statement n
end

for ii = [5 9 7]
Statement 1
...
Statementn
end

for ii = [1 2 3; 4 5 6]
Statement 1
...
Statement n
end

循环指数 ii 在第一次执行时为行向量[1 4] ，第二次执行时为 [4 5]，第三次执行时为 [6 7]

break 和 continue 语句

function [outarg1, outarg2, ...] = fname(inarg1, inarg2, ...)
%H1 comment line               //我们可以使用lookfor指令找到第一行注释
%Other comment lines            //使用help指令可以找到余下的指令
...
(Executable code)
...
(return)


maltab 程序与它们函数之间的交互用是按值传递机制。


MATLAB符号运算与绘图
-------------
### 创建符号数与符号变量
*	MATLAB中的符号变量默认为复数，可以指定变量的类型，见下
*	使用函数`sym()`创建符号数，例如`sym(1/3)`将使用分数的形式精确表示1/3，然而不使用sym函数的1/3将以浮点的形式保存在内存中。在进行符号计算时最好使用`sym`对常数进行转化，这样最终的结果更加精确。由`sym()`创建的符号值是常量；
*	使用关键字`syms`创建符号变量：`syms x y z`。当然了，也可以使用`sym()`函数创建符号变量

	> 使用sym()函数一次创建多个符号变量：`A = sym('a',[1 20])`，这将产生a1,a2,a3....a20共20个符号变量。创建黄金分割比例的方式：`(1+sqrt(sym(5)))/2`
*	使用syms创建函数：

	> `syms f(x,y)`，这样将一次创建三个符号变量：f、x、y；  
	> 也可以分别创建变量和函数：  
	> syms x y  %创建两个符号变量  
	> f(x,y) = x^3 * y^2  %创建函数变量 f  
	> syms g  %使用这种方式创建的变量g不能使用这种形式：g(x,y)  
*	在MATLAB中默认符号变量为复数，但可以指定符号变量的类型(integers, positive, rational,real.)：

	> %使用assumptions来获取符号的类型，使用assumptions关键字可以获得所有符号变量的类型  
	> syms x  
	> assumptions(x)   % assumptions不加变量将显示所有变量的属性     
	> assume(x >= 0) %assume将覆盖变量的熟悉，如果想添加属性需要使用assumeAlso  
	> assume(x ,'clear') %清空属性，使用默认属性   
	> assumeAlso(x,'integer') %不覆盖原属性  
	> a = sym('a', 'real');   %使用sym指定real属性  
	> syms a b real  %使用syms时指定实数属性  
### 常见符号运算
#### 求导

	syms x y
	f = sin(x)^2 + cos(y)^2;
	diff(f)  %如果没有指定求导的变量，则MATLAB将使用其内置的默认顺序求解（可以使用函数symvar获得顺序）
	f = sin(x)^2 + cos(y)^2;
	diff(f, y, 2) %对y求两次偏导
#### 求积分
不定积分：

	syms x y n
	f = x^n + y^n;
	int(f)  %使用默认的顺序求积分 先 x
定积分：

	%If the int function cannot compute an integral, it returns an unresolved integral
	syms x y n
	f = x^n + y^n;
	int(f, 1, 10)
#### 解方程

	%Use the double equal sign (==) to define an equation
	%If you do not specify the right side of the equation, solve assumes that it is zero
	syms x
	solve(x^3 - 6*x^2 == 6 - 11*x)
	solve(x^3 - 6*x^2 + 11*x - 6)

	syms x y
	solve(6*x^2 - 6*x^2*y + x*y^2 - x*y + y^3 - y^2 == 0, y)%依旧可以使用默认顺序，不指定变量
	
	syms x y z
	[x, y, z] = solve(z == 4*x, x == y, z == x^2 + y^2)
#### 化简与替换
化简，化简有不同的函数用于不同目的的化简

	phi = (1 + sqrt(sym(5)))/2;  
	f = phi^2 - phi - 1  
	simplify(f)  %化简，但因为何为最简并没有明确的定义，故最终结果并不一定是你想要的
	
	expand(f) %以多项式的形式展开
	factor(g) %以多项式根的形式展开
	horner(h) %nested (Horner)   x*(x*(x*(x*(x + 1) + 1) + 1) + 1)

替换，替换可以用于很多方面，下面只是一个例子

	syms x y
	f = x^2*y + 5*x*sqrt(y);
	subs(f, x, 3)  %9*y + 15*y^(1/2)

#### 符号绘图函数
绘图函数(2016之后将使用新的绘图名)：  

*	`ezplot` to create 2-D plots of symbolic expressions, equations, or functions in Cartesian coordinates.使用fimplicit为隐函数绘图
	
		syms x   
		f = x^3 - 6*x^2 + 11*x - 6;  
		fplot(f)  
		xlabel('x')
		ylabel('y')
		title(texlabel(f))
		grid on

		%隐函数绘图
		syms x y
		eqn = (x^2 + y^2)^4 == (x^2 - y^2)^2;
		fimplicit(eqn, [-1 1]) 

*	`ezplot3` to create 3-D parametric plots.

		syms t
		fplot3(t^2*sin(10*t), t^2*cos(10*t), t)

*	`ezpolar` to create plots in polar coordinates.
*	`ezsurf` to create surface plots.

		syms x y
		fsurf(x^2 + y^2)

*	`ezcontour` to create contour plots.
*	`ezmesh` to create mesh plots.