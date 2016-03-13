本文摘自：HTML5与CSS3基础教程；
-	目录：    
	-	[web环境](#environment)
	-	[HTML5 CSS3](#html)	
	-	[JavaScript](#js)
	-	[PHP](#php)

## web环境 [\[Index\]](#Index) <span id="environment"/>      
-	nginx html目录：/usr/share/html
## HTML5 CSS3   [\[Index\]](#Index) <span id="html"/>      
### HTML5的一般概念
-	渐进增强（progressive  enhancement）的理念能帮助你构建具有普适性的网站。不必要求网站对所有人来说体验都是一样的，关键是网站的内容是可访问的`<body>`开始标签以上的内容都是为浏览器和搜索引擎准备的。在每个HTML 页面的开头都有一些主要用于浏览器和搜索引擎（如Bing、Duck Duck Go、Google、Yahoo 等）的信息。浏览器不会将这些信息呈现给访问者。
-	无障碍访问：内容对所有用户可用，不论其能力如何。万维网的力量在于其普适性。让包括残障人士在内的每个人都能访问万维网，
-	HTML 元素描述的是内容是什么（语义），而非看起来是什么样。CSS（从第7 章开始讲解）才控制内容的外观（如字体、颜色、阴影等）。
-	元素由开始标签、内容和结束标签组成。
-	空元素（empty element或void element），既不包含文本也不包含其他元素。
-	属性的顺序并不重要。不同的属性–值对之间都用空格隔开。有的属性只接受特定的值。例如，只能将link 元素里的media 属性设为all、screen、print 等值中的一个。
-	`<input type="email" name="emailaddr" required />` 布尔属性required 代表用户必须填写该输入框。布尔属性不需要属性值，如果一定要加上属性值，则写作required="required"。
-	`&eacute;`（表示é）、`&copy;`（表示©）等。
-	不要在文件名和文件夹名中使用空格分隔单词。应该使用短横线，例如company-history.html 和my-favorite-movies.html。有的网站使用下划线（_），我们不推荐这种做法，因为短横线是搜索引擎更容易接受的方式。
-	***根相对URL***：根相对URL 就是`/img/family/vacation.jpg`（假定img 文件夹位于网站的根文件夹，这也是惯常的用法，对于asp.net而言这种方式无效）。
-	出于性能考虑，多数时候在页面底部`</body>`标签结束前加载JavaScript 是更好的选择。
-	除了title，其他head 里的内容对页面访问者来说都是不可见的。
-	WAI-ARIA（Web Accessibility  Initiative’s Accessible Rich Internet Applications，无障碍网页倡议– 无障碍的富互联网应用，也简称ARIA）是一种技术规范。无障碍访问的意义是让所有的访问者都能获取网站的内容。
-	地标角色：即便不使用ARIA 地标角色，页面看起来也没有任何差别，但是使用它们可以提升使用辅助设备的用户的体验不要在页面上过多地使用地标角色。过多的地标角色会让屏幕阅读器用户感到累赘，从而降低地标的作用，影响整体体验。
```
role = "banner"
role = "navigation"
role = "main"
role = "contentinfo"
role = "complementary"
```

### 常用HTML5元素
-	`<a href="...">...</a>`：创建指向另一个网页的链接。rel="external"属性表示这个链接是指向其他网站的。href 指hypertext reference。可以使用a元素创建锚点和链接锚：`<a href="#idname">...</a>` 其中当前页面中有一个id的值为idname。a元素可以用于其他元素：图片、段落、视频、右邮件地址、电话：
	-	`<a href="mailto : someone@somedomain.com"> someone@somedomain.com</a>`;     
	-	`<a href = "tel:+18001234567">1(800) 123-4567</a>`。
-	`<em>` ：语义为 强调。不应该为了让文字变为斜体就使用em 或cite，添加样式是CSS 的事情。一定要在符合内容语义的情况下使用该元素，而不是为了减小字号而使用。
-	`<b>`：HTML5 将b 重新定义为：b 元素表示出于实用目的提醒读者注意的一块文字，不传达任何额外的重要性，
-	`<i>`：HTML5 将i 重新定义为：i 元素表示一块不同于其他文字的文字，具有不同的语态或语气，或其他不同于常规之处，用于如分类名称、技术术语、外语里的惯用语、翻译的散文、西方文字中的船舶名称等。
-	`<small>`：small的语义并不是指字体比较小，而是指内容类似于解释，注释（side comment），等辅助内容。
-	`<strong>` 元素表示内容的重要性，而em 则表示内容的着重点。
-	`<title>`：head中的title会显示在网页标题栏处。
-	`<header>`：页面中有一块包含一组介绍性或导航性内容的区域。`<header role="banner">`，可选的role="banner"并不适用于所有的页眉，它显式地指出该页眉为页面级的页眉。不能在header 里嵌套footer 元素或另一个header，也不能在footer 或address元素里嵌套header。
-	`<h1>,h2,h3,h4,h5,h6`：分级标题。
-	`<nav>`：`<nav role="navigation">`   导航。HTML5 不允许将nav 嵌套在address元素中。链接和导航是两种不同的语义。
-	`<main>`：页面的主要区域。一个页面只有一个部分代表其主要内容。可以将这样的内容包在main 元素中。最好在main 开始标签中加上role="main"，role="main" 可以帮助屏幕阅读器定位页面的主要区域。main 元素是HTML5 新添加的元素，在一个页面里仅使用一次。不能将main 放置在article、aside、footer、header 或nav 元素中。
-	`<article>`：HTML5 的新元素。article 元素表示文档、页面、应用或网站中一个独立的容器，原则上是可独立分配或可再用的，就像聚合内容中的各部分。
-	`<section>`：文档或应用的一个一般的区块。在这里，section是具有***相似主题***的一组内容。如果只是出于添加样式的原因要对内容添加一个容器，应使用div 而不是section。section 不能作为添加样式的通用容器。
-	`<aside>`：附注栏。引述、侧栏、指向相关文章的一组链接（通常针对新闻网站）、广告、nav 元素组（如博客的友情链接），Twitter 源、相关产品列表（通常针对电子商务网站），等等。在HTML 中，应该将附注栏内容放在main 的内容之后。HTML5 不允许将aside 嵌套在address元素内。aside 可以嵌套在主要内容里面，也可以位于主要内容外面。
-	`<cite>`：使用cite 元素可以指明对某内容源的引用或参考，例如，戏剧、脚本或图书的标题，歌曲、电影、照片或雕塑的名称，演唱会或音乐会，规范、报纸或法律文件等。`<cite>...</cite>`。
-	`<del>`：表示删除内容，浏览器中的表示：在文字的中间画一条线，表示删除。
-	`<ins>`：表示新插入的内容。
-	`<code>`：表示代码，在code中使用 `&lt;`和`&gt;`表示`<`和`>`：
```
<pre>
 <code>
    #include&lt;stdio.h&gt;
    int main()
	{
    	printf("Hello word !");
    }
 </code>
</pre>
```
-	`<pre>`：使用预格式化的文本。pre只是保留了文本中固有的空格和换行，但有些符号会被处理例如：`<`和`>`。一定要对页面进行验证，检查是否在pre 中嵌套了HTML 元素。
-	`<mark>`：突出显示文本。试着将mark 想象成荧光笔的语义化对照物。
-	`<blockquote>`：表示单独存在的引述（通常更长，但也可能不是）：
```
<blockquote cite="http://www.marktwainbooks.edu/the-adventures-of-huckleberry-finn/">
   <p>We said there warn't no home like a raft, after all. Other places do seem so cramped up and smothery, but a raft don't. You feel mighty free and easy and comfortable on a raft.</p>
</blockquote>
```
-	`<q>`：元素则用于短的引述，如句子里面的引述。浏览器应对q 元素中的文本自动加上特定语言的引号。blockquote 和q 元素可以嵌套。
```
<q>Have you read Barbara Kingsolver's <cite>High Tide in Tucson</cite>? It's inspiring.</q>
```
-	`<footer>`：页脚。当footer最靠近的祖先是body时，	其才是整个页面的页脚。只能对页面级的footer 使用role="contentinfo"，且一个页面只能使用一次。
-	`<img src="..." / alt="..." width="" height="">`：显示图片，当无法显示图片时，alt中的文字会显示在图片应显示处。***如果图像是页面设计的一部分，而不是内容的一部分，则应使用CSS background-image 属性引入该图像，而不是使用img 标记。***
-	`<figure>`：图可以是图表、照片、图形、插图、代码片段，以及其他类似的独立内容。
-	`<figcaption>`：figure的标题，出现在figure内容的开头或结尾处不管figure 里有多少内容，只允许有一个figcaption。
```
<figure>
   <figcaption><b>Figure  3:</b></figcaption>
   <img src="..."/>
   ...
</figure>
```
-	`<time>`：我们可以使用time 元素标记时间、日期或时间段，这是HTML5 新增的元素。`<time>16:20</time>`，`<time datetime="2013-11-20T18:30:00"> `。对于时间元素而言，在不提供datetime属性时，time中的内容必须是机器可读的（即要满足一定的格式）。当time元素中含有datetime属性时，其内容不受限制。
-	`<abbr>`：可以使用abbr 元素标记缩写词并解释其含义：`<abbr title="National Football League">NFL</abbr>`
-	`<dfn>`：可以使用dfn元素对其作语义上的区分。仅用dfn包围要定义的术语，而不是包围定义：`<dfn>pleonasm</dfn> means "a redundant word or expression"  `dfn 元素及其定义必须挨在一起，否则便是错误的用法。 
-	`<sub>和<sup>`：下标和上标。被包含的文字会成为上下标。
-	`<address>`：有关作者、相关人士或组织的联系信息，通常位于页面底部或相关部分内。
```
<address>
   Have a question or comment about the site? <a href="site-feedback.html"> Contact our web team</a>.
</address>
```
-	`<div>`：一个完全没有任何语义含义的容器。
-	`<br/>`：换行。将br作为最后的选择，样式最好都留给CSS来完成。
-	`<span>`：同div一样，span元素是没有任何语义的。不同的是，span 只适合包围字词或短语内容，而div 适合包含块级内容。`<span lang="es">La Casa Milà</span>`
-	`<u> <wbr> <ruby> <rp> <rt> <bdi> <bdo> <meter> <progress>`：其他类型的元素，如文字排版的方向（从左到右或从右到左），进度条...

### HTML5元素的属性
-	id：`id = "name"`，在一个html文件中，id的值必须是唯一的。id值几乎可以是任何字符，只要不以数字开头且不包含空格。
-	class：一个元素可以是多种类别：`class = "classname1 classname2 ..."`，推荐使用类别来为元素添加样式。在class 和id 名称中，通常使用短横线分隔多个单词，例如class="footer-page"。
-	title：为网站上任何部分加上提示标签（注意与title元素的区别）。
-	cite：可以对blockquote 和q 使用可选的cite 属性，提供引述内容来源的URL。

### CSS
-	CSS每条规则都由两个部分组成：选择器，声明块。
-	CSS的注释：`/*...*/`
-	
## JavaScript   [\[Index\]](#Index) <span id="js"/>      
### 问题
-	为例减少对性能的影响，应尽量减少网页中的标记并减少对DOM的访问。还可以对js脚本进行压缩：去除脚本中多余的字符，如注释与多余的空格（现成的工具可用。）
-	JavaScript代码有两种方式放入HTML中：
	1. 将JavaScript代码放在head中的script之间：`<head><script> ...</script></head>`
	2. 第二种方式是直接引用js文件：`<script src="..."></script> `。
	3. 最好的办法是将`<script></script>`标签放在HTML文档最后，`</body>`标签之前，这样可以加快页面的载入。
	4. 注意JavaScript是对DOM进行操作的，故当DOM没有建立前调用JavaScript将得不到想要的结果（window.onload = scriptNmae;）。
-	JavaScript的注释有三种形式：
	1. 类似于C的单行注释：//
	2. 类似于C的多行注释：`/* ... */`
	3. 类似于HTML：`<!--`  在JavaScript中可以不用 `->`结尾 。（不推荐使用。）
-	在JavaScript中内建数据类型使用的是pass-by-value（js中只有三种内建数据：数字，布尔，串。数组是对象）；
-	为了实现渐进增强，一般要将JavaScript从html中分离：

```
<!DOCTYPE html>
<html lang="en">
<head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8" />
  <title>Example</title>
<script>
window.onload = function() {
  if (!document.getElementsByTagName) return false;
  var lnks = document.getElementsByTagName("a");
  for (var i=0; i<lnks.length; i++) {
    if (lnks[i].getAttribute("class") == "popup") {
      lnks[i].onclick = function() {
        popUp(this.getAttribute("href"));
        return false;
      }
    }
  }
}

function popUp(winURL) {
  window.open(winURL,"popup","width=320,height=480");
}

</script>
</head>
<body>
<a href="http://www.example.com/" class="popup">Example</a>
</body>
</html>

```

### JavaScript 变量
-	JavaScript中的单引号与双引号之间没有区别，但是在引号的嵌套中需要注意：双引号中嵌套的引号必须是单引号。
-	JavaScript中的基本类型为：数字、布尔、串。（***数组是特殊的内建对象，不是基本数据类型***）
-	JavaScript是弱类型语言。
-	JavaScript是大小写敏感的。
-	JavaScript中的变量可以声明也可以不声明。若程序员未声明变量（默认全局）则系统会在变量赋值时自动的声明。当然了，可以显式的声明变量：
	-	`var age;`
	-	`var mood ,age;`
	-	`var mood = "happy" , age = 33;`
-	***不使用var声明而直接使用的变量会成为全局变量***。
-	JavaScript中的字符串可以使用单引号或双引号。注意转义字符 \ 。
-	使用函数splice()删除数组中的一个元素并将使后面的元素的index减一。
### 对象
-	this对象：this表示当前的元素对象（例如对于a元素：this.href  ）。
-	JavaScript中new的用处：new用于创建一个类的实例，不使用new就相当于执行了一个函数，具体效果依靠函数的返回值。
-	数组是JavaScript中特殊的内建对像（可以认为数组是对象的子类）。
-	传统数组：
	-	`var beatls = Array(4);`//4个元素
	-	`var beatls = Array();`//元素个数未知
	-	`var beatls = [];`//元素个数未知
	-	`var beatls = Array("John","Paul",3.14,"Tom","Ringo");`//数组中的元素类型不一定要一样
	-	`var beatls = ["John","Paul",3.14,"Tom","Ringo"]`
	-	`beatls[0] = "John"; beatls[3] = "Paul"; `
	-	***数组中可以包含其他的数组，而且子数组的维度可以不一样。***
-	关联数组：
	-	关联数组中的index可以是字符而不仅仅是数字。
	-	***所谓的关联数组在JavaScript中其实是向Array对象中添加属性。***故一般不推荐使用这种方式，***为了实现关联数组的形式，可以使用对象（object()）。***
```
var lennon = Array();//关联数组是向Array对象中添加属性。这种方式不推荐
lennon["name"] = "John";
lennon["years"] = 1940;
lennon["leaving"] = false;
//使用对象来实现关联数组
var lennon = object();//推荐的方式，对象和数组对元素的读取语法不同。
lennon.name = "John";
lennon.years = 1940;
lennon.leaving = false;
```
-	对象的创建方式：
	1. `var len = object();`
	2. `var len = {propertyName:value , propertyName:value ...};`//***对象中的元素用逗号分隔***。
-	对象和数组的混合使用：（对象同样可以使用类似数组的形式对元素进行访问，objectNmae[propertyName]）
```
var beatls = Array();
beatls[0] = lennon;
//获得值的方式
beatls[0].name = ...;
//beatls和 lennon 均为对象
var beatls = {};
beatls.vocalist = lennon;
beatls.vacation.name = ...;
```
-	向对象中添加属性的方式很简单：直接为新属性赋值即可创建一个新的属性：
```
lennon.age = 99;//lennon中以前是没有age这个属性的，直接对其进行赋值即可创建属性age。
```
### 操作
-	运算符：
	-	`"10" + 20 ;` //结果为 "1020"
	-	`3 + "4"`;   //结果为"34"，数字和字符串的混合，最终的结果都是字符串。
	-	`10 + 20 `;   //结果为30
-	JS中的“range for”：`for(val in container){ ... };`//若container是对象，则val为对象中属性的名字。val的次序与属性的位置没有直接的关系。
-	JavaScript中的严格比较：`===` 同时比较值与类型，变量只有在完全相同时才会返回true。
```
false == "";//将返回true
false === "" ;//将返回false，因为false和""的类型不同。
```
-	JavaScript中的函数名可以赋予另一个变量，这样这个变量也将代表原函数。


### JavaScript内建属性与函数
-	`Math.random();`：生成一个0~1的随机数
-	`element.childNodes`：返回一个数组，包含当前元素的所有子元素。（length属性，数组的长度）
-	`var body_element = document.getElementsByTagName("body")[0];` ：通过元素名（body ul a img ...）获得对象***数组***，因为一个文档中不一定只有一个a元素（也不一定只有一个img元素），故返回值是数组。
-	`window.open(url , "popup" , "width= 320 , height=480");`弹出一个窗口，url为窗口的链接，第二个参数为窗口的名称，第三个参数完成对窗口的设定。

### 运行
-	JavaScript没有编译单元的说法，故在一个文件中的JavaScript语句（包括对其他js文件的引用）共享一个全局，故要注意名字冲突的问题。
-	`window.onload = countBodyChildren; `window.onload是在页面加载之后执行的一个js函数。


## PHP  [\[Index\]](#Index) <span id="php"/>      
-	PHP 文件的后缀是 ".php"。
-	PHP 脚本可放置于文档中的任何位置。PHP 脚本以` <?php `开头，以` ?>` 结尾。
-	PHP中的单引号与双引号的区别在于：单引号中的数据不会被处理，双引号中的数据会被解析。
-	PHP 支持三种注释
```
<?php
// 这是单行注释
# 这也是单行注释
/*
这是多行注释块
它横跨了
多行
*/
```
-	在 PHP 中，所有用户定义的函数、类和关键词（例如 if、else、echo 等等）都对大小写不敏感，故Echo、echo、ecHo...表达相同的意思。但在 PHP 中，所有变量都对大小写敏感，$color、$COLOR、$coLOr...表达不同的意思。

### 变量
-	PHP中的变量都由 `$` 开头。PHP对变量的大小写敏感。
-	变量会在首次为其赋值时被创建：`$x = 5;`
-	可变变量：
-	定义常量：`define('MONEY' , 100);`使用时不加 $ ：`echo MONEY`。
-	PHP访问变量的方式：（假设变量在表单中的属性name 为 name-value：`<input type="text" name = "name-value"）`
	-	$name-value  //要使用这种方式要先设置 `register_globals`为 on，不推荐这种方式
	-	`$_POST['name-value']`  //推荐这种方式，如果method为get则将POST改为GET。
	-	`$HTTP_POST_VARS['name-value']`  //不推荐使用
-	PHP是弱类型语言，但其支持基本的数据类型：int,float(double),string,bool,array,object。而且PHP中可以对数据进行类型的转化：`$total = (float)tatal_1`
-	PHP 有四种不同的变量作用域：
	-	local（局部）//与C类似
	-	global（全局）//与C相差较大（在PHP中，在函数内部是无法直接使用全局变量的，这是与C差距差距十分明显的地方。）
	-	超全局变量：它们在一个脚本的全部作用域中都可用，无需 global 关键字（如：$GLOBALS,_POST,_GET...）。常量是元一种超全局变量。
	-	static（静态）//与C类似

-	函数之外声明的变量拥有 Global 作用域，***只能在函数以外进行访问***。函数内部声明的变量拥有 LOCAL 作用域，只能在函数内部进行访问。在函数内部访问全局变量的方式有两种：
	1.	在函数内部使用关键字global再次对全局变量进行声明，而且名字要与全局变量名完全一致。
	2.	php中的全局变量保存在名为$GLOBALS[index]的数组中，故可以使用这样的语法访问全局变量：`$GLOBAL['val_name']`         

```
<?php
$x=5;
$y=10;

function myTest() {
	global $x;
	global $y;
	$GLOBALS['y']=$GLOBALS['x']+$GLOBALS['y'];
} 

myTest();
echo $y; // 输出 15
?>
```
-	PHP 逻辑：逻辑是 true 或 false。
-	PHP 数组：
```
<?php 
$cars=array("Volvo","BMW","SAAB");
var_dump($cars);//var_dump() 会返回变量的数据类型和值
?>
```
-	PHP对象：
```
<?php
class Car
{
  var $color;
  function Car($color="green") {
    $this->color = $color;
  }
  function what_color() {
    return $this->color;
  }
}
?>
```
-	PHP 常量：常量名称前面没有 $ 符号。与变量不同，常量贯穿整个脚本是自动全局的。
```
<?php
//php使用define定义常亮，define含有3个参数，
//第一参数为变量名，第二个参数为变脸的值，
//第三个参数表示变量名是否对大小写敏感，默认为false
define("GREETING", "Welcome to W3School.com.cn!");
echo GREETING;
?>
```
### PHP运算符
-	PHP的特殊运算符：
	-	串连接运算符 `.` (一个点)。
	-	完全相等：===  （PHP是动态语言，但其内部实现也是有类型之分的 == 表示值相等，=== 表示类型也一样）
	-	`!=`和`<>` 都表示不等，一般指值不同。
	-	`!==` 只要不是 === 就是 `!==`
	-	引用运算符  `&` 与C++中的引用的概念是相同的。
	-	错误抑制操作符：@ ，例如：`@(4/0)`，代码将抑制除零警告。
	-	执行操作符：\` \`(一对反向单引号)，引号中的命令会被当做服务器端的命令行来执行，其返回值为命令的返回值。
	-	类型操作符：`instanceof` ，`$objectNmae instanceof sampleClass`判断objectNmae是不是sampleClass这个类的对象。
	-	delcare ,控制后面的代码的运行规则。
-	if...elseif...else ...
-	foreach($array as $value)...//PHP的foreach和特别，元素位置和其他语言完全相反。
-	PHP中有类似于python的控制结构语法：

```
if($a == 0) :
	echo ...;
	exit;
endif;
```
-	PHP中创建数组：`$cars=array("Volvo","BMW","SAAB");`

```
<?php
$cars=array("Volvo","BMW","SAAB");
echo count($cars);    //返回数组的长度
echo "I like " . $cars[0] . ", " . $cars[1] . " and " . $cars[2] . ".";
?>
```
-	PHP关联数组（index不是整数，而是字符串）：

```
$age=array("Peter"=>"35","Ben"=>"37","Joe"=>"43");
//或
$age['Peter']="35";
$age['Ben']="37";
$age['Joe']="43";

echo "Peter is " . $age['Peter'] . " years old.";
//使用foreach遍历关联数组
foreach($age as $x=>$x_value) {//对于 "peter"=>"35" x对应peter，x_value对应 35
   echo "Key=" . $x . ", Value=" . $x_value;
   echo "<br>";
}
```

### 函数
-	function fun_name(){ }
```
function sum($x,$y) {
  $z=$x+$y;
  return $z;//直接返回，PHP是动态语言
}
```
-	数组的排序函数
	-	sort() - 以升序对数组排序
	-	rsort() - 以降序对数组排序
	-	asort() - 根据值，以升序对关联数组进行排序
	-	ksort() - 根据键，以升序对关联数组进行排序
	-	arsort() - 根据值，以降序对关联数组进行排序
	-	krsort() - 根据键，以降序对关联数组进行排序
