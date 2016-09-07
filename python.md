本文摘自：[廖雪峰的python博客](http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000)
### 准备
-	在python中使用pip安装第三方模块。
-	Python3默认使用unicode编码（无论代码还是内存中的对象，默认都是unicode）
	-	声明文件的编码方式：`# -*- coding:utf-8 -*-`
-	注意因为python是用缩进来表示不同的代码块，故不要随便的使用缩进。
-	python使用`#`作为注释的开始。
-	python hello.py   使用python解释权执行python程序。
	-	在linux和Mac下可以为.py文件添加可执行权限：
	-	在文档的第一行添加文件的执行程序：`#!/usr/bin/env python3`
	-	为代码添加权限：`chomd a+x *.py`

### 部分关键字[参考][1]
*	`is`：is is used in Python for testing object identity. While the == operator is used to test if two variables are equal or not, is is used to test if the two variables refer to the same object.
*	`None`：None is a special constant in Python that represents the absence of a value or a null value. 
*	`as`：as is used to create an alias while importing a module，`import math as myAlias`

### 基本概念
-	python中的变量作用范围与C类似，global关键字用于声明当前域引入了某个全局变量（例如：`global x`）
-	**在python中所使用的一切均是对象，例如：`a=3`其中a是int类型的对象。**
-	**注意python中变量之间的传递均是以引用方式进行的，对于不可变量（元组、数值、字符串）当他们发生变化时系统会在内存中创建新的元素。为了实现副本，可以使用复制例如list b与a：`b = a[:]`**
-	python 可以使用单引号和双引号表示字符串，`printf('hello')`。如果字符串里面有很多字符都需要转义，则可以在字符串的前面加上`r`，表示在引号中的字符串不再转义。`print(r'\\\t\\')`输出为`\\\t\\`
-	在python中变量是没有类型的，有类型的是变量所引用的对象。可以认为python中的所有变量都是类似于C中的void指针，变量赋值改变的是变量指向的对象。python学习手册第六章。
-	在python中 == 比较的是变量指向的对象，谓词 is 比较的是变量（即指针）。
-	三个单引号包含的字符串的排版是所见即所得的。（也可以使用r来表示不转义）
-	python3中的list与tuple类似php中的数组，只是list是可变的，而tuple（元组）是不可变的，但是若tuple中的元素是list则list中的内容可变。list支持pop与append方法。
-	类似`__xxx__`的属性和方法在Python中都是有特殊用途的，比如`__len__`方法返回长度。在Python中，如果你调用len()函数试图获取一个对象的长度，实际上，在len()函数内部，它自动去调用该对象的`__len__()`方法。

### python3 的编码问题（python3中字符串使用的编码是unicode）
-	***python3在计算机内存中，统一使用Unicode编码(存储方式可能是utf-16)，当需要保存到硬盘或者需要传输的时候，就转换为UTF-8编码。***
-	python提供`ord('A')`（返回65）函数来获得字符对应的unicode 编码。`chr(25991)`（返回汉字“文”）可以把编码转化为对应的符号。
-	因为python3在内存中保存字符串的形式是utf-16，故为了在网络上传播这些内容，需要先将数据转化为bytes类型：
```
'abc'.encode('ascii')#将字符串用ascii保存，即bytes型。所有的串，即使是英文，其在内存中的默认存储格式都是utf-16
'abc'.encode('UTF-8')#将字符串用UTF-8格式保存。
'你好'.encode('ASCII')#是错误的方式，因为中文是无法使用ascii编码保存的。
'你好'.encode('UTF-8')#是正确的语法
```
-	从网络上接收到的数据都是以bytes格式保存，为了便于处理，需要将这些数据转化为unicode编码并在内存中保存（utf-16）。
```
>>> b'ABC'.decode('ascii')#内存中字符的保存方式就是bytes
'ABC'
>>> b'\xe4\xb8\xad\xe6\x96\x87'.decode('utf-8')#指明bytes集合的编码方式为utf-8
'中文'
```

