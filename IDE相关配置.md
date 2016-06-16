## Qtcreater pro文件配置（[参考][1]）
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
