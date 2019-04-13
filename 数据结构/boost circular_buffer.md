### boost circular_buffer

circular_buffer实现了循环缓冲区的数据结构,支持标准的容器操作(如push_back)但是大小是固定的,当到达容器末尾时将自动循环利用容器另一端的空间



#### 头文件

```c++
<boost/circular_buffer.hpp>
```



#### 用法

circular_buffer被设计成一种可以与标准容器无缝结合使用的容器,实现了一个大小固定的循环队列,就像是一个deque和stack的混合体,可以像普通双端队列一样执行push_back(),push_front(),insert()等操作来增加元素,也可以像栈一样pop_back(),pop_front()来弹出元素,它也具有标准容器的共通功能,如判断大小,获取迭代器,删除元素,operator[]等.例如:

```c++
#include <iostream>
#include <boost/circular_buffer.hpp>
#include <assert.h>
using namespace std;
using namespace boost;

int main()
{

    circular_buffer<int> cb(5);// 声明一个大小为5的循环缓冲区
    assert(cb.empty()); //缓冲区目前无数据

    cb.push_back(1); // 向后端添加元素1
    cb.push_front(2); // 向前端添加元素1
    assert(cb.front() == 2);
    cb.insert(cb.begin(),3); // 向前端添加元素3

    // 可以使用迭代器遍历容器
    for(auto pos = cb.begin();pos != cb.end();++pos)
    {
        cout<<*pos<<",";
    }
    cout<<endl;

    cb.pop_front(); // 弹出首元素3
    assert(cb.size() == 2);
    cb.push_back(); // 弹出元素1

    assert(cb[0]=2);

    return 0;
}
```

也重载了比较运算符.



#### 环形缓冲区

circular_buffer 的特殊之处在于它内部存储数据的方式,内存空间不是动态增长的,而是循环使用的.可以把circular_buffer内部想象成一个收尾相连的环,当元素数量达到容器上限时将自动重用最初的空间.

例子:

```c++
#include <iostream>
#include <boost/assign.hpp>
#include <boost/circular_buffer.hpp>
using namespace std;
using namespace boost;
// using namespace boost::assign;

template<typename T>
void print(T& cb)
{
    for(auto &x : cb)
    {
        cout<<x<<",";
    }
    cout<<endl;
}

int main()
{
    using namespace boost::assign;
    // circular_buffer可以使用assign库初始化
    circular_buffer<int> cb = (list_of(1),2,3);
    print(cb); // 1,2,3此时缓冲区已满

    cb.push_back(4); // 4将覆盖最开始的1
    print(cb); // 2,3,4 begin()从2开始

    cb.push_back(5); // 5将覆盖最开始2
    print(cb); // 3,4,5 begin()从3开始

    cb.pop_front();  // 弹出最开始的3
    print(cb); // 4,5现在只有两个元素

    return 0;
}
```



#### 特殊操作函数

full() 判断缓冲区是否已满

linearize() 可以把缓冲区线性化成一个连续的普通数组,is_linearized()可以检测缓冲区可否连续化

rotate() 从指定的迭代器位置旋转整个缓冲区

例如:

```c++
using namespace boost::assign;
circular_buffer<int> cb = (list(1),2,3,4,5);
assert(cb.full());
print(cb);

int * p = cb.linearize(); // 获取线性数组
assert(p[0]==1&&p[3]==4);

cb.rotate(cb.begin()+2); // 从第三个位置开始旋转
print(cb);// 3,4,5,1,2
```



在使用circular_buffer需要注意一点,虽然circular_buffer内部存储是循环的,但它的迭代器不是循环的,迭代器只在begin()和end()区间内有效,超过这个区间迭代器就会失效.





#### 空间优化型缓冲区

一次性分配内存,是标准容器的通常做法,但对于缓冲区数据不一定合适.因此,circular_buffer库提供了一个circular_buffer_space_optimized类,它是circular_buffer的适配器,只有在需要时候,才分配内存 空间,而且当元素减少时也会自动释放内存.

circular_buffer_space_optimized的用法几乎与circular_buffer完全相同:

```c++
using namespace boost::assign;

circular_buffer_space_optimized<int> cb(10);
push_back(cb)(1),2,3,4;

assert(cb.size() == 4);
assert(cb.capacity() == 10);

cb.resize(100,10);
assert(cb.size() == cb.capacity());
```

当程序需要容纳大量的元素,但大多数情况下仅保存较少数量元素的时候就可以使用circular_buffer_space_optimized,它可以有效减少内存的占用,提高程序的运行效率.