### 常见方法&函数
-	在启动脚本的时候可以传递参数给脚本，不过需要在文件中导入sys模块。sys.argv是传递给文件的参数列表
-	函数id将返回对象唯一识别码（在CPython中这个是对象地址）
-	可以使用type函数来确定对象的类型：`type(123)`将返回：`<class 'int'>`
	-	`type(123) == type(345)`
	-	`type(123) == int`
	-	`type(abs) == types.BuiltinFunctionType`#使用import types
-	判断一个变量是否是某个类型（可用于继承关系）可以用isinstance()：`>>> isinstance(a, list) `
	-	也可以使用isinstance来判断一个变量是否是某些类型中的一种：`>>> isinstance([1, 2, 3], (list, tuple))`
-	函数dir将以字符串的形式返回对象的所有属性和方法：`dir('abc')`。
-	配合getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态：` hasattr(obj, 'x') # 有属性'x'吗？`，`setattr(obj, 'y', 19) # 设置一个属性'y'`
-	输入：`val = input('please enter sth:')`
-	输出：`print('The quick brown fox', 'jumps over', 'the lazy dog')`
-	python 中的逻辑运算：not   and  or
-	指数运算`**`，8**2 = 64
-	python3 中的两种除法：
	-	` / `普通的算术除法：10/3 得 3.33333333333...
	-	` // `地板除：10/3 得  3 ，这个类似于C中的整数相除。
-	int(str , base = 10)#base表示str中的进制，默认情况下base=10，即默认情况下将str中的数据当做10进制数。
-	map():map()函数接收两个参数，一个是函数，一个是**Iterable**，map将传入的函数依次作用到序列的每个元素，并把结果作为新的**Iterator**返回。（注意返回的是iterator而不是iterable，故map并不改变源数据）
	-	`r = map(fun, [1,2,3,4,5,6])`
-	filter():与map类似，接受两个参数。但filter第一个函数的返回值必须是bool类型，filter依据true，false来决定是否保留当前元素。与map同样，filter并不更改源数据，其返回的是一个iterator，不是序列。
-	reduce():reduce把一个函数作用在一个序列[x1, x2, x3, ...]上，这个函数必须接收两个参数，reduce把结果继续和序列的下一个元素做累积计算：`reduce(f, [x1, x2, x3, x4]) 类似于 f(f(f(x1, x2), x3), x4)`
-	len()函数计算的是str的字符数，如果换成bytes，len()函数就计算字节数。
-	字符串格式化：`'Hi, %s, you have $%d.' % ('Michael', 1000000)`显示结果： `'Hi, Michael, you have $1000000.'`

### 列表生成：
*	列表生成
```
>>>l = [x*x for x in range(1,1)]//使用方括号的原因在于生成物需要使用列表保存。
>>> l
[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]
>>> [x*x for x in range(1,11) if x%2 == 0]
[4, 16, 36, 64, 100]
>>> [m+n for m in "he" for n in "she"]
['hs', 'hh', 'he', 'es', 'eh', 'ee']
>>> [d for d in os.listdir("C:/Users")]
['All Users', 'Default', 'Default User', 'desktop.ini', 'HJiahu', 'Public']
>>> d = {'x': 'A', 'y': 'B', 'z': 'C' }
>>> for k, v in d.items():
...     print(k, '=', v)
...
y = B
x = A
z = C
>>> L = ['Hello', 'World', 'IBM', 'Apple']
>>> [s.lower() for s in L]
['hello', 'world', 'ibm', 'apple']
```
*	截取数组
```
>>> for i, value in enumerate(['A', 'B', 'C']):#Python内置的enumerate函数可以把一个list变成索引-元素对
...     print(i, value)
...
0 A
1 B
2 C
>>> for x, y in [(1, 1), (2, 4), (3, 9)]:
...     print(x, y)
...
1 1
2 4
3 9
>>>classmates = ['Michael', 'Bob', 'Tracy']#list与C语言中的数据的区别之一在于list[-1]可以索引最后一个元素，-2、-3...
>>>classmates = ('Michael', 'Bob', 'Tracy')#tuple
#切片（截取数组的一段），冒号前后与C++的begin，end是类似的，[start:end:gap]，从start到end每gap个数取一个
>>>classmates[1:2]#返回[Bob]，前闭后开
>>>classmates[:3]
>>>classmates[-2:]#切片中，冒号前的下标起始点，后面是结束位索引(类似于C++中的尾后迭代器)，从左向右。即使起始点是负数，那么也是向右切片。本例是切到最后
[Bob Tracy]
>>>L = list(range(0,100))#创建从0到99的一个数组，不包含100
>>>L[:10:2]#前10个数，每两个数取一个
[0,2,4,6,8]
```

