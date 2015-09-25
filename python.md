本文摘自：[廖雪峰的python博客](http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000)

注意因为python是用缩进来表示不同的代码块，故不要随便的使用缩进。        

python使用`#`作为注释的开始。

python hello.py   使用python解释权执行python程序。

在linux和Mac下可以为.py文件添加可执行权限：
-	在文档的第一行添加文件的执行程序：`#!/usr/bin/env python3`
-	为代码添加权限：`chomd a+x *.py`


`print('The quick brown fox', 'jumps over', 'the lazy dog')`
> print()会依次打印每个字符串，遇到逗号“,”会输出一个空格。

name = input('please enter your name:')

exit()

python 可以使用单引号和双引号表示字符串，`printf('hello')`。如果字符串里面有很多字符都需要转义，则可以在字符串的前面加上r，表示在引号中的字符串不再转义。`print(r'\\\t\\')`

三个单引号包含的字符串的排版是所见即所得的。（也可以使用r来表示不转义）
> ```
 print('''line1
 line2
 line3''')
 ```
 打印的出来的形式就是：
 ```
 line1
 line2
 line3
 ```

 python 中的逻辑运算：not   and  or  

 python3 中的两种除法：
 -	` / `普通的算术除法：10/3 得 3.33333333333...
 -	` // `地板除：10/3 得  3 ，这个类似于C中的整数相除。

 python3 的编码问题：
-	***在计算机内存中，统一使用Unicode编码，当需要保存到硬盘或者需要传输的时候，就转换为UTF-8编码。***
-	python3使用unicode来编码其字符串。
-	python提供`ord('A')`（返回65）函数来获得字符对应的unicode 编码。`chr(25991)`（返回汉字“文”）可以把编码转化为对应的符号。
-	如果知道字符的整数编码，还可以用十六进制这么写str：`'\u4e2d\u6587'`

字符串和编码
