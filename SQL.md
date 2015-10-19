sql语句示例：

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
group by 语句按指定的列中的性质进行分类，如果列中只有男和女那么数据就分为两组。再对不同的组进行会总计筭，***每一组生成一条数据***。一般在存在group by子语句的sql语句中select的第一个列名与group by 分类的属性相同。
```
select 用户等级,性别,count(*) as '人数'
from 用户
group by 性别
order by 用户等级
```
注意 order by 是对选择之后的数据进行处理，故其在约书