### 生成器
-	***函数是顺序执行，遇到return语句或者最后一行函数语句就返回。而变成generator的函数，在每次调用next()的时候执行，遇到yield语句返回，再次执行时从上次返回的yield语句处继续执行。***
	```
	#列表生成的一个缺点就是当数据太多时时很占内存的，软而我们在使用列表时并不是使用所有的值，故将列表完全的保存在内存中并不好。
	#生成器和列表的一个区别在于生成器使用的是圆括号而不是方括号。
	>>> g = (x*x for x in range(1,10000))
	>>> g
	<generator object <genexpr> at 0x000000000361AF10>
	#生成器并不把所有的元素都放在内存中，只是使用的时候在将数据计算出来，使用next(g)可以依次使用g中的元素。当然也可以用for
	>>>next(g)#每次算一个值，当遍历玩之后会抛出异常
	1
	#函数经过处理也可以成为生成器，将函数中生成的数据用yield修饰即可
	#斐波那契数列
	def fib(max):
		n, a, b = 0, 0, 1
		while n < max:
			yield b   
			a, b = b, a + b
			n = n + 1
		return 'done'
	#函数是顺序执行，遇到return语句或者最后一行函数语句就返回。而变成generator的函数，在每次调用next()的时候执行，遇到yield语句返回，再次执行时从上次返回的yield语句处继续执行。举个简单的例子，定义一个generator，依次返回数字1，3，5：
	def odd():
		print('step 1')
		yield 1
		print('step 2')
		yield(3)
		print('step 3')
		yield(5)
	```

-	python中的迭代器（与C++中的概念不太一样）：可以被next()函数调用并不断返回下一个值的对象称为迭代器：Iterator。
```
>>> from collections import Iterator
>>> isinstance((x for x in range(10)), Iterator)#注意与方括号的区别
True
>>> isinstance([], Iterator)
False
#使用iter()函数可以把list、dict、str等Iterable变成Iterator
>>> isinstance(iter([]), Iterator)
True
>>> isinstance(iter('abc'), Iterator)
True
```
-	python中其他数据结构有set（s1 = set([1,2,3,4])），和字典。与C++中的set和map相对应，python中的set中的元素是不可重复的，而且这两种数据结构是自序的，即其打印次序可能与输入次序不同（在key-value对中，key值是不可变的）。
```
>>> from collections import Iterable
>>> isinstance('abc', Iterable) # str是否可迭代
True
>>> isinstance(123, Iterable) # 整数是否可迭代
False
#默认情况下，for迭代的是dict的key
>>>d = {'a':1,'b':2,'c':3}#a、b、c如果不加引号，则会出未定义的错误
>>> for key in d:
	print(key)	
c
a
b
>>> for value in d.values():
	print(value)	
3
1
2
>>> for key,value in d.items():
	print(key,':',value)	
c : 3
a : 1
b : 2
```

### 函数
-	装饰器
-	偏函数
-	在代码运行期间动态增加功能的方式，称之为“装饰器”（Decorator）
#### lambda函数
-	Lambda expressions (sometimes called lambda forms) are used to create anonymous functions.
-	匿名函数有个限制，就是只能有一个表达式，不用写return，返回值就是该表达式的结果。

