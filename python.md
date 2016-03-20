本文摘自：[廖雪峰的python博客](http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000)

-	在python中使用pip安装第三方模块。
-	可以使用type函数来确定对象的类型：`type(123)`将返回：`<class 'int'>`
	-	`type(123) == type(345)`
	-	`type(123) == int`
	-	`type(abs) == types.BuiltinFunctionType`
-	函数dir将以字符串的形式返回对象的所有属性和方法：`dir('abc')`。
-	配合getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态：` hasattr(obj, 'x') # 有属性'x'吗？`
-	**注意python中变量之间赋值默认是以引用来传递可变对象（变量）的（list，set...）只有对于不可变量（内置数据类型int，double...）才会使用传值的形式。为了实现副本，可以使用复制例如list b与a：`b = a[:]`**

```
#python中优先引用传递，只有无法使用引用的时候才会转按值传递。
>>> a = 9
>>> b = a#此时id(a) == id(b)
>>> b = 3#此时id(a) != id(b)，但是当a是可变的时候，id(b) == id(a)，如下
>>> a = [1,2]
>>> b = a
>>> a[1] = 3#此时a == [1,3]，而 b == [1,3]，即id(a) == id(b)
>>> b = a[:]#使用复制可以获得a的副本，即id(a) != id(b)
>>> a = [1,2,3]
>>> b = [1,2,3]#此时id(a) != id(b)     ###########################
```
-	注意因为python是用缩进来表示不同的代码块，故不要随便的使用缩进。        
-	python使用`#`作为注释的开始。
-	python hello.py   使用python解释权执行python程序。
-	在linux和Mac下可以为.py文件添加可执行权限：
-	在文档的第一行添加文件的执行程序：`#!/usr/bin/env python3`
-	为代码添加权限：`chomd a+x *.py`
-	输入：`val = input('please enter sth:')`
-	输出：`print('The quick brown fox', 'jumps over', 'the lazy dog')`
	-	print()会依次打印每个字符串，遇到逗号“,”会输出一个空格。

-	python 可以使用单引号和双引号表示字符串，`printf('hello')`。如果字符串里面有很多字符都需要转义，则可以在字符串的前面加上`r`，表示在引号中的字符串不再转义。`print(r'\\\t\\')`输出为`\\\t\\`
-	三个单引号包含的字符串的排版是所见即所得的。（也可以使用r来表示不转义）            

 ```
 print('''line1
 line2
 line3''')
 打印的出来的形式就是：
 line1
 line2
 line3
```

-	python 中的逻辑运算：not   and  or  
-	python3 中的两种除法：
	-	` / `普通的算术除法：10/3 得 3.33333333333...
	-	` // `地板除：10/3 得  3 ，这个类似于C中的整数相除。
-	python3中的list与tuple类似php中的数组，只是list是可变的，而tuple（元组）是不可变的，但是若tuple中的元素是list则list中的内容可变。list支持pop与apped方法。

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
-	列表生成：

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
-	生成器
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
#函数经过处理也可以成为生成器，将函数中生成的数据用yield修饰即可(在写这种函数时，可以先用print替代yield使逻辑变得清晰，然后将print用yield替换，当感觉熟悉之后可以直接使用yield。)
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
-	len()函数计算的是str的字符数，如果换成bytes，len()函数就计算字节数。
-	字符串格式化：`'Hi, %s, you have $%d.' % ('Michael', 1000000)`显示结果： `'Hi, Michael, you have $1000000.'`
-	注意puthon判断语句之后要加冒号`：`

