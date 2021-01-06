counter = 100          # 整型变量
miles   = 1000.0       # 浮点型变量
name    = "runoob"     # 字符串

print (counter)
print (miles)
print (name)

a = b = c = 1
print(a,b,c)

a, b, c = 1, 2, "runoob"
print(a,b,c)

a, b, c, d = 20, 5.5, True, 4+3j
print(type(a), type(b), type(c), type(d))#用type可以输出变量类型
#还可以用 isinstance 来判断类型：
a=111
print(isinstance(a,int))
#isinstance 和 type 的区别在于：
#1.type()不会认为子类是一种父类类型。
#2.isinstance()会认为子类是一种父类类型。
#注意：在 Python2 中是没有布尔型的，它用数字 0 表示 False，用 1 表示 True。
#到 Python3 中，把 True 和 False 定义成关键字了，但它们的值还是 1 和 0，它们可以和数字相加。

#删除引用
var1,var2=1,10
del var1,var2

#运算
print(4+5)    # 加法
print(4.3 - 2)# 减法
print(3 * 7)  # 乘法
print(2 / 4)  # 除法，得到一个浮点数
print(2 // 4) # 除法，得到一个整数
print(17 % 3) # 取余
print(2 ** 5) # 乘方

#List(列表)
list = [ 'abcd', 786 , 2.23, 'runoob', 70.2 ]
tinylist = [123, 'runoob']

print (list)            # 输出完整列表
print (list[0])         # 输出列表第一个元素
print (list[1:3])       # 从第二个开始输出到第三个元素
print (list[2:])        # 输出从第三个元素开始的所有元素
print (tinylist * 2)    # 输出两次列表
print (list + tinylist) # 连接列表
#与Python字符串不一样的是，列表中的元素是可以改变的

#Tuple(元组)
tuple = ( 'abcd', 786 , 2.23, 'runoob', 70.2  )
tinytuple = (123, 'runoob')

print (tuple)             # 输出完整元组
print (tuple[0])          # 输出元组的第一个元素
print (tuple[1:3])        # 输出从第二个元素开始到第三个元素
print (tuple[2:])         # 输出从第三个元素开始的所有元素
print (tinytuple * 2)     # 输出两次元组
print (tuple + tinytuple) # 连接元组
#元组与字符串类似，可以被索引且下标索引从0开始，-1 为从末尾开始的位置。
#也可以进行截取（看上面，这里不再赘述）。其实，可以把字符串看作一种特殊的元组。
#tuple的元素不可改变，但它可以包含可变的对象，比如list列表。
#构造包含 0 个或 1 个元素的元组比较特殊，所以有一些额外的语法规则：
tup1 = ()    # 空元组
tup2 = (20,) # 一个元素，需要在元素后添加逗号

#集合(Set)
sites = {'Google', 'Taobao', 'Runoob', 'Facebook', 'Zhihu', 'Baidu'}

print(sites)   # 输出集合，重复的元素被自动去掉

# 成员测试
if 'Runoob' in sites :
    print('Runoob 在集合中')
else :
    print('Runoob 不在集合中')


# set可以进行集合运算
a = set('abracadabra')
b = set('alacazam')

print(a)

print(a - b)     # a 和 b 的差集

print(a | b)     # a 和 b 的并集

print(a & b)     # a 和 b 的交集

print(a ^ b)     # a 和 b 中不同时存在的元素

#字典(Dictionary)
dict = {}
dict['one'] = "1 - 菜鸟教程"
dict[2]     = "2 - 菜鸟工具"

tinydict = {'name': 'runoob','code':1, 'site': 'www.runoob.com'}


print (dict['one'])       # 输出键为 'one' 的值
print (dict[2])           # 输出键为 2 的值
print (tinydict)          # 输出完整的字典
print (tinydict.keys())   # 输出所有键
print (tinydict.values()) # 输出所有值