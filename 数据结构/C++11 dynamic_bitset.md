#### C++11 dynamic_bitset

C++ 标准为处理二进制数值提供了两个工具，vector<bool>和bitset.

vector<bool>是对元素类型为bool的vector特化，它内部并不是真正存储bool值，而是用bit来压缩保存，使用代理技术来操作bit，造成的后果就是它很像容器，大多数情况下的行为与标准容器一致，但他并不是容器，不满足容器的定义。（在数据存储上，有一种对象类型，它可以持有其它对象或指向其它对像的指针，这种对象类型就叫做容器）

bitset与vector<bool>类似，同样存储二十进制位，但他的大小固定，而且比vector<bool>支持更多的位运算。

vector<bool>和bitset各有优缺点，vector可以动态增长，但不能方便地进行位运算，bitset则正好相反。

boost.dynamic_bitset刚好能兼顾



**头文件**：

#include <boost/dynamic_bitset.hpp>

using namespace boost;



**注意**：

与vector<bool>和bitset一样，dynamic_bitset不符合标准容器的定义，不是严格意义上的“容器”。



**创建和赋值**：

模板参数：

```c++
template<typename Block,typename Allocator>
```

参数1指明dynamic_bitset以什么整数类型存储二进制位，必须是一个无符号整数，默认是unsigned long，第二个类型参数是类内部使用的内存分配器，默认是std::allocator<Block>.这两个参数我们无需改动，默认类型会工作的很好。

```c++
dynamic_bitset<> db1; // 空的
dynamic_bitset<> db2(10); // 大小为10的dynamic_bitset
dynamic_bitset<> db3(0x16,BOOST_BINARY(10101)); // 大小为22的dynamic_bitset
dynamic_bitset<> db4(string("0100")); // 字符串构造
dynamic_bitset<> db5(db3); // 拷贝构造

dynamic_bitset<> db6;
db6 = db4; // 赋值操作符
```

这其中，db3对象使用了BOOST_BINARY宏构造了一个编译期的二进制数，没有运行时开销，较db4使用string临时变量的构造效率更高。

**dynamic_bitset内部按照由高到低的顺序存储二进制位，也就是说，第0个元素存储最低位（二进制字面值最右边的值）。**

 **容器操作**：

```c++
dynamic_bitset<> db;
db.resize(10,true); // 使用true可以默认为1 扩展为10个二进制位
db.resize(5); 缩小容量为5
```

清空dynamic_bitset可以使用成员函数resize(0),但使用clear(）更快速。

```c++
dynamic_bitset<> db(5,BOOST_BINARY(01110))；
cout << db << endl; // 输出01110

db.clear() // 清空
```

dynamic_bitset使用block来存储二进制位，因此size()函数不能反馈dynamic_bitset所占用内存的大小，dynamic_bitset提供num_blocks()返回所有二进制位占用的block的数量，即size()/sizeof(Block)*8+1

在64为的linux系统上，如果使用默认模板参数unsigned long，那么一个Block就可以存储64个二进制位，num_blocks()的计算公式是size()/64+1.下面断言成立

```c++
assert(dynamic_bitset<>(64).num_blocks()==1);

assert(dynamic_bitset<>(65).num_blocks()==2); // 为啥啊？
```

push_back()-可以使用

append() 是另一个增加值的方法，它把整数转换为二进制位全部追加到dynamic_bitset末尾（最高位）。读者请注意append()的效果，它将整数转换为一个Block再追加，这将使dynamic_bitset的大小增加一个Block的长度：

```c++
dynamic_bitset<> db(5,BOOST_BINARY(01001));
db.append(BOOST_BINARY(101));
assert(db.size() == sizeof(unsigned long)*8 + 5);
cout<<db<<endl; // 0...010101001 

```

**位运算与比较运算**：

与vector<bool>相似，dynamic_bitset也运用了代理技术，重载了operator[]等操作符，能像普通数组一样访问二进制位，而且能对二进制位或整个容器做任意位运算（|、^、~、<<等）。dynamic_bitset也提供了各种比较操作符，可以对两个dynamic_bitset对象进行各种比较运算。

因此对dynamic_bitset对象的操作就如同操作两个普通的二进制数，只是不能做加减乘除的算术运算而已。

示范：

```c++
dynamic_bitset<> db1(4,BOOST_BINARY(1010));
db1[0] &= 1; // 按位与运算
db1[1] ^= 1; // 按位异或运算
cout<<db1<<endl; // 1000

```

**访问元素**：

四个测试二进制位的函数：

1、test()函数检验第n位是否是1;

2、如果容器中存在二进制位1，那么any()返回true；

3、如果容器不存在二进制位1，那么none()返回true;

4、count()函数统计容器中所有值为1的元素的数量；



有三个翻转二进制位的函数：

1、set()函数可以置全部或者特定位置的值为1或0；

2、reset()函数可以置全部或者特定位置的值为0；

3、flip()可以翻转全部或者特定位置的值；

```c++
dynamic_bitset<> db(4,BOOST_BINARY(0101))；
db.flip() // 翻转所有二进制位
assert(db.to_ulong() == BOOST_BINARY(1010));
db.set(); // 置所有位为1
assert(!db.none()); // 此时无0二进制位
db.reset(); // 置所有位为0
assert(!db.any()); // 此时无1二进制位
db.set(1,1); // 设置db[1]为值1
```



dynamic_bitset还为访问元素提供了查找操作：

1、find_first()从第0位开始查找，返回第一个值为1的位置；

2、find_next(pos)则从第pos位置开始查找，返回第一个值为1的位置，如果找不到这样的值，则返回npos

**类型转换**：

to_ulong()可以直接将内部存储的二进制转换成类型为unsigned long的整数。

```c++
dynamic_bitset<> db(10,BOOST_BINARY(1010101));
COUT<< db.to_ulong()<<endl; // 85
```

