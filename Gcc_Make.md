##GCC

### 无选项编译和链接：              
-	`gcc test.c ` 直接输出可执行文件 a.exe 或a.out 。 注意gcc和g++是不同的，gcc只编译C，而g++编译C和C++。               

-	指定输出文件的名称：`gcc test.c -o test.exe`


### 如果有多个源文件，基本上有两种编译方法：         
假设有两个源文件为test.c和testfun.c                
1.	多个文件一起编译：gcc testfun.c test.c -o test                           
2.	分别编译各个源文件，之后对编译后输出的目标文件链接
          
	gcc -c testfun.c //将testfun.c编译成testfun.o             
	gcc -c test.c //将test.c编译成test.o              
	gcc  testfun.o test.o -o test //将testfun.o和test.o链接成test              

-	以上两种方法相比较，第一中方法编译时需要所有文件重新编译，而第二种方法可以只重新编译修改的文件，未修改的文件不用重新编译。 

### Overall option（全局选项）

-	-x language
	> 明确指出后面输入文件的语言为 language (而不是从文件名后缀得到的默认选择).这个选项应用于后面 所有的输入文件,直到遇着下一个-x选项. language 的可选值有 c,objective-c, c-header, c++, cpp-output, assembler,和assembler-with-cpp。
-	-x none 
	> 关闭任何对语种的明确说明,因此依据文件名后缀处理后面的文件(就象是从未使用过-x选项)。
-	-c 
	> 编译或汇编源文件,但是不作连接.编译器输出对应于源文件的目标文件. 缺省情况下, GCC 通过用.o替换源文件名后缀.c, .i, .s,等等,产生目标文件名.可以使用-o 选项选择其他名字. GCC 忽略-c 选项后面任何无法识别的输入文件(他们不需要编译或汇编).   
-	-S 
	> 编译后即停止,不进行汇编.对于每个输入的非汇编语言文件,输出文件是汇编语言文件. 缺省情况下, GCC 通过用.o替换源文件名后缀.c, .i,等等,产生 目标文件名.可以使用-o 选项选择其他名字. GCC 忽略任何不需要编译的输入文件. 
-	-E 
	> 预处理后即停止,不进行编译.预处理后的代码送往标准输出. GCC 忽略任何不需要预处理的输入文件.
-	-o file  
	> 指定输出文件为file.该选项不在乎GCC 产生什么输出,无论是可执行文件,目标文件,汇编文件还是 预处理后的C 代码. 由于只能指定一个输出文件,因此编译多个输入文件时,使用-o选项没有意义,除非输出一个可执行文件. 如果没有使用-o选项,默认的输出结果是:可执行文件为a.out.
-	-v 
	>(在标准错误)显示执行编译阶段的命令.同时显示编译器驱动程序,预处理器,编译器的版本号. 
-	-pipe 
	> 在编译过程的不同阶段间使用管道而非临时文件进行通信.这个选项在某些系统上无法工作,因为那些系统的汇编器不能从管道读取数据. GNU的汇编器没有这个问题. 


### Linker option（链接选项）
-	object-file-name
	> 如果某些文件没有特别明确的后缀 a special recognized suffix, GCC 就认为他们是目标文件或库文件. (根据文件内容,连接器能够区分目标文件和库文件).如果GCC 执行连接操作,这些目标文件将成为连接器的输入文件.
-	-l library
	> 连接名为library 的库文件. 连接器在标准搜索目录中寻找这个库文件,库文件的真正名字是liblibrary.a.连接器会 当做文件名得到准确说明一样引用这个文件. 搜索目录除了一些系统标准目录外,还包括用户以-L选项指定的路径. 一般说来用这个方法找到的文件是库文件---即由目标文件组成的归档文件(archive file).连接器处理归档文件的 方法是:扫描归档文件,寻找某些成员,这些成员的符号目前已被引用,不过还没有被定义.但是,如果连接器找到普通的目标文件,而不是库文件,就把这个目标文件按平常方式连接进来.指定-l选项和指定文件名的唯一区别是, -l 选项用lib和.a把library 包裹起来,而且搜索一些目录.
