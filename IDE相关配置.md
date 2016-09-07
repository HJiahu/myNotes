## Qtcreater pro文件配置（[参考][1]）
### [Qt官方说明][2] [指定平台][3]
```
#这不是一个完整的qt pro文件的配置，下面只是罗列了pro文件中一些语法的用法
HEADERS = mainwindow.h paintwidget.h #变量赋值

include(other.pro)                   #包含其他项目

SOURCES = main.cpp mainwindow.cpp \  #下面两行均是向变量赋值，反斜杠表示下一行依旧为赋值内容
          paintwidget.cpp            #最后一行不能加反斜杠

CONFIG += qt                         #这是对变量值的扩充

QMAKE_CXXFLAGS+=-O2                  #编译指令（开关）
QMAKE_LFLAGS                         #连接器指令
TEMP_SOURCES = $$SOURCES             #两个$$表示取变量值

win32:INCLUDEPATH += "C:/mylibs/extra headers" #指明平台，用于单行
unix:INCLUDEPATH += "/home/user/extra headers"


win32 {                              #在windows系统下有效
    SOURCES += paintwidget_win.cpp
	
	debug {                          #可以嵌套
        HEADERS += debugging.h
    }
}

win32:debug {                        #使用:运算符实现嵌套
    HEADERS += debugging.h
}

win32:DEFINES += QT_DLL              #单行嵌套

!unix {                             #在unix/linux系统下无效
    SOURCES -= paintwidget_win.cpp
}

win32|macx {                         #同时在windows和Max下有效
    HEADERS += debugging.h
}         

#下面的语句通过是否使用变量来实现编译控制
CONFIG += opengl
opengl {                            
    TARGET = application-gl          #因为使用了opengl变量，故使用这行编译命令
} else {
    TARGET = application
}

win32:xml {
    message(Building for Windows)
    SOURCES += xmlhandler_win.cpp
} else:xml {
    SOURCES += xmlhandler.cpp
} else {
    message("Unknown configuration")
}


```
*    `#` ：注释 
*    `TEMPLATE`：告诉qmake为这个应用程序生成哪种makefile
    * `app`：应用程序型、 `lib`：库、 `vcapp`：vs项目文件、 `vclib`：vs库文件、 `subdirs`：特殊
*    `DESTDIR += ../bin`：指定生成的应用程序放置的目录
*    `TARGET = pksystem`：指定生成的应用程序名
*    `CONFIG += [qt] [warn_on] [release] [debug]`：其中qt表示使用qt连编、warn_on表示将编译器设置为输出警告信息...
*    `OBJECTS_DIR += ../tmp`：指定目标文件(obj)的存放目录
*    `DEPENDPATH += . forms include qrc sources`：程序编译时依赖的相关路径
*    `INCLUDEPATH += .`：头文件包含路径
*    `HEADERS += include/painter.h`：工程中包含的头文件
*    `SOURCES += sources/main.cpp sources/painter.cpp`：工程中包含的源文件
*    `LIBS += -L folderPath`：引入的lib文件的路径  -L：引入路径
    *    `Release:LIBS += -L folderPath`：release 版引入的lib文件路径
    *    `Debug:LIBS += -L folderPath`：Debug 版引入的lib 文件路径
*    `DEFINES += XX_XX_XXX`：定义编译选项
*    其他选项见[参考][1]。


















[1]:http://blog.csdn.net/steven6977/article/details/9124539
[2]:http://doc.qt.io/qt-5.7/qmake-project-files.html
[3]:http://doc.qt.io/qt-5.7/qmake-language.html#scopes
