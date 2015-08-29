# title1 多级标题
## title2
### title3
#### title4
##### title5
###### title6
markdown 允许六级标题，分别在行的**起始**处使用1到6个 # 。为了保持美观可以在#和标题之间留下空格。  

## 转义
就像C中printf函数中的\n \a 那样，因为n和a已经有自己本身的含义了，故加上斜杆将其转义。在markdown语法中，有些符号被markdown赋予了特殊的意思，故在使用这些符号的文本意思时要加转义斜杆。  
例如：
> \*在markdown中有特殊的意义，当用两个\*（或\_）包围文本时这些被包含的文本会显式为斜体。  
> 故如果你想输入文本\*号，就应该输入\\\*  。  
> markdown 中有特殊意义的符号有：  
> \*   \_   


## 换行（在一个文本段内）
*	在markdown中<cr>不代表换行。平时我们在记事本，和其他编辑txt文本的软件中编辑文档时，每次换行一般都输入enter键，也就是<cr>。可是在markdown语法规则中，两个空格才代表换行。也就是说当我们在使用markdown语法编辑文本时，在点击enter键之前，先输入两个空格在行尾，这样在将markdown 语法文本转化为其他格式文本时，这些换行还是存在的。这在markdown中称为软换行。
*	markdown中还有一中所谓的硬换行，那就是文本之间留一个空行。这样当文本转化格式之后，这种换行还是存在的。
*	**注意**  
这里所说的换行是一整个文本段内，不包含有标题和下面将要说到的列表。但是当标题为空白时最好在#后添加两个空格。一个列表条目内的文本软换行也要加空格，引用文本一样要加空格实现软换行。

## *斜体*和**黑体**
*	黑体：使用\*\*或\_\_ 将文本包围住： markdown  **markdown**  __markdown__
*	斜体：使用\* 或 \_ 将文本包围：markdown *markdown*  _markdown_
*	同时的黑体和斜体：套用上面的语法 ***markdown***  **_markdown_**

## 链接
內联链接（inline link）：[CNblog](www.cnblog.com)  
引用链接（reference link）：  
		[Search][Google]  
		[Search][Baidu]  
		\[Google\]:www.google.com     
		\[Baidu\]:www.baidu.com   这句和上句应该放在本文最后。  
图片链接：![PicName]( http://octodex.github.com/images/foundingfather_v2.png)
使用引用链接来实现图片链接：  
![PicName][PicUrl] 在这里\[PicUrl\]的链接在本文最后。 

##  
文本的引用：在段落或行前使用符号 >  
>this is a example.  
>this is a example too .  

## 列表
*	无序列表，使用 \* 或 \-
-	两者都行

1.	有序列表
2.	就像这样
3.	...
### 多级列表
*	block1
 *	line1
  *	subline1
  *	...
有序列表和无序列表可以混合使用。  

## 代码的表示
-	一对\`表示行内代码：`hello Markdown`  
-	一对\`\`\`也就是三个\`表示代码块：
	```
    #include <iostream>
	int main(int argc, char const* argv[])
	{
		std::cout << "hello, world!" << std::endl;
		return 0;
	}
	```
-	行前面有四个空格的行也会被认为是代码（但这种方法不是很通用，故最好用上一中方法）：
	```
	#include <iostream>
	int main(int argc, char const* argv[])
	{
		std::cout << "hello, world!" << std::endl;
		return 0;
	}
    ```

## Markdown扩展
*	http://en.wikipedia.org/wiki/Markdown#Syntax_examples
*	http://johnmacfarlane.net/babelmark2/faq.html
*	http://idratherbewriting.com/2013/06/04/exploring-markdown-in-collaborative-authoring-to-publishing-workflows/

[Google]:www.google.com  
[Baidu]:www.baidu.com  
[PicUrl]:http://octodex.github.com/images/founding-father.jpg
