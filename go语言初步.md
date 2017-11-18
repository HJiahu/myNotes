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
*	godoc，打开本地的参考文档。`godoc -http=:8000`，可以在8000端口打开网页版参考文档
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


### 语言基础
*	一些概念
	*	零值，go中的零值不是空值nil，而是默认值，对于整数与浮点数一般是`0`，字符串就是`""`
	*	全局的且以大写开头的变量与函数是public的，即可以在包外使用如：fmt.Print()
	*	go中的指针
		*	声明：`var a *int`
		*	星号与C中的功能时相同的，声明与解引用都是星号 `*`
		*	与C一致，go中使用 `&` 求变量的地址
	*	数组（array）的定义：`var arr [n]type`
		*	数组的长度也是数组类型的一部分，即不同长度的数组是不同的类型。数组的长度不可变
		*	**go中数组是可以赋值的**，且赋值使用的是pass by value，将赋值整个数组而非指针，这点与C不同
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
	*	go中的结构体
		*	结构体类型定义方式 
		
				type person struct {
			        name string
			        age int
			    }
		*	结构体变量声明与定义方式
			*	`var P person`
			*	`P := person{“Tom”, 25}`//顺序提供初始化值
			*	`P := person{age:24, name:“Tom”}`//任意顺序的初始化值
			*	`P := new(person)`
		*	匿名字段
			*	只提供类型，而不写字段名的方式，也就是匿名字段，也称为嵌入字段
			*	所有的内置类型和自定义类型都是可以作为匿名字段的
			*	当匿名字段是一个struct的时候，那么这个struct所拥有的全部字段都被隐式地引入了当前定义的这个struct。当前struct使用匿名struct中的成员时与使用自己字段的语法是相同的。而且匿名字段亦可以作为当前字段的一个字段(如下代码示例)。
			*	对于同名字段，go的解决办法很简单：最外层的优先访问

					package main
				    import "fmt"
				    type Skills []string
				    type Human struct {
				        name string
				        age int
				        weight int
				    }
				    type Student struct {
				        Human  // 匿名字段，struct
				        Skills // 匿名字段，自定义的类型string slice
				        int    // 内置类型作为匿名字段
				        speciality string
				    }
					func main() {
					    // 初始化学生Jane
					    jane := Student{Human:Human{"Jane", 35, 100}, speciality:"Biology"}
					    // 现在我们来访问相应的字段
					    fmt.Println("Her name is ", jane.name)
					    // 我们来修改他的skill技能字段
					    jane.Skills = []string{"anatomy"}
					    fmt.Println("Her skills are ", jane.Skills)
					    // 修改匿名内置类型字段
					    jane.int = 3
					}
	*	make&new
		*	new
			*	new与C++中的关键字new类似，用于分配内存，但GO中没有堆栈之分，go中new也返回指针
			*	go中的new将初始化内存
		*	make
			*	make只能创建內建类型（map、slice、channel）,make返回的不是指针而是初始化了的对应类型的变量。如果上面三个类型的变量没有初始化则为nil，make返回的都已经初始化。	
	*	go的switch中的每个case语句自带break，与C有明显的差别
	*	go中的函数声明
		*	` func funcName(input1 type1, input2 type2) (output1 type1, output2 type2)...return v1,v2...`
		*	变量output1和output2不想声明也可以，直接就两个类型
		*	如果只有一个返回值且不声明返回值变量，那么可以省略包含返回值的括号
	*	go中的函数变量
		*	go中的函数也可以作为变量进行传递，C中只能传递函数指针，不过二者的机制是相同的，go对一些概念进行了抽象
		*	函数类型的声明：`type typeName func(input1 inputType1 , ...`
	*	go中的变参：`func myfunc(arg ...int) {}`，变量arg是一个int的slice
	*	defer关键字
		*	使用defer关键字修饰的语句将在函数返回前**逆序执行**，这与C++11中的lock_gurad思想类似，不过go中的defer语句是在函数返回语句之前执行。可以假设每个函数中都有一个defer栈，每一个出现的defer语句都将推入栈中，然后在返回前依次出栈执行。
	*	init函数
		*	init与main一样，不能有参数与返回值
		*	一个包里可以有任意多个init函数，但一般定义一个最好
		*	当一个包被导入时其中的包级常量与变量将被初始化（重复导入的包只初始化一次），然后init中将会被依次执行。最后系统将初始化main包中的变量然后执行main函数
	*	go中的面向对象
		*	go中的成员函数处理其实就是C++类中成元的处理方式
		*	go中可以为任何自定义与内置类型添加方法
		*	A method is a function with an implicit first argument, called a receiver.
		*	go中method的继承很简单：包含匿名字段的struct可以直接使用这个匿名字段中的方法
		*	method方法重写的原理也很简单：外层优先
		*	go中所有的成员都定义在类型外，通过类型关联对应的方法：
				
				//类型方法的定义方式，有两种：传值与传指针（ReceiverType指针类型）
				//func (r ReceiverType) funcName(parameters) (results)
				type Rectangle struct{
					width,height float64
				}
				//定义求Rectangle面积的方法
				//这行和下一行语法的区别在于前者传指针，后者传值
				//虽然计算结果相同但效率不同且后者更改的是“临时变量”（C++概念）
				//func (r *Rectangle)area float64{
				func (r Rectangle)area float64{
					//无论r是传值还是指针，都可以使用点运算获得对象的成员
					//如果r是指针那么想C那样(*r).width也是可以的
					return r.width*r.height 
				}
				//如果rect是rectangle类型，调用方法：rect.area();
				//
	*	go中的并发
		*	goroutine
			*	goroutine其实就是协程，且运行在相同的地址空间，go使用`runtime.Gosched()`实现协程的切换
			*	go 1.5前使用单线程运行协程，1.5后默认使用CPU的核数，可以使用`runtime.GOMAXPROCS(n)`设定线程数，如果n<1则不会改变当前的设置。
		*	channel(goroutine间的内存共享与同步工具，分缓冲和非缓冲两种)
			*	使用make创建channel：`ci := make(chan int)`
			*	channel通过操作符<-来接收和发送数据：`ci <- v // 发送v到channel ci.`、`fmt.Println(<-ci) //从ci中提取数据`
			*	默认情况下（非缓冲型channel），channel接收和发送数据都是阻塞的，除非另一端已经准备好
			*	Buffered Channels：可以指定channel的缓冲大小（`ch := make(chan type, value)`）,这样在写channel时有空余的缓冲空间则不阻塞、在读时如果有有效的缓冲空间可读则不阻塞
			*	range和close。我们可以像读数组与slice那样读缓冲型channel：`for i:= range() ci {...}`//for退出的条件是显示的对于channel调用close
			
