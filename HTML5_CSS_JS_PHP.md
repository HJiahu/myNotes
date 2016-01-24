本文摘自：HTML5与CSS3基础教程；

### HTML5的一般概念
-	渐进增强（progressive  enhancement）的理念能帮助你构建具有普适性的网站。不必要求网站对所有人来说体验都是一样的，关键是网站的内容是可访问的`<body>`开始标签以上的内容都是为浏览器和搜索引擎准备的。
-	无障碍访问：内容对所有用户可用，不论其能力如何。万维网的力量在于其普适性。让包括残障人士在内的每个人都能访问万维网，
-	在每个HTML 页面的开头都有一些主要用于浏览器和搜索引擎（如Bing、Duck Duck Go、Google、Yahoo 等）的信息。浏览器不会将这些信息呈现给访问者。
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