```
if a>0:
	...
else:
	...
elif:
	...
for a in coll:
	...
while n>0:
	...
...

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
-	int(str , base = 10)#base表示str中的进制，默认情况下base=10，即默认情况下将str中的数据当做10进制数。
-	map():map()函数接收两个参数，一个是函数，一个是**Iterable**，map将传入的函数依次作用到序列的每个元素，并把结果作为新的**Iterator**返回。（注意返回的是iterator而不是iterable，故map并不改变源数据）
-	filter():与map类似，接受两个参数。但filter第一个函数的返回值必须是bool类型，filter依据true，false来决定是否保留当前元素。与map同样，filter并不更改源数据，其返回的是一个iterator，不是序列。
-	reduce():reduce把一个函数作用在一个序列[x1, x2, x3, ...]上，这个函数必须接收两个参数，reduce把结果继续和序列的下一个元素做累积计算：`reduce(f, [x1, x2, x3, x4]) 类似于 f(f(f(x1, x2), x3), x4)`

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
-	一个.py文件就称之为一个模块
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
> 比如__len__方法返回长度。在Python中，如果你调用len()函数试图获取一个对象的长度，实际上，在len()函数内部，它自动去调用该对象的__len__()方法。                
> 我们自己写的类，如果也想用len(myObj)的话，就自己写一个__len__()方法。            

-	python中没有方法可以限制对private函数或变量的调用，但我们不应该调用他们。以下划线开头的变量名或函数名`_xx或__xx`被认为是私有的。
-	配合getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态。

### python中的面向对象
-	类的定义：
-	注意类中变量self的作用，其要作为每一个成员函数的第一个参数，表示类对应的实例。
-	类似于js，python对象中的成员变量是在使用的时候直接使用，不用声明，系统会自动的生成这些变量。

```
class Student(object): # 括号中包含的是当前类的父类，一般而言object是python中所有类的父类。
	#__init__函数是Python的构造函数，其中selt是每一个__init__函数都有的变量，表示创建的对象本身，self有系统自动生成，不用认为传入
 	def __init__(self, name, score): 
       		self.__name = name  #__name是无法在类外访问的。
        	self.score = score

	def print_score(self):  #注意self在此处的作用，在使用这个成员函数时，self也是不用认为传入的。
			print('%s: %s' % (self.name, self.score))
```
-	有些时候，你会看到以一个下划线开头的实例变量名，比如`_name`，这样的实例变量外部是可以访问的，但是，按照约定俗成的规定，当你看到这样的变量时，意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问”。
-	python中的变量如果使用两个下划线开头：`__xx`则表示变量不能从对象外方位，类似于C++中的private变量。但若变量同时以双下划线结尾，则表示这些变量是特殊变量，可以在对象外访问，而且不能使用这些名字作为普通的变量。
-	双下划线开头的实例变量是不是一定不能从外部访问呢？其实也不是。不能直接访问`__name`是因为Python解释器对外把`__name`变量改成了`_Student__name`，所以，仍然可以通过`_Student__name`来访问`__name`变量。因为不同版本的python会把`__name`修饰不同的名称，故最好不要使用这些特性。
-	***类属性与对象属性***：属于self的属性是对象属性，而不属于self且在类中的变量被称为类属性。对象属性的优先级高于类属性，故当对象属性和类属性同名则若使用对象来访问同名变量，则访问的是对象属性。**类属性并不是静态的，每一个对象都有其自己的类属性，改变一个对象的类属性并不会对其他的对象产生影响。**
-	继承

```
class Animal(object):        #父类
    def run(self):
        print('Animal is running...')
	
class Dog(Animal):           #子类

    def run(self):           #子类会直接覆盖父类中的同名方法
        print('Dog is running...')

class Cat(Animal):

    def run(self):
        print('Cat is running...')


```
-	判断一个变量是否是某个类型可以用isinstance()：`>>> isinstance(a, list) `
-	对于静态语言来说，如果需要传入Animal类型，则传入的对象必须是Animal类型或者它的子类，否则，将无法调用run()方法。对于Python这样的动态语言来说，则不一定需要传入Animal类型。我们只需要保证传入的对象有一个run()方法就可以了，这就是动态语言的“鸭子类型”，它并不要求严格的继承体系，一个对象只要“看起来像鸭子，走起路来像鸭子”，那它就可以被看做是鸭子。
