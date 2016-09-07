本文以MySQL为例
### mySQL的设置
-	安装（因为mysql被oracle收购，应该算纯开源，故使用mariabd替代）
	-	`yum -y install mariadb* `
	-	`systemctl start mariadb.service `
	-	`systemctl enable mariadb.service `
	-	`mysql_secure_installation `//一路yes,为数据库增加安全功能
-	以root权限登录：`mysql -u root -p`  ( `mysql -h hotname -u username -p`缺省的host为当前机器，缺省的username为登录系统的用户名)
-	创建用户：`insert into mysql.user(Host,User,Password) values("localhost","username",passward("123456"));`。也可以直接使用grant命令在授予权限的同时创建用户。
-	无论使用什么方式创建用户都需刷新权限表：flush privileges;使用户生效。
-	为用户授权：见下面grant命令（需要使用root登录）。
-	可以直接执行包含sql语句的文件：`> mysql -h host -u bookorama -D books -p < bookorama.sql`
-	删除匿名访问权限：
	-	`use mysql;`//指令后的分号告诉系统执行当前语句
	-	`delete from user where User=''`
	-	使命令生效：`mysqladmin -u root -p reload`
-	创建数据库：`create database books;`
-	从数据库中导出语句：` mysqldump  -u  root  -p  javadb > d:\789.sql`
-	grant和revoke命令：赋予和撤销用户的global、database、table、column四种不同的权限。

```
//用户典型的权限设置
mysql> grant select, insert, update, delete, index, alter, create, drop
	-> on books.*          #在这里books为数据库名，books.*表示books中的所有表。*.*表示所有数据库中的表。
	-> to username identified by ‘'pwd'; #flush privileges;使用户生效。
//取消用户的某些权限
//删除用户username
revoke  all privileges ,grant
	-> from username;
//减少部分权限
revoke alter，create ，drop
	-> on books.*
	-> from username;
```
-	使用指定的数据库：`use dbname`
-	创建表：`create table tablename(columns );`

```
Book-O-Rama schema:
	Customers(CustomerID, Name, Address, City)  CustomerID 为主键
	Orders(OrderID, CustomerID, Amount, Date)   OrderID 为主键 CustomerID 为外键
	Books(ISBN, Author, Title, Price) ISBN为主键 
	Order_Items(OrderID, ISBN, Quantity) OrderID 和ISBN同为主键与外键
	Book_Reviews(ISBN, Reviews) ISBN为主键且为外键
SQL语句：
create table customers
(  customerid int unsigned not null auto_increment primary key,
   name char(50) not null,
   address char(100) not null,
   city char(30) not null
);
create table orders
(  orderid int unsigned not null auto_increment primary key,
   customerid int unsigned not null,
   amount float(6,2), #显示6位有效数字（不含小数点），2位的小数点
   date date not null
);
create table books
(  isbn char(13) not null primary key,
   author char(50),
   title char(100),
   price float(4,2)
);
create table order_items
(  orderid int unsigned not null,
   isbn char(13) not null,
   quantity tinyint unsigned,

   primary key (orderid, isbn)
);
create table book_reviews
(
  isbn char(13) not null primary key,
  review text
);
```
-	查看表与数据库：`show tables;`，`show databases;` ,`describe databasename`（describe描述的是***表的信息***不是数据库）
-	用户管理：
	-	最小权限原则：一个用户或进程应该拥有能够执行分配给它的任务的最低级别的权限。

### 表的设计理念
-	每一个表都要有一个***主键***，这样才能实现与其他表的交互，主键最好有一定的意义，最好不要将自动增长的id作为主键。
-	***主键***：表中可以唯一标识行的列或列的组合（主键用下划线表示）。
-	外键：当前表中的列在其他表中为主键，则称此列为外键（外键使用斜体表示）。
-	***原子列***：列中的元素是不可分割的，例如一个订单中可能有多本书，但为了不在一个列中存放多个书名，可以再建立一个表，表中放置订单号、书名和对应的书的数量，通过查找相同的订单号来获取同一个订单中的所有书名。
-	模式：数据库整套表格的完整设计，可以认为模式为数据库的设计蓝图。
-	关系：同一个数据库中不同表之间行与行之间的关系。主要由三种：一对一（两个表中的行与行之间只存在一对一的关系），一对多（一个表中的一行和另一个表中的若干行相对应），多对多。
-	在设计表时，我们常对现实世界的**实体**与**关系**（实体与实体之间的关系）建立模型。
-	每个表中只放置与实体和关系必要的属性以防数据的冗余。很多数据如果不是唯一的，就只在一张表中保存，否则要改动这些数据时的开销会很大，而且很可能会破坏数据的完整性（例如数据的不一致）
### mySQL中的数据类型（php和mySQL web开发中文版179页）
-	整数类型（在类型后添加unsigned，创建对应的无符号型变量）：tinyint、bit、bool、smallint、mediumint、int、integrate、bigint。
-	浮点数：float、double、precision、real、decimal、numeric、dec、fixed。
-	日期和时间：
	-	date yyyy-mm-dd
	-	time hh:mm:ss
	-	datetime yyyy-mm-dd hh:mm:ss
	-	timestamp  有不同的表示方式
	-	year