```
lambda parameters:expression
等价于
def <lambda>(arguments):
    return expression
#可以把匿名函数赋值给一个变量，再利用变量来调用该函数
>>> f = lambda x: x * x
>>> f
<function <lambda> at 0x101c6ef28>
>>> f(5)
25
#也可以把匿名函数作为返回值返回，比如：
def build(x, y):
    return lambda: x * x + y * y
```
#### 部分内建函数

```
def my_abs(x):#注意冒号
    if x >= 0:
        return x
    else:
        return -x
def nop():
    pass//表示什么都不做

//python可以同时返回多个参数
 x, y = move(100, 100, 60, math.pi / 6)
```
-	python中的函数也作为对象而赋给其他变量，函数名也是变量。

```
import math
>>> f = abs
>>> f(-1)
1
>>> abs = math.sqrt
>>> abs(2)
1.4142135623730951
>>> abs = 10
>>> abs(10)#出错，因为此时abs是个数，不是函数。
```
-	python中的默认参数与C++中的形式是相同的。默认参数有一个***大坑***：对于C++而言无论调用函数多少次，默认变量均是不变的，然而在python中，默认参数是一个在内存中真实存在的量，如果我们改变了这个量，那么其他函数的默认变量也会被改变，故python中的默认变量必须是不可变的量（字面值变量一般是不可变的，还有就是None常量）：

```
def add_end(L=[]):
    L.append('END')
    return L
#第一次执行add_end();返回的是['end']
#第二次执行add_end();返回的就是['end','end']
#为了解决这个问题，可以将默认参数设置为：None，然后在函数体内做判断
```
-	python可变参数（参数的个数是可变的）：在参数前加星号可以定义可变参数`*value`，Python允许你在list或tuple前面加一个*号，把list或tuple的元素变成可变参数传进去。

```
>>> def calc(*numbers):
	sum = 0
	for n in numbers:
		sum = sum + n * n
	return sum
>>> calc(1,2,3)
14
>>> nums = [1, 2, 3]#使用*号可以将list和其他列表转化为可变参数
>>> calc(*nums)
14
```
-	关键字参数，如果把可变参数看做list和tuple，则关键字参数在函数内会被组装成字典：

```
def person(name, age, **kw):
    print('name:', name, 'age:', age, 'other:', kw)

>>>person('Adam', 45, gender='M', job='Engineer')
name: Adam age: 45 other: {'gender': 'M', 'job': 'Engineer'}
```
-	命名关键字参数:如果要限制关键字参数的名字，就可以用命名关键字参数:

```
#和关键字参数**kw不同，命名关键字参数需要一个特殊分隔符*，*后面的参数被视为命名关键字参数。命名关键字参数必须传入参数名。
#使用命名关键字参数时，要特别注意，*不是参数，而是特殊分隔符。
def person(name, age, *, city, job):
    print(name, age, city, job)

#命名关键字参数可以有缺省值，从而简化调用：
def person(name, age, *, city='Beijing', job):
    print(name, age, city, job)

>>> person('Jack', 24, job='Engineer')
Jack 24 Beijing Engineer
```
#### 将函数作为返回对象

```
def count():
    fs = []
    for i in range(1, 4):
        def f():
             return i*i
        fs.append(f)
    return fs

f1, f2, f3 = count()
#正真的输出是：9,9,9，原因就在于返回的函数引用了变量i，但它并非立刻执行。等到3个函数都返回时，它们所引用的变量i已经变成了3，因此最终结果为9。
```
### 模块
-	一个.py文件就称之为一个模块，在import时其后缀.py不用加上。
-	每一个python文件模块中都有一个变量`__name__`，如果这个模块单独运行则其值为`__main__`；如果其被import到其他模块中其值就会改变。
-	每一个包目录下面都会有一个`__init__.py`的文件，这个文件是必须存在的，否则，Python就把这个目录当成普通目录，而不是一个包。`__init__.py`可以是空文件，也可以有Python代码，因为`__init__.py`本身就是一个模块，而它的模块名就是mycompany
-	任何模块代码的第一个字符串都被视为模块的文档注释

