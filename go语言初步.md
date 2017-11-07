### 基本概念
*	Go是静态类型的语言，它的类型系统没有层级。
*	Go完全是垃圾回收型的语言，并为并发执行与通信提供了基本的支持。
*	按照其设计，Go打算为多核机器上系统软件的构造提供一种方法。

### gopath
*	Unix：`export GOPATH=/home/apple/mygo`
*	win32：`GOPATH=c:\mygo`，新建一个环境变量GOPATH并赋值，像处理path变量一样
*	当有多个GOPATH时，默认会将go get的内容放在第一个目录下
*	`$GOPATH` 目录约定有三个子目录
	*	src 存放源代码（比如：.go .c .h .s等）
	*	pkg 编译后生成的文件（比如：.a）
	*	bin 编译后生成的可执行文件（为了方便，可以把此目录加入到 $PATH 变量中，如果有多个gopath，那么使用${GOPATH//://bin:}/bin添加所有的bin目录）

### 常见命令
*	go install，进入对应的应用包目录编译应用
*	go build，编译程序
	*	如果是普通包，执行go  build之后，它不会产生任何文件。如果是main包，当你执行go  build之后，它就会在当前目录下生成一个可执行文件。
	*	可以指定编译输出的文件名：go build -o oo.exe
	*	go build命令默认会编译当前目录下的所有go文件但会忽略目录下以“_”或“.”开头的go文件
	*	如果你的源代码针对不同的操作系统需要不同的处理，那么你可以根据不同的操作系统后缀来命名文件。
*	go get，获取远程包（go get本质上可以理解为首先第一步是通过源码工具clone代码到src下面，然后执行go install）。go get -u 参数可以自动更新包，而且当go get的时候会自动获取该包依赖的其他第三方包。通过这个命令可以获取相应的源码，对应的开源平台采用不同的源码控制工具，例如github采用git、googlecode采用hg，所以要想获取这些源码，必须先安装相应的源码控制工具。
*	go clean，用来移除当前源码包和关联源码包里面编译生成的文件
*	go fmt，go强制了代码格式（比如左大括号必须放在行尾）使用go fmt命令，其实是调用了gofmt，而且需要参数-w，否则格式化结果不会写入文件。gofmt -w -l src，可以格式化整个项目。
*	go test，执行这个命令，会自动读取源码目录下面名为*_test.go的文件，生成并运行测试用的可执行
文件。
*	go run，编译并运行Go程序
*	go tool，
*	go generate
*	godoc，

### 语言基础
*	一些规则
	*	零值，go中的零值不是空值nil，而是默认值，对于整数与浮点数一般是`0`，字符串就是`""`
	*	全局的且以大写开头的变量与函数是public的，即可以在包外使用如：fmt.Print()
	*	数组（array）的定义：`var arr [n]type`
		*	数组的长度也是数组类型的一部分，即不同长度的数组是不同的类型。数组的长度不看变
		*	go中数组的赋值使用的是pass by value，将赋值整个数组而非指针，这点与C不同
		*	`c := [...]int{4, 5, 6}` //由编译器自动推测长度
		*	`b := [10]int{1, 2, 3}` //只设定一部分，其他为默认值
		*	`easyArray := [2][4]int{{1, 2, 3, 4}, {5, 6, 7, 8}}` //多维数组
		*	array中的切片语法与pyton相似
	*	动态数组（slice）
		*	声明方式：`var fslice []int` //与array相比没有指定长度
		*	slice是引用类型，可以将其看做opencv中的Mat，拷贝时默认为浅拷贝
		*	`slice := []byte {'a', 'b', 'c', 'd'}`
		*	slice对象中有几个内置成员函数：len、cap(最大容量)、append、copy（类似于Mat::clone）
	*	字典（map，与C++中的map<type>相似）
		*	声明方式：`var varable map[keyType]valueType`
		*	**map和其他基本型别不同，它不是thread-safe，在多个go-routine存取时，必须使用mutex lock机制**。
		*	map也是一种引用类型。
		*	自动推导的方式：`rating := map[string]float32{"C":5, "Go":4.5 }`
		*	使用示例：`numbers["ten"] = 10 //赋值`
		*	`csharpRating, ok := rating["C#"]`，map有两个返回值，第二个返回值，如果不存在key，那么ok为false，如果存在ok为true
	*	make&new
		*	new
			*	new与C++中的关键字new类似，用于分配内存，但GO中没有堆栈之分，go中new也返回指针
			*	go中的new将初始化内存
		*	make
			*	make只能创建內建类型（map、slice、channel）,make返回的不是指针而是初始化了的对应类型的变量。如果上面三个类型的变量没有初始化则为nil，make返回的都已经初始化。	
	
*	代码示例

		//说明当前文档所属的包，GO中包名和文件名可以不一样
		package main  //main包很特殊，表明当前文件是一个独立的执行入口包
	
		import(
			"fmt"
			"errors"
		)
	
		func main(){ //go中的main是没有返回值与参数的
			fmt.Println("你好！") //go默认使用utf8作为编码标准
			
			//变量定义，go中强制每个类型都有初始值
			//var name type 
			var a,b int = 1,2 //a b 都是int类型的变量，int型具体长度依赖编译器实现
			//byte(uint8)、int、uint、int32(rune)、uint32，complex128
			var c int64  //c 的长度固定为64位
			//GO中各种类型之间不能进行操作与赋值，下面的操作将报错
			//c := a + c
			d := a  //:= 使用:=后变量的类型自动推导前面变量的类型，这种语法只能用于函数内
			var e = b //这样也是自动推导e的变量类型
			//可以在需要的地方使用 _ 作为占位符，但 _ 是不能作为正常变量使用的，默认float64
			_,f := 1.0,2.0 
			const g = "hello" //使用const关键字可自动推导类型 
			var h bool //h默认为 false
			var ( // 或 var ( 等
				i int
				pi float32
				prefix = "go_"
			)
			//go中的字符串可以使用双引号("")或反引号(``)包含
			str1,str2 := `hello`,"aworld" //使用``包含的字符串是raw字符串
			//str[0] = 'm' //与python类似，go中的字符串默认常量，无法更改。可以改成[]byte
			str1 = str1+str2[1:] //与python类似，go中的字符串可以进行切片操作
			err := errors.New("this is a error")
			if err != nil{ //go中有一个error类型，专门用于处理错误信息
				fmt.Print(err)
			}
			//go中的关键字iota用于声明枚举变量时使用
			//除非被显式设置为其它值或iota，每个const分组的第一个常量被默认设置为它的0值
			//第二及后续的常量被默认设置为它前面那个常量的值，如果前面那个常量的值是iota，
			//则它也被设置为iota。
			const (
				x = iota //x == 0，默认开始值为0
				c = "c"
				y = iota //y == 1
				z  		 //z == 3
			)
			const w = iota //w == 0，因为iota每遇见一个const关键时都会重置为0 
		}