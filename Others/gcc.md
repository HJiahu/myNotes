### 无选项编译和链接：              
-	`gcc test.c `   
>直接输出可执行文件 a.exe 或a.out 。 注意gcc和g++是不同的，gcc只编译C，而g++编译C和C++。作用：将test.c预处理、汇编、编译并链接形成可执行文件。这里未指定输出文件，默认输出为a.out。

-	`gcc test.c -o test.exe`
>指定输出文件的名称。 

### 如果有多个源文件，基本上有两种编译方法：         
假设有两个源文件为test.c和testfun.c                
1.	多个文件一起编译
>用法：gcc testfun.c test.c -o test              
>作用：将testfun.c和test.c分别编译后链接成test可执行文件。            

2.	分别编译各个源文件，之后对编译后输出的目标文件链接
>用法：             
gcc -c testfun.c //将testfun.c编译成testfun.o             
gcc -c test.c //将test.c编译成test.o              
gcc  testfun.o test.o -o test //将testfun.o和test.o链接成test              

以上两种方法相比较，第一中方法编译时需要所有文件重新编译，而第二种方法可以只重新编译修改的文件，未修改的文件不用重新编译。 

### Overall option（全局选项）

-	-x language
>明确指出后面输入文件的语言为 language (而不是从文件名后缀得到的默认选择).这个选项应用于后面 所有的输入文件,直到遇着下一个-x选项. language 的可选值有 c,objective-c, c-header, c++, cpp-output, assembler,和assembler-with-cpp。

-	-x none 
>关闭任何对语种的明确说明,因此依据文件名后缀处理后面的文件(就象是从未使用过-x选项)。

-	-c 
>编译或汇编源文件,但是不作连接.编译器输出对应于源文件的目标文件. 缺省情况下, GCC 通过用.o替换源文件名后缀.c, .i, .s,等等,产生目标文件名.可以使用-o 选项选择其他名字. GCC 忽略-c 选项后面任何无法识别的输入文件(他们不需要编译或汇编).     

-	-S 
>编译后即停止,不进行汇编.对于每个输入的非汇编语言文件,输出文件是汇编语言文件. 缺省情况下, GCC 通过用.o替换源文件名后缀.c, .i,等等,产生 目标文件名.可以使用-o 选项选择其他名字. GCC 忽略任何不需要编译的输入文件. 

-	-E 
>预处理后即停止,不进行编译.预处理后的代码送往标准输出. GCC 忽略任何不需要预处理的输入文件.

-	-o file  
>指定输出文件为file.该选项不在乎GCC 产生什么输出,无论是可执行文件,目标文件,汇编文件还是 预处理后的C 代码. 由于只能指定一个输出文件,因此编译多个输入文件时,使用-o选项没有意义,除非输出一个可执行文件. 如果没有使用-o选项,默认的输出结果是:可执行文件为a.out.

-	-v 
>(在标准错误)显示执行编译阶段的命令.同时显示编译器驱动程序,预处理器,编译器的版本号. 

-	-pipe 
>在编译过程的不同阶段间使用管道而非临时文件进行通信.这个选项在某些系统上无法工作,因为那些系统的汇编器不能从管道读取数据. GNU的汇编器没有这个问题. 


### Linker option（链接选项）
-	object-file-name
>如果某些文件没有特别明确的后缀 a special recognized suffix, GCC 就认为他们是目标文件或库文件. (根据文件内容,连接器能够区分目标文件和库文件).如果GCC 执行连接操作,这些目标文件将成为连接器的输入文件.

-	-l library
>连接名为library 的库文件. 连接器在标准搜索目录中寻找这个库文件,库文件的真正名字是liblibrary.a.连接器会 当做文件名得到准确说明一样引用这个文件. 搜索目录除了一些系统标准目录外,还包括用户以-L选项指定的路径. 一般说来用这个方法找到的文件是库文件---即由目标文件组成的归档文件(archive file).连接器处理归档文件的 方法是:扫描归档文件,寻找某些成员,这些成员的符号目前已被引用,不过还没有被定义.但是,如果连接器找到普通的目标文件,而不是库文件,就把这个目标文件按平常方式连接进来.指定-l选项和指定文件名的唯一区别是, -l 选项用lib和.a把library 包裹起来,而且搜索一些目录.

-	-L dir 
>为-l添加扫描目录dir，在连接时连接器会在dir文件夹下迭代的搜寻库文件。

-	-I 
>指定头文件打位置，这样当头文件不在当前文件夹时，gcc会自动的在指定文件夹中寻找。

-	-l objc
>这个-l 选项的特殊形式用于连接Objective C 程序.

-	-nostartfiles
>不连接系统标准启动文件,而标准库文件仍然正常使用.

-	-nostdlib
>不连接系统标准启动文件和标准库文件.只把指定的文件传递给连接器.

-	-static
>在支持动态连接(dynamic linking)的系统上,阻止连接共享库.该选项在其他系统上无效.

-	-shared
>生成一个共享目标文件,他可以和其他目标文件连接产生可执行文件.只有部分系统支持该选项.

-	-symbolic
>建立共享目标文件的时候,把引用绑定到全局符号上.对所有无法解析的引用作出警告(除非用连接编辑选项 -Xlinker -z -Xlinker defs取代).只有部分系统支持该选项.

-	-Xlinker option
>把选项option 传递给连接器.可以用他传递系统特定的连接选项, GNU CC 无法识别这些选项. 如果需要传递携带参数的选项,你必须使用两次-Xlinker,一次传递选项,另一次传递他的参数. 例如,如果传递-assert definitions,你必须写成-Xlinker -assert -Xlinker definitions,而不能写成-Xlinker "-assert definitions",因为这样会把整个 字符串当做一个参数传递,显然这不是连接器期待的.

-	-Wl,option
>把选项option 传递给连接器.如果option 中含有逗号,就在逗号处分割成多个选项.

-	-u symbol
>使连接器认为取消了 symbol 的符号定义,从而连接库模块以取得定义.你可以使用多个 -u选项,各自跟上不同的符号,使得连接器调入附加的库模块. 