```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

' a test module '# 任何模块的第一个字符串将被视为模块的文档注释

__author__ = 'Michael Liao'# 作者名

import sys
```
-	作用域问题：类似`__xxx__`的变量是特殊变量，如`__author__`表示模块的作者、`__doc__`表示注释。
> 比如`__len__`方法返回长度。在Python中，如果你调用len()函数试图获取一个对象的长度，实际上，在len()函数内部，它自动去调用该对象的`__len__()`方法。                
> 我们自己写的类，如果也想用len(myObj)的话，就自己写一个`__len__()`方法。            

-	python中没有方法可以限制对private函数或变量的调用，但我们不应该调用他们。以下划线开头的变量名或函数名`_xx或__xx`被认为是私有的。
-	配合getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态。

### python中的面向对象
-	类的定义：
-	注意类中变量self的作用，其要作为每一个成员函数的第一个参数，表示类对应的实例。
-	类似于js，python对象中的成员变量是在使用的时候直接使用，不用声明，系统会自动的生成这些变量。

-	python中的变量如果使用两个下划线开头：`__xx`则表示变量不能从对象外访问（**因为系统会重新命名这些名称，还有就是除非变量的后缀也是两个下划线**），类似于C++中的private变量。但若变量同时以双下划线结尾，则表示这些变量是特殊变量，可以在对象外访问，而且不能使用这些名字作为普通的变量。
-	双下划线开头的实例变量是不是一定不能从外部访问呢？其实也不是。不能直接访问`__name`是因为Python解释器对外把`__name`变量改成了`_Student__name`，所以，仍然可以通过`_Student__name`来访问`__name`变量。因为不同版本的python会把`__name`修饰不同的名称，故最好不要使用这些特性。
-	***类属性与对象属性***：属于self的属性是对象属性，而不属于self且在类中的变量被称为类属性。对象属性的优先级高于类属性，故当对象属性和类属性同名则若使用对象来访问同名变量，则访问的是对象属性。**类属性并不是静态的，每一个对象都有其自己的类属性，改变一个对象的类属性并不会对其他的对象产生影响。**
-	对于静态语言来说，如果需要传入Animal类型，则传入的对象必须是Animal类型或者它的子类，否则，将无法调用run()方法。对于Python这样的动态语言来说，则不一定需要传入Animal类型。我们只需要保证传入的对象有一个run()方法就可以了，这就是动态语言的“鸭子类型”，它并不要求严格的继承体系，一个对象只要“看起来像鸭子，走起路来像鸭子”，那它就可以被看做是鸭子。
-	**动态的向对象与类添加方法与属性：**
	-	可以向js一样直接向已经存在的对象添加属性：`s.name = 'tom'`，s创建时时没有属性name的，这条语句会为其创建name属性。
	-	也可以类似创建属性一样，向类和对象中动态的添加方法，向类中添加的方法可以用于所有对象，即使对象定义在添加方法之前（对类添加的方法似乎无法改变对象中已经存在的变量，这个问题有机会要查一下）：

```
>>> class Student(object):
	def __init__(self,name,age):
		self.name = name
		self.age = age
	def prints(self):
		print(self.name , self.age)

>>> def set_age(self,age):
	self.age = age
	#对实例绑定的新方法只适用于当前对象，而不会影响其他的实例，但当把方法绑定到类后这些方法就可以用于所有对象。
>>> tom.set_age = MethodType(set_age,tom)#MethodType同样可以给类绑定方法，这样这些方法就可以适用于类所有的实例。
```
-	向类中添加属性是非常方便的，但有方式可以限制对象中添加属性：在类中定义`__slots__=('name','age',...)`对于对象而言，只能添加在`__slots__`中定义过的属性。**`__slots__`是不能继承的。**
-	python中有与C#中属性类似的东西，即类似set与get的方法（`@property`）。
-	python支持多重继承。
-	python中其他面向对象特性：
	-	定制类，特殊的成员函数，用双下划线开始与结尾。用于特殊的函数调用，如`__len__()`之于`len(...)`；用于print的`__str(self)__`
	-	枚举类，python中实现常量的方法。
	-	元类，用于创建类（好神奇）

