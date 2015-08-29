摘自：[Google C++ stlye][Google Style]

### Google C++命名规则：
-	除了比较常见的缩写如num、dns...在名字中少用缩写。
-	文件名全部使用小写，并可以包含 下划线 \_  	和连接符  -
-	C++ 文件要以 .cc 结尾, 头文件以 .h 结尾. 专门插入文本的文件则以 .inc 结尾，参见:ref:self-contained headers。
```
	my_useful_class.cc
	my-useful-class.cc
	myusefulclass.cc
```
-	为保证唯一性, 头文件包含守卫的命名应该依据所在项目源代码树的全路径. 例如, 项目 foo 中的头文件 foo/src/bar/baz.h 可按如下方式保护:
```
	 #ifndef FOO_BAR_BAZ_H_
	 #define FOO_BAR_BAZ_H_
			…
	 #endif // FOO_BAR_BAZ_H_
```
-	所有类型命名 —— 类, 结构体, 类型定义 (typedef), 枚举 —— 均使用相同约定. 例如:
```
	// classes and structs
	class UrlTable { ...
	class UrlTableTester { ...
	struct UrlTableProperties { ...

	// typedefs
	typedef hash_map<UrlTableProperties *, string> PropertiesMap;

	// enums
	enum UrlTableErrors { ...
```
-	变量名一律小写, 单词之间用下划线连接. 类的成员变量以下划线结尾, 但结构体的就不用。   
```
a_local_variable, a_struct_data_member, a_class_data_member_.i
string table_name;  // 可 - 用下划线。
string tablename;   // 可 - 全小写。
```
-	类数据成员：    
不管是静态的还是非静态的，类数据成员都可以和普通变量一样, 但要接下划线。
```
class TableInfo {
  ...
 private:
  string table_name_;  // 可 - 尾后加下划线。
  string tablename_;   // 可。
  static Pool<TableInfo>* pool_;  // 可。
};
```
-	结构体变量:     
不管是静态的还是非静态的，结构体数据成员都可以和普通变量一样, 不用像类那样接下划线:
```
struct UrlTableProperties {
    string name;
    int num_entries;
};
```
-	全局变量:     
对全局变量没有特别要求, 少用就好, 但如果你要用, 可以用 ***g_*** 或其它标志作为前缀, 以便更好的区分局部变量.
-	***常量命名：***    
在全局或类里的常量名称前加 k: kDaysInAWeek. 且除去开头的 k 之外每个单词开头字母均大写。所有编译时常量, 无论是局部的, 全局的还是类中的, 和其他变量稍微区别一下. k 后接大写字母开头的单词:
```
const int kDaysInAWeek = 7;
```
-	函数命名    
常规函数使用大小写混合, 取值和设值函数则要求与变量名匹配。函数名的每个单词首字母大写, 没有下划线：
```
	MyExcitingFunction()
	MyExcitingMethod()
	my_exciting_member_variable()
	set_my_exciting_member_variable().
```
如果您的某函数出错时就要直接 crash, 那么就在函数名加上 OrDie. 但这函数本身必须集成在产品代码里，且平时也可能会出错。
```
	AddTableEntry()
	DeleteUrl()
	OpenFileOrDie()
```


***不要內联超过十行的代码。***     
内联函数必须放在 .h 文件中.

定义函数时先是输入参数然后是输出参数。输入参数一般是传值或const引用。即使是新加的只输入参数也要放在输出参数之前。

项目内头文件应按照项目源代码目录树结构排列, 避免使用 UNIX 特殊的快捷目录 . (当前目录) 或 .. (上级目录). 
例如, google-awesome-project/src/base/logging.h 应该按如下方式包含:   
	`#include “base/logging.h”`   







[Google Style]:http://zh-google-styleguide.readthedocs.org/en/latest/google-cpp-styleguide/end/
