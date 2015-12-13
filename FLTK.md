参考：[http://www.cppblog.com/cyantree/archive/2012/05/13/174761.html](http://www.cppblog.com/cyantree/archive/2012/05/13/174761.html)

-	关于FLTK的编译，使用-I指令引入包含文件：gcc -I/usr/.../include...  使用指令-L引入库文件：gcc -L/usr/.../lib...
-	FLTK为了实现静态链接一般将不同的函数放在了不同的库文件中，需要链接那个函数时才会链接，不会链接不需要的部分。
-	在FLTK中不同的控件位于不同的头文件中，所以FLTK中有很多的头文件：FL/Fl\_Window.h  FL/Fl\_Button ...每一个FLTK文件必须包含FL/Fl\_Fl.h
-	在FLTK中除了设置lable可以不调用redraw函数，设置其他的属性之后都需要显式的调用redraw函数来刷新显示。
-	在FLTK中一般控件只保存其label字符串的指针，故lable字符串不能保存在栈中，但可以使用copy_label函数来设置label，这样就不用担心label字符串的保存位置。
-	回调函数的原理：
> 调用回调函数时，我们提供回调函数的的指针和其所需要的参数，这些参数会在调用函数内部被”组装“，例如一个回调函数 void call_back(int a, int b);我们将其函数指针作为参数传给一个函数 `point(void (*fp)(int, int ) )  ` ,在point中使用call_back函数时的形式类似于：`(*fp)(m , n);`或fp(a,b);其中fp中的参数是由point函数提供的。在FLTK中，回到函数的第一个参数是调用回调函数的控件的指针，是默认的。第二个参数是一个void指针，第二个参数可以没有。

-	FLTK 中的每一个控件都只有一个callback函数，故只能对一种动作做出反应。例如button的callback是用于按钮的点击，窗体的callback用于窗体的关闭box（右上角的 X ）
- 	在FLTK中，所以的回调函数均只有两个参数，其中第一个参数已经确定，就是调用回调函数的控件的指针，故其类型是确定的 `Fl_Widget *p_widget` 。第二个参数是一个void 指针`void * `。


控件之间简单通信的方法：
```
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <cstdlib>                   //for exit(0)
using namespace std;

void copy_cb( Fl_Widget* , void* );  //function prototypes
void close_cb( Fl_Widget* , void* );
void make_window();

   
int main() {

   make_window();
   return Fl::run();//让FLTK进入循环等待获得
}


void make_window() {
  
   Fl_Window* win= new Fl_Window(300,200, "Testing 2");
   win->begin();       //begin和end之间的控件会被默认放置在父控件内。
      Fl_Button*  copy = new Fl_Button( 50, 100, 140, 30, "change me");
      Fl_Button* close = new Fl_Button(100, 150, 70, 30, "&Quit");
      Fl_Input*       inp = new Fl_Input(50, 50, 140, 30, "In");             
   win->end();
   copy->callback(  copy_cb, inp );  //userdata is the inp pointer
   close->callback( close_cb );
   win->show();//show中可以有参数，如argv，这样就可以使用控制台参数来动态的设定窗口的显示。
 }


void copy_cb( Fl_Widget* o , void* v) {

   Fl_Button* b=(Fl_Button*)o;
   Fl_Input* i=(Fl_Input*)v;
   b->copy_label(i->value());  //FLTK中的set和get属性使用函数的重载来实现，含参数的函数一般为设置函数（set）而不含参数的函数可以认为是获得属性（get）。
   b->position(x, y);
}


void close_cb( Fl_Widget* o, void*) {

   exit(0);
}
```


控件之间通信的推荐方法：
```
#include <FL/Fl.H> 
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
using namespace std;

//---------------------------------------------------
 
//控件之间通信的一个主要问题在于如何让回调函数获得各控件的指针，
//而存在于一个类中的控件可以使用this关键字来获得对象的指针从而可以很方便的获得各控件的指针。
//如果回调函数直接被定义在类内，那么也可以直接调用类中的成员。
class SimpleWindow : public Fl_Window{
 
   public:
      SimpleWindow(int w, int h, const char* title );
      ~SimpleWindow();
      Fl_Button* copy;
      Fl_Button* quit;
      Fl_Input* inp;
      Fl_Output* out;
    
   private:
      static void cb_copy(Fl_Widget*, void*);  //在C++中，类内的非静态函数的地址是无法获得的，故在这里使用了一对函数来实现类中的回调，其中第一个函数用于实现回调与返回对象的this地址从而实现调用不同对象中的对应函数。
      inline void cb_copy_i();
  
      static void cb_quit(Fl_Widget*, void*);
      inline void cb_quit_i();
};

//----------------------------------------------------

int main (){
  
   SimpleWindow win(300,200,"SimpleWindow");
   return Fl::run();
}

//----------------------------------------------------

SimpleWindow::SimpleWindow(int w, int h, const char* title):Fl_Window(w,h,title){ //父类的初始化，调用父类的构造函数
    
   begin();
      copy = new Fl_Button( 10, 150, 70, 30, "C&opy");//& 的存在会将其后面的字符转化为快捷键。
      copy->callback( cb_copy, this );
     
      quit = new Fl_Button(100, 150, 70, 30, "&Quit");
      quit->callback(cb_quit, this);
   
      inp = new Fl_Input(50, 50, 140, 30, "Input:");
      out = new Fl_Output(50, 100, 140, 30, "Output:");
   end();
   resizable(this);
   show();
}

//----------------------------------------------------

SimpleWindow::~SimpleWindow(){}

//----------------------------------------------------

void SimpleWindow::cb_copy(Fl_Widget* o, void* v) { 
 
   //SimpleWindow* T=(SimpleWindow*)v;
   //T->cb_copy_i();
    
   // or just the one line below
    ((SimpleWindow*)v )->cb_copy_i();
}


void SimpleWindow::cb_copy_i() {

   out->value(inp->value());  
}

//----------------------------------------------------

void SimpleWindow::cb_quit(Fl_Widget* , void* v) {

   ( (SimpleWindow*)v )->cb_quit_i();
}


void SimpleWindow::cb_quit_i() {

    hide();
}

//---------------------------------------------------
```
