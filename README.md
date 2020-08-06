# 打卡机程序设计基本思路

## 1. 数据结构管理
后台数据库需要以员工的编号作为键值，从周一到周五，记录员工的上下班打卡时间
```
 ----------------------------------------------------------
| 员工编号 | 周一打卡时间 | 周二打卡时间 |........|周五打卡时间|
 ----------------------------------------------------------
```
简单地使用数组线性组织这些表项，更好的方式是使用哈希表，但实现稍微复杂

## 2. 系统运行方式
系统提供几种模式：
#### 1. 员工打卡模式
这种模式下，系统接受输入，为员工增加打卡记录
#### 2. 管理员模式
这种模式下，可以对系统中的几个关键变量进行修改，如上班规定时间，时间流动速度等
#### 3. 结算模式
这种模式下，可以对数据记录进行结算，显示考勤的数据统计


## 3. 操作方式
使用命令行的形式。
* time ->显示当前时间
* work ->进行打卡操作