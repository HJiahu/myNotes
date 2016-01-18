
# 一些快捷键和指令：
Ctrl-w  h j k l    在splits间切换
zr  open all folds
zm close all folds
[z move to start of open fold.
]z move to end of open fold.
:MkdToHtml   
##  
段内移动与操作： 2015-08-08 16：39:41
w：				   跳至下一个单词的第一个字母。
w：				   跳过一串没有空白的字符串，光标停留在下一个字符串的第一个字符处。
c2w：			   更改两个单词。
e：				   和w类似，只是将光标停留在单词的最后一个字符上。
b和ge：			   反向的跳转一个单词，与w他e反向。
xp：			   交换两个字母，剪切当前字符，p将剪切板内的字符粘贴在光标之后。
f和t：			   跳转到指定的符号处。
0和^：			   跳转到段的起始，
$：	   			   跳转到段的结尾。
%：				   匹配括号。
H  L  M，
X = dh
D = d$
. repeat a change ,find is not a change so we can not use . to repaet find .not a command line change .			

书签：ma
返回标签处：'a 是跳转到标签所处打行打首位。\`是跳转到定义标签处。

vim的对象操作：vim打指令可以直接操作一个对象，对象可以是单词、可以是句子\
				daw：表示delete a word vim会删除光标位置处打单词。
				cis：change in sentence
				vas：选定一个句子。
## 				
vim列的操作：
复制一列块数据并将其粘贴于某一列之后，首先使用ctrl-v进入可视模式复制选定的块。再使用ctrl-v模式选定一列，注意这里是选定一列，然后使用p将刚复制打块粘贴在这个列之后。

## 
vim tab 的操作：
	在打开vim时使用指令-p可以将多个文档放在不同的标签中。vim -p txt1  txt2...
一些指令：
	：tabedit {file}   edit specified file in a new tab
	：tabfind {file}   open a new tab with filename given, searching the 'path' to find it
	：tabclose         close current tab
	：tabclose {i}     close i-th tab
	：tabonly          close all other tabs (show only the current tab)
	：tab ball         show each buffer in a tab (up to 'tabpagemax' tabs)
	：tab help         open a new help window in its own tab page
	：tab drop {file}  open {file} in a new tab, or jump to a window/tab containing the file if there is one
	：tab split        copy the current window to a new tab of its own
	：tabs         list all tabs including their displayed windows
	：tabm 0       move current tab to first
	：tabm         move current tab to last
	：tabm {i}     move current tab to position i+1
	：tabn         go to next tab
	：tabp         go to previous tab
	：tabfirst     go to first tab
	：tablast      go to last tab
	Ctrl-PgDn     go to next tab
	Ctrl-PgUp     go to previous tab

##
nerdtree快捷键：
o：open the file and change cursor position  to the file
go：open the file and stay cursor in nerdtree
s：open the file in vsplit 
gs：like g in go 
u：Move the tree root up one directory
U：Same as 'u' except the old root node is left open
r：recursively refresh the current directory
r：Recursively refresh the current root
q：Close the NERDTree window
A：Zoom (maximize/minimize) the NERDTree window|NERDTree-A|
X：Recursively close all children of the current node|NERDTree-X|
P：Jump to the root node|NERDTree-P|
p：Jump to current nodes parent|NERDTree-p|


##  
shotcut for surrend
ys takes a valid Vim motion or text object as the first object, and wraps
it using the second argument as with |cs|. 
  Hello w*orld!             ysiw)       Hello (world)!
     ysiw  ys a word ;          ysiW ys in WORD ;     ysap ys a paragraph
	 ysas ys a sentence ;
As a special case, yss operates on the current line, ignoring leading
In visual mode, a simple "S" with an argument wraps the selection.

  Old text                  Command     New text ~
  "Hello *world!"           ds"         Hello world!
  [123+4*56]/2              cs])        (123+456)/2
  "Look ma, I'm *HTML!"     cs"<q>      <q>Look ma, I'm HTML!</q>
  if *x>3 {                 ysW(        if ( x>3 ) {
  my $str = *whee!;         vllllS'     my $str = 'whee!';
  Hello w*orld!             ysiw)       Hello (world)!
  
## 



# 在windows下使用vim
最主要的就是解决lua和clang的问题。
1.	下载支持lua和其他扩展的[vim](https://tuxproject.de/projects/vim/)。
2.	解决lua
> 下载[lua53.dll](http://luabinaries.sourceforge.net/download.html)并将其放在与gvim.exe相同的文件夹下。

3.	解决clang           
下载[clang_for_windows](http://llvm.org/releases/download.html)。安装下载的软件，在_VIMRC中添加下面两行: ``let g:clang_use_library=1 let g:clang_library_path="C:\\Program Files\\LLVM\\bin`
4.	解决GCC
下载GCC，并将对应的文件夹写入环境变量。            
复制一份mingw32-make.exe到相同的文件夹下，并且将其名称给位make.exe。

删除文章中的空行
:g/^s*$/d
简单解释一下：
g ：全区命令
/ ：分隔符
^s*$ ：匹配空行，其中^表示行首，s表示空字符，包括空格和制表符，*重复0到n个前面的字符，$表示行尾。连起来就是匹配只有空字符的行，也就是空行。
/d ：删除该行
