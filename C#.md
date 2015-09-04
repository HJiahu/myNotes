本文摘自 C#入门经典

### 第八章 OOP

***类是模板，对象是实体。对象是类的实例化结果。***

***C#和C++的一个不同点：在C#中关键字new是用来调用类中的构造函数的，并返回一个对象。而在C++中new关键字将在堆中创建对象，并返回这个对象的地址。***这意味着在C#中构造函数不是系统自动调用的。

？？？？？静态构造函数和静态类，与C++不同的概念。P167

**OOP技术**
1.	接口
> 接口是public属性和方法的集合，是类的创建者和使用者之间的契约。            
> 一个类可以支持多个接口，而多个类也可以使用相同的接口。         
> ***可删除的对象***                   
> IDisposable 接口可以删除对象，一般在C#中对象的清除是依赖于C#的垃圾清理机制。         
> 自动调用IDisposable 方法清除对象的语法：          
> classname VariableName = new classname();               
> using (VariableName)                
> {      ....       }                          
> 或者直接点：            
> using (classname VariableName = new classname())             
> {...               }            
> 当using代码块结束时，系统会调用IDisposable方法自动清除对象，而不用等到C# 的垃圾清理机制。

2.	继承   
> C#中只能实现类的继承，不支持继承多个类。

3.	多态性
> ***简单来说多态性是“一个接口多个方法”  对象需要执行的代码在运行时才能确定。多态性是通过虚函数来实现的。***            
> 例如：dog类和cat类都是继承自animal类。animal类中有eat方法。               
> dog dog1 = new dog();      
> animal an = dog1 ;           
> an.eat();  //dog's eat()           
> animal an = new cat();             
> an.eat();  //cat's eat()          
接口的多态性：     
Cow myCow = new Cow();                    
Chicken myChicken = new Chicken();                         
IConsume consumeInterface;                   
consumeInterface = myCow;               
consumeInterface.EatFood();                  
consumeInterface = myChicken;                 
consumeInterface.EatFood();                 

4.	事件 

5.	引用类型和值类型 
> 在这里不要将引用类型和C++中的引用想混淆，这里的引用类型指的是数据的存储方式，而C++中的引用可以认为是数据的调用方式。           
> 值类型：可以认为变量名就是变量的地址虽然说在C#中没有指针，也可以说不同的变量名代表了不同的内存空间。                    
> 引用类型相当于C++中的指针，即变量名是一个指针，这个指针指向的才是这个数据的存储位置。            
> ***在C#中structure是值类型，而class是引用类型。***

### 第九章 定义类
```
internal/public abstract/sealed class Myclass : Mybase ,Interface_1 , Interface_2...
{

}  //与C++的区别是这里没有分号
```
说明：              
默认情况下C++中的类声明是内部的，即internal。           
abstract：抽象类，不能实例化但可以继承。         
sealed：         

一般在冒号的后面首先跟父类，再跟接口，如果没有继承父类则冒号后可直接跟接口。***父类和接口的次序不能颠倒***             


下面的代码是不能通过编译的：
```
internal class MyBase
{
// Class members.
}
public class MyClass : MyBase         //继承类扩展了父类的作用域，这是不允许的。
{
// Class members.
}
```
***如果类的声明是internal则其能继承于internal和public的父类，但如果类的声明是public，则其不能继承internal型的类。***                  

接口的定义：           
```
internal/public interface IMyInterface : IMyBaseInterface, IMyBaseInterface2
{
// Interface members.
}
```
所有类的根都是System.Object，而这个类中有一些可以直接使用的方法：
-	Object():构造函数，由派生类构造函数自动调用。
-	~Object()（也称为Finalize()）:析构函数，由派生类自动调用，不能手动调用。
-	bool Equals(Object) :在C#中对象是引用数据类型，故这个方法会查看两个参数是否引用了相同的对象。
-	bool Equals(Object_1 , Object_2) :即使两个参数都引用了NULL，依旧会返回true，因为两个NULL引用是一样的。
-	...
-	...

类的实例化过程：              
-	为了实例化派生的类，必须实例化其基类。故实例化一个类必然首先调用System.Object.Object();
> 举个简单的例子，创建了一个新的类dog，其继承于animal，那么在实例化dog时，首先调用System.Object.Object(),然后调用animal的构造函数，再才是dog的构造函数。

-	C#的构造函数初始化器，base() 和 this()  base按照其参数表的形式指定基类的构造函数，而this会依照参数表先调用指定的构造函数。例如：
> public class MyDerivedClass : MyBaseClass              
	{                     
		public MyDerivedClass() : this(5, 6)                      
		{                  
		}              
		...             
		public MyDerivedClass(int i, int j) : base(i)           
		{               
		}           
	}               
如果使用默认的构造函数，那么上面的代码的构造函数调用次序为：    
	1.	执行 System.Object.Object 构造函数。
	2.	执行 MyBaseClass.MyBaseClass(int i)构造函数。
	3.	执行 MyDerivedClass.MyDerivedClass(int i, int j)构造函数。
	4.	执行 MyDerivedClass.MyDerivedClass()构造函数。                
***如果没有给构造函数指定构造函数初始化器，编译器就会自动添加 base()， 这会执行本节前面介绍的默认序列。***

***类库项目：***                          
如果一个项目中只包含类而没有接口，那么这个项目就称为类库。而类库一般就编译为.dll文件。P196

***接口和抽象类***                
-	两者的相似之处：都有可以由派生类继承的成员。而且两者都不能直接实例化，但两者都可以声明变量，作为左值。
-	不同之处：类只能有一个基类，但可以由多个接口。

### 第十章 定义类成员
-	在C#中对于类中成员访问的限制，C#与C++是有区别的，C#中比C++多了一个internal关键字，这意味着对象中的成员只能在本项目中被调用。例如类库中的某些成员是组成类库的一部分，但在类库之外的项目中是无法调用这些成员的。
-	在C#中定义的成员，每一个前面都要加上访问限定符，这与C++也有一定的区别。
-	C#类中比C++多了几种种限定符，一种是readonly（用于字段）， 还有一种是sealed（表明方法不能被重写），还有其他的。
-	如果在C#中定义了一个成员，并且使用static进行了修饰，那么在C#中这类成员就只能使用类名进行访问，而在C++中使用对象也是可以访问这些成员的 。
-	其他关键字：
	-	virtual——方法可以重写。                  
	-	abstract——方法必须在非抽象的派生类中重写(只用于抽象类中)。                 
	-	override——方法编写了一个基类方法(如果方法被重写，就必须使用该关键字)。                
	-	extern——方法定义放在其他地方。                   
-	***字段和属性：***
	-	字段：类似于C++中的变量的定义。
	-	属性：在字段的基础之上，按照我的理解，属性是附加在字段上的一些操作。
	> ```
		// Field used by property.
		private int myInt;  //这是字段
		// Property.
		public int MyIntProp  //这是属性，属性比字段多了两个访问器，get和set
		{
		get
			{
			return myInt;
			}
		protected set
			{
			if (value >= 0 && value <= 10) myInt = value;
			else
			throw (new ArgumentOutOfRangeException("MyIntProp", value, "MyIntProp must be assigned a value between 0 and 10."));
			}
		}
	```               
属性可以使用 virtual、 override 和 abstract 关键字，就像方法一样，但这几个关键字不能用于字段。

P209