-	-L dir 
	> 为-l添加扫描目录dir，在连接时连接器会在dir文件夹下迭代的搜寻库文件。
-	-l objc
	> 这个-l 选项的特殊形式用于连接Objective C 程序.
-	-I 
	> 指定头文件的位置，这样当头文件不在当前文件夹时，gcc会自动的在指定文件夹中寻找。
-	-nostartfiles
	> 不连接系统标准启动文件,而标准库文件仍然正常使用.
-	-nostdlib
	> 不连接系统标准启动文件和标准库文件.只把指定的文件传递给连接器.
-	-static
	> 在支持动态连接(dynamic linking)的系统上,阻止连接共享库.该选项在其他系统上无效.
-	-shared
	> 生成一个共享目标文件,他可以和其他目标文件连接产生可执行文件.只有部分系统支持该选项.
-	-symbolic
	> 建立共享目标文件的时候,把引用绑定到全局符号上.对所有无法解析的引用作出警告(除非用连接编辑选项 -Xlinker -z -Xlinker defs取代).只有部分系统支持该选项.
-	-Xlinker option
	>把选项option 传递给连接器.可以用他传递系统特定的连接选项, GNU CC 无法识别这些选项. 如果需要传递携带参数的选项,你必须使用两次-Xlinker,一次传递选项,另一次传递他的参数. 例如,如果传递-assert definitions,你必须写成-Xlinker -assert -Xlinker definitions,而不能写成-Xlinker "-assert definitions",因为这样会把整个 字符串当做一个参数传递,显然这不是连接器期待的.
-	-Wl,option
	>把选项option 传递给连接器.如果option 中含有逗号,就在逗号处分割成多个选项.
-	-u symbol
	>使连接器认为取消了 symbol 的符号定义,从而连接库模块以取得定义.你可以使用多个 -u选项,各自跟上不同的符号,使得连接器调入附加的库模块. 


## Makefile

### tips
-	搜索路径和文件的顺序一定要处理好，即包含文件夹要在包含文件之前（L 要在 l之前）
-	***对于GCC而言，-llib 意味着lib 的全名为liblib.a ,系统会默认lib的后缀为.a ，前缀为lib***   使用-l 和-L指令和直接在gcc后添加编译文件的区别在于系统会自动的在-L指定的文件夹中搜索-l后的库，而直接添加库名意味着要写全文件的路径和名，不便于读makefile。
-	通配符：~ 表示用户的$HOME ,~John 表示Johb的HOME；* 任意长度的字符；
-	makefile文件一般保存名称为makefile或者Makefile，没有后缀。
-	make 会一层又一层地去找文件的依赖关系,直到最终编译出第一个目标文件。 
-	在Makefile 中,规则的顺序是很重要的,因为,Makefile 中只应该有一个最终目标,其它的目标都是被这个目标所连带出来的,所以一定要让 make 知道你的最终目标是什么。一般来说,定义在 Makefile 中的目标可能会有很多,但是第一条规则中的目标将被确立为最终的目标。如果第一条规则中的目标有很多个,那么,第一个目标会成为最终的目标。make 所完成的也就是这个目标。
-	变量的定义。
	> 在 Makefile 中我们要定义一系列的变量,变量一般都是字符串,这个有点像 C 语言中的宏,当 Makefile 被执行时,其中的变量都会被扩展到相应的引用位置上。变量的定义方式：sourcefiles = 1.cpp 2.cpp ...变量的引用方式：$(sourcefiles),$(sourcefiles)会像c中打宏定义一样被展开。
-	文件指示。
	> 其包括了三个部分,一个是在一个 Makefile 中引用另一个 Makefile,就像C 语言中的 include 一样;另一个是指根据某些情况指定 Makefile 中的有效部分,就像 C 语言中的预编译 #if 一样;还有就是定义一个多行的命令。
-	注释。
	> Makefile 中只有行注释,和 UNIX 的 Shell 脚本一样,其注释是用“#”字符开头。如果你要在你的 Makefile 中使用“#”字符,可以用反斜框进行转义,如:\# 。最后,还值得一提的是,**在 Makefile 中的命令,必须要以 Tab 键开始。**


### makefile的语法规则
*	**注意在makefile中指令必须以tab键开头，在vim中设定：set tabstop=4**
-	在 Makefile 使用 include 关键字可以把别的 Makefile 包含进来,这很像 C 语言的#include,被包含的文件会原模原样的放在当前文件的包含位置。 
-	包含的语法类似于：include foo.make   *.make  $(macro) 可以在include前面添加一个减号，表示当本行指令存在问题时，make只是警告而不报错停止。
-	在 include 前面可以有一些空字符,但是绝不能是 Tab 键开始。include是make保留的关键字不是shell中可执行的指令。
-	一般来说,makefile的目标基本上是一个文件,但也有可能是多个文件

*	例1：

		targets : prerequisites ; command 
		或者：
		targets : prerequisites
				  command 
	> 冒号前是需要生成的文件，冒号后面是生成这个文件所需要的文件(文件依赖) 。只有在冒号后面的文件比冒号前的文件新，指令command才会被执行。     

*	例2：（这段代码的作用和例1是一样的）

		objects = main.o kbd.o command.o display.o insert.o search.o files.o utils.o
		
		edit : $(objects)
			　　cc -o edit $(objects)
		
		clean :#因为clean后面没有依赖文件所以clean不会主动被执行，需要使用指令make clean
			　　rm edit $(objects)     


*	***make可以自动推导文件以及文件依赖关系后面的命令,只要 make 看到一个.o 文件,它就会自动的把.c 文件加在依赖关系中。***

		objects = main.o kbd.o command.o display.o insert.o search.o files.o utils.o
		edit : $(objects)	#变量的引用
			　　cc -o edit $(objects)
		main.o : defs.h     #自动的将main.cpp当作依赖文件。当make看见.o文件时，会自动将与.o文件前缀同名的源文件添加至依赖文件。
		
		　　... ...
		
		.PHONY : clean
		clean :
			-rm edit $(objects)

*	伪目标一般没有依赖的文件。但是，我们也可以为伪目标指定所依赖的文件。伪目标同样可以作为“默认目标”，只要将其放在第一个。一个示例就是，如果你的 Makefile 需要一口气生成若干个可执行文件，但你只想简单地敲一个 make 完事，并且，所有的目标文件都写在一个 Makefile 中，那么你可以使用“伪目标”这个特性：HONY 意思表示 clean 是一个“伪目标”。而在 rm 命令前面加了一个小减号的意思不要管可能出现的某些错误,继续做后面的事。 

		all : prog1 prog2 prog3
		.PHONY : all
		prog1 : prog1.o utils.o
			cc -o prog1 prog1.o utils.o
		prog2 : prog2.o
			cc -o prog2 prog2.o
		prog3 : prog3.o sort.o utils.o
			cc -o prog3 prog3.o sort.o utils.o


### 文件搜索
*	VPATH变量：指定额外的搜索路径，VPATH=/usr/:../src:./include/  此时VPATH变量中定义了3个路径，不同的路径使用冒号来分隔        
vpath关键字：	vpath关键字有三种使用方法
	1.	vpath %.c /usr/include  其中第一个参数是pattern，第二个参数是路径。在路径下寻找符合pattern的文件，在这里就是寻找后缀为.c的文件。
	2.	vpath %.c 清除后缀为.c的pattern路径，此前定的关于%.c模式的路径都会被删除。
	3.	vpath  删除所有已经设置后的搜索路径。#百分号表示匹配若干个字符，如果名称中含有百分号，此时就要使用转意字符\，类似于\%
