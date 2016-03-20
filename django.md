### 安装django
-	安装pip 
-	将python根目录下的script文件夹写入环境变量
-	在终端：`pip install django`

### 一些问题
-	使用`python manage.py check`差错，例如：
-	如果出现`Segmentation fault`错误，执行`python manage.py check`，解决先关错误。

### django基础理念
-	 一个视图就是Python的一个函数。一般将视图文件的名称定为：veiws.py
-	 可以在settings.py中改变时区（TIME_ZONE）。

### 一般流程
#### 创建工程与应用
-	工程与应用的区别：
	-	应用：apps用于完成某些任务
	-	工程是配置和apps的集合。
-	工程的创建：`django-admin startproject mysite `#在当前目录下创建一个名为mysite 的站点，注意名称不能和系统中的名称重名（不能取名test）

```
mysite/        #根目录
    manage.py  
    mysite/         
        __init__.py    #这个文件一般为空，是为了让python将当前文件夹当做一个包看待
        settings.py
        urls.py
        wsgi.py
```
-	创建一个应用：`python manage.py startapp polls`#应用名为polls
-	为了在工程中激活应用，需要在工程文件中的settings.py中的INSTALLED_APPS中添加应用的名称：` d`

```
polls/    #与manage.py相同目录，polls有自己的配置文件
    __init__.py
    admin.py
    apps.py
    migrations/  #用于存放有关数据库的数据，如与数据库交互的sql语句
        __init__.py
    models.py
    tests.py
	urls.py   #此文档不是自动创建的，需要手动添加。每一个app都可以有自己的URLconf，在全局urls.py中使用include可以使用此urls.py
    views.py
```
-	在工程中添加app：编辑mysite/urls.py 
-	**注意下面include的使用。**使用include可以以开发插件的形式来开发django应用，这些插件是独立的。
-	urlpatterns中的url()中可以有四个参数，其中两个是必须的，两个是可选的。

```
from django.conf.urls import include, url
from django.contrib import admin

urlpatterns = [
    url(r'^polls/', include('polls.urls')),#这里的include表示将使用polls的urls.py 系统将截取url中...polls/后的字符传递给poll.urls
    url(r'^admin/', admin.site.urls),#urls中的第一个参数时url匹配正则表达式，第二个参数是将要调用的视图（对应的函数） 
]
```
#### 启动server
-	`python manage.py runserver`#默认端口号为：8080。使用localhost:8080或127.0.0.1:8080访问当前网站
-	` python manage.py runserver 8080`#修改默认端口
-	`python manage.py runserver 0.0.0.0:8000`

### 数据处理
-	django默认使用SQLite作为数据库，若想使用其他数据可需要安装其他的数据库接口。
-	在创建django工程时系统在settings.py中的INSTALLED_APPS中添加了一些额外的应用，这些应用是需要数据库支持的，故应先创建这些应用所需的数据库：`python manage.py migrate `