*	代码示例

		//说明当前文档所属的包，GO中包名和文件名可以不一样
		package main  //main包很特殊，表明当前文件是一个独立的执行入口包
	
		import(
			"fmt"
			"errors"
			"./model" // 使用相对路径导入模块，亦可以使用绝对路径导入包
			. "xxx"   // 可以不使用前缀使用包xxx中的成员
			f "xxx"   // 为包xxx取个别名
			_ "xxx"   // 引入包xxx但不使用其中的函数，仅仅调用了包中的init函数
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
			//可以在需要的地方使用 _ 作为占位符，但 _ 是不能作为正常变量使用的，f默认float64
			//go中声明但没有使用变量将报错，故使用 _ 丢弃部分函数返回值
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
			
			//流程与函数
			if x := fun();x>0{//if的条件判断中可以声明一个变量，也可以没有
				...
			} else{
				...
			}
			for expression1; expression2; expression3 {
        		//...
    		}
			for sum < 1000 {//go中没有while关键，其功能使用for实现
				sum += sum
			}
			for _, v := range map{
				fmt.Println("map's val:", v)
			}

		}

		//go中函数的声明顺序不像C那么严格，这点go与python类似：先扫描文档，后找依赖关系
		//a的类型为离其最近的类型
		func max(a, b int) int {
	        if a > b {
	            return a
	        }
	        return b
		}
		
		//如果在返回参数列表中有变量名，可以使用不带参数的返回值语句返回这两个参数
		func SumAndProduct(A, B int) (add int, Multiplied int) {
		    add = A+B
		    Multiplied = A*B
		    return
		}