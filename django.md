### 安装django
-	安装pip :`python setup.py install`
-	将python根目录下的script文件夹写入环境变量
-	在终端：`pip install django`

### 在windows服务器中搭建django环境
-	首先在服务中安装django
-	安装Apache，[参考](http://www.cnblogs.com/fnng/p/4119712.html)  
-	安装mod_wsgi，[下载地址](http://www.lfd.uci.edu/~gohlke/pythonlibs/#mod_wsgi)
	-	注意下载的文件的后缀为whl，将后缀名改为zip解压。解压之后将得到一个mod_wsgi.so 文件，将其拷贝到Apache24\modules\ 目录下。
### 一些问题
-	使用`python manage.py check`查错，例如：
-	如果出现`Segmentation fault`错误，执行`python manage.py check`，解决错误。

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
-	为了在工程中激活应用，需要在工程文件中的settings.py中的INSTALLED_APPS中添加应用的名称：`polls.apps.PollsConfig`

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
-	polls/urls.py:

```
from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
]
```
-	polls/views.py：

```
from django.http import HttpResponse

def index(request):
    return HttpResponse("Hello, world. You're at the polls index.")
```
#### 启动server
-	`python manage.py runserver`#默认端口号为：8080。使用localhost:8080或127.0.0.1:8080访问当前网站
-	` python manage.py runserver 8080`#修改默认端口
-	`python manage.py runserver 0.0.0.0:8000`

### 数据处理
-	django默认使用SQLite作为数据库，若想使用其他数据可需要安装其他的数据库接口并在setting中做对应的设置。使用默认的SQLite不需要做任何设置。
-	在创建django工程时系统在settings.py中的INSTALLED_APPS中添加了一些额外的应用，这些应用是需要数据库支持的，故应先创建这些应用所需的数据库：`python manage.py migrate `
-	定义自己的数据库：
	-	编辑polls/models.py：

```
class Question(models.Model):
	question_text = models.CharField(max_length = 200)
	pub_date = models.DateTimeField('date published')
	#添加一些方法
	def was_published_recently(self):
        return self.pub_date >= timezone.now() - datetime.timedelta(days=1)


class Choice(models.Model):
	question = models.ForeignKey(Question,on_delete = models.CASCADE)
	choice_text = models.CharField(max_length = 200)
	votes = models.IntegerField(default = 0)
```
-	执行指令：`python manage.py makemigrations polls `告诉django你对数据库做了一些更改，并想将更改写入数据库。执行这条指令之后会生成一个文档：polls/migrations/0001_initial.py，该文档描述了django对数据库的对应操作（使用python语言描述）。
-	执行指令：` python manage.py sqlmigrate polls 0001`使django生成对应的sql语句（生成的语句会因为数据库的不同而改变）。这条语句不是必须的。
-	执行指令：` python manage.py migrate `执行上面生成的sql语句，实现对数据库的更改。
-	**注意**：数据库中的表会自动的加上前缀：`polls_`，而且所有的表名自动转化为小写。但我们在django中使用表时依旧使用models中定义的名称。
	-	系统会自动为第一列添加主键属性，对于外键，系统会自动的添加后缀`_id`
-	通过python与django项目交互：`python manage.py shell`
-	导入数据库：`from polls.models import Question, Choice`
 
```
>>> from polls.models import Question, Choice   # Import the model classes we just wrote.
>>> Question.objects.all() #没有数据
[]
>>> from django.utils import timezone
>>> q = Question(question_text="What's new?", pub_date=timezone.now()) #在Question中创建一条心的记录
>>> q.save()  #向数据库中保存此条记录。
>>> q.id #返回新记录的id值
1
>>> q.question_text
"What's new?"
>>> q.pub_date
datetime.datetime(2012, 2, 26, 13, 0, 0, 775217, tzinfo=<UTC>)
>>> q.question_text = "What's up?"  #改变值，一定要再调用save()保存到数据库中。
>>> q.save()   ################################
>>> Question.objects.all()  #显示所有记录
[<Question: Question object>]
```
### 用户管理
-	创建超级用户：` python manage.py createsuperuser`