-	字符串类型
	-	char [binary|ascii|unicode]、varchar 
	-	text
	-	BLOB （binary large objects），可以用于存储图片、视频、声音等所有类型的数据。
	-	set 和 enum
### SQL注意事项：
-	sql对大小写不敏感，但数据库和表名对大小写敏感。
### sql语句示例：

1. 选区指定的列
```
select 图书编号,图书名称
from 图书
```
2. 查询全部信息
```
select *
from 图书
```
3. 查询信息之后更改所获得的列的名称
```
select 姓名 as '用户名', 电话 as '联系电话'
from 用户
```
也可以这样
```
select '用户名'=姓名,'联系电话'=电话
from 用户
```
4. 对某些列进行计筭后在显式
```
select 图书编号,图书名称,'折后价格'=定价*0.8
from 图书
```
5. 削除重复的行
```
select disticnt 订单状态
from 订单
```
6. 限制返回结果的行数
```
select top n [percent] 列名
from ...
```
7. where子句
```
select 用户帐号, 姓名,性别,创建时间
from 用户
where 创建时间>'2010-12-31' and 性别='男'
```
```
select 用户帐号,姓名,创建时间,消费金额
from 用户
where 创建时间 between '2010-1-1' and '2010-12-31'
```
8. 列表查询
```
select *
from 用户
where 用户.用户等级 in (1,2,4)
```
9. 模糊匹配查询
```
select *
from 用户
where 用户.用户名 like '李%_'
```
通配符的意义：
```
_：单个任意字符
%：0个或多个任意的字符
[]:指定范围内的任意字符
[^]：不属于指定范围的字符
```
10. 空值查询
```
where 表达式 is [not] NULL
```
11. order by
```
select *
from 图书
where 库存量>500
order by 上架时间,定价 desc
```
order by默认条件是升序排列，对于上面的语句，全局而言按上架时间升序排列，对于上架时间相同的行再以定义逆序排列。
12. select into ...
```
select 图书编号,图书名称,作者,定价
into 计算机类图书
from 图书
where 类别=1
```
执行之后将创建一个新表：计算机类图书，其中其列名由select语句决定。
13. 聚合函数（对列进行操作）
```
select max(销售量) as '类别5最高销售量'
from 图书
where 类别=5
```
```
select count(*) as '消费500元以上人数'
from 用户
where 消费金额>500
```
14. 分组查询（group by）
```
select 性别,count(*) as '人数'
from 用户
group by 性别
```
group by 语句按指定的列中的性质进行分类，如果列中只有男和女那么数据就分为两组。再对不同的组进行汇总计筭，***每一组生成一条数据***。一般在存在group by子语句的sql语句中select的第一个列名与group by 分类的属性相同。
```
select 用户等级,性别,count(*) as '人数'
from 用户
group by  用户等级 性别 
order by 用户等级 性别
```
注意 order by 是对选择之后的数据进行处理，故其在选择数据的语句之后。本句先对数据以用户等级分组，再以性别进行分组，再统计小组的数据。
15. having子句（对group by之后的组进行进一步的筛选）
```
select 类别 ,sum(销售量) as '总销量'
from 图书
group by 类别
having sum(销售量)>200
```
16. ***where 用于筛选from指定的数据对像;group by用于对where的结果进行分组;having 则是对group by分组后的数据进行筛选。***
17. compute 子句对要显式的表进行进一步的处理...
18. 多表查寻
```
select 用户.用户帐号, 等级.等级名称
from 用户,等级
where 用户.用户等级 = 等级.等级编号
```
```
select 图书.*, 图书类别.*
from 图书,图书类别
where 图书.类别 = 图书类别.类别编号 and 定价>=50 and 图书类别.类别名称 = '计算机'
```
19. 多表连接（join）
	1. 内连接（inner join）以on后面的条件为表的连接条件。内连接的特点是舍去那些不满足条件的行。
	```
	select 用户帐号,姓名,消费金额,等级编号
	from 用户 join 等级 on 用户.用户等级 = 等级.等级编号
	```
	2. 外连接 外连接的特点是：以左外连接为例：即使左表的一些行在右表中没有与之对应的行，也将左表这些行保存下来，其右侧的数据用NULL补充。左外和右外的区别在于以哪个表为主表。
		1. 左外连接
		`from 表1 left [outter] join 表名2 on 条件`
		2. 右外连接
		`from 表1 right [outter] join 表名2 on 条件`
	3. 交叉连接
	`from 表1 cross join 表2`           
	交叉连接没有条件，所获得的表是表1的每一行与表2的每一行相连接的结果，相当于以两表的行为元素进行笛卡尔积运算。