### python中的socket
-	网络通信就是两个进程之间的通信。
-	TCP通信客户端：

```
>>> import socket
>>> sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
>>> sock.connect(('115.159.118.165',9999))
>>> sock.send('hello')
>>> sock.send('hello'.encode())#内部字符保存为utf-16 
5
>>> sock.close()
```
-	TCP服务器端

```
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('127.0.0.1', 9999))
s.listen(5)
while True:
    # 接受一个新连接:
    sock, addr = s.accept()
    # 创建新线程来处理TCP连接:
    t = threading.Thread(target=tcplink, args=(sock, addr))
    t.start()

def tcplink(sock, addr):
    print('Accept new connection from %s:%s...' % addr)
    sock.send(b'Welcome!')
    while True:
        data = sock.recv(1024)
        time.sleep(1)
        if not data or data.decode('utf-8') == 'exit':
            break
        sock.send(('Hello, %s!' % data.decode('utf-8')).encode('utf-8'))
    sock.close()
    print('Connection from %s:%s closed.' % addr)
```

### python面向对象
*	python中对象的定义
```
#python使用class定义类，括号中的变量为类继承的父类
#python中所有对象均继承自object对象
class Student(object):
	#__init__ 类似于C++中的构造函数，方法的第一个参数必须是self
	#但在使用这些方法的时候不用指明self
    def __init__(self, name, score， age):
		#python类中的属性（成员变量）的添加与js类似
		#当向一个对象中没有的属性赋值时，系统会自动增加这个属性
        self.name = name       
		#在类内定义的以双下划线开头的属性在类外的访问名与类内不同
		#例如在类外访问__score可能是这样的：classname._Student_name
		#python以这种方式隐藏 私有成员。
		#在python类中，没有对象成员是不能从外访问的，只是访问方式改变了
        self.__score = score
		#以双下划线开头语结尾的变量是特殊变量，可以在类外直接访问
		self.__age__ = age 

		#以单下划线开头的变量一般意味着他是私有的但可以直接在类外访问
		self._height = 2
	def print_name(self):
		print(self.name)
#在对象外使用__score将产生与类内__score不同的成员变量
```
*	类属性和对象属性
	*	对象属性可以直接使用对像名添加：`obj.new_name = ...`，也可以使用在类的定义时使用self关键字添加：`self.new_name = ...`
	*	类属性，直接在类中定义（不是在方法中）
```
class Student(object):
	name = 'student'
```
### 异常处理与单元测试
*	一般的调试方法[(参考)][2]：
	*	断言：`assert`
	*	logging
	*	调试器：`python -m pdb ***.py`
	*	IDE自带的调试工具
*	python使用关键字`raise`抛出异常；因为异常都是类，所以要先定义异常对象（继承基本异常类）；如果raise后没有参数则表示将当前异常再次向上抛出。
*	异常处理
```
import logging
try:
    print('try...')
    r = 10 / int('a')
    print('result:', r)
except ValueError as e: #except类似于C++中的catch
    print('ValueError:', e)
except ZeroDivisionError as e:
    print('ZeroDivisionError:', e)
except BaseException as e: #BaseException是python中所有异常的父类。
	logging.exception(e)   #打印错误栈，并不中断程序的运行。可以通过配置记录这些数据。
	print('base error')
else:                      #当没有错误出现时，这条语句会被执行。
	print('no error')
finally:                #finally语句可以没有，但只要其存在，其一定会被执行（无论是否有异常出现）。
    print('finally...')
print('END')
```
*	单元测试[参考][3]










[1]:http://www.programiz.com/python-programming/keyword-list#none
[2]:http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431915578556ad30ab3933ae4e82a03ee2e9a4f70871000
[3]:http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/00143191629979802b566644aa84656b50cd484ec4a7838000
