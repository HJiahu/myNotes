### 常用指令
-	安装django（python>=3.5.1）：`pip install django`
-	创建project：` django-admin startproject mysite`
-	使用内置server启动发布projecrt：`python manage.py runserver`
	-	指定端口号：`python manage.py runserver 8080`
	-	指定ip与端口号：`python manage.py runserver 0.0.0.0:8000`
-	创建app：`python manage.py startapp polls`
-	通知django需要更新数据库：`python manage.py makemigrations polls`
-	返回用于更新数据库的SQL语句：`python manage.py sqlmigrate polls 0001`
-	将更新写进数据库：`python manage.py migrate`
-	通过控制台控制数据库：` python manage.py shell`
-	声明使用的数据库表：`from polls.models import Question, Choice`
-	创建一条记录：`q = Question(question_text="What's new?", pub_date=timezone.now())`
	-	要提前导入：`from django.utils import timezone`
-	保存记录到数据库：`q.save()`
-	为站点创建管理员：`python manage.py createsuperuser`
-	使用admin页面可以管理对应的数据库表：
	```
	from django.contrib import admin
	from .models import Question

	admin.site.register(Question)
	```

### 在windows服务器中搭建django环境
-	首先在服务中安装django
-	安装Apache，[参考](http://www.cnblogs.com/fnng/p/4119712.html)
-	安装mod_wsgi，[下载地址](http://www.lfd.uci.edu/~gohlke/pythonlibs/#mod_wsgi)
	-	注意下载的文件的后缀为whl，将后缀名改为zip解压。解压之后将得到一个mod_wsgi.so 文件，将其拷贝到Apache24\modules\ 目录下。

### 一些问题
-	使用`python manage.py check`查错，例如：
-	如果出现`Segmentation fault`错误，执行`python manage.py check`，解决错误。

### django基础概念
-	一个视图就是Python的一个函数或方法。一般将视图文件的名称定为：veiws.py。django将从urls.py文件中找到对应的函数。
-	urls.py用于配置路径（域名之后的部分）与视图的对应关系，在django中每一个路径都对应一个视图。
	-	url()函数中有四个参数，其中两个是必须的：regex、view；两个可选的：kwargs、name
		-	regex：一般urlpatterns中有很多的url，系统会从上到下选择一个匹配的url。get与post参数不参加匹配。
		-	view：与对应url对应的视图，view的第一个参数是HttpResquest，余下的是从url中提取的参数。
		-	kwargs：关键字参数。
		-	name：给url命名，这样你就可以在其他地方用name引用这个url，特别是在template中，使用name可以减少后期维护的工作量（template中：`<a href="{% url 'detail' question.id %}">{{ question.question_text }}</a>`，urls.py中：`url(r'^(?P<question_id>[0-9]+)/$', views.detail, name='detail')`），这样在改变一个url时，只需在urls.py中更改即可。
-	django默认在每个app下找模板目录例如在polls app下找template目录。（static目录也是一样，static目录用于存放静态页面，如css文件：` polls/static/polls/style.css`）
-	可以在settings.py中改变时区（TIME_ZONE = 'Asia/Shanghai'）。
-	在project中激活app，在setting.py文件中的INSTALED_APPS中添加'polls.apps.PollsConfig'，注意逗号
-	Django admin模块是为了方便管理员添加修改删除数据和管理站点而建立的。admin适用于管理员而非网站的访问者。
-	同一个django project中可能有多个app，那么为了辨别不同app url中的name，django提供了名字空间的概念：
	-	在urlpatterns前加上app_name变量，表明pattern适用的app：`app_name = 'polls'`
	-	在模板总的用法：`<a href="{% url 'polls:detail' question.id %}">{{ question.question_text }}</a>`

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
