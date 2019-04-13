### bimap

C++标准提供了映射型容器map和multi_map,它们就像是一个关联数组,把一个元素(key)映射到另一个元素(value),但这种映射是单向的.

boost.bimap扩展了标准库的映射型容器,提供双向映射的能力,功能强大.

#### 头文件

```c++
#include <boost/bimap.hpp>
using namespace boost;
```

#### 基本用法

bimap可以容纳两个类型的视图,是这两种元素的集合,这是bimap的基本视图.此外,这个关系还可以有两个视图:左视图和右视图,分别用成员变量left和right访问,相当于两个不同方向的std::map,其用法和std::map一样.

对于bimap<X,Y>,bimap.left相当于map<X,Y>,bimap.right相当于map<Y,X>. 

例如:下面的代码定义了一个int和string的bimap,分别用左视图和右视图插入一些数据,最后用左视图查看:

```c++
#include <boost/bimap.hpp>
#include <iostream>
using namespace std;
using namespace boost;

int main()
{
    bimap<int,string> bm; // 定义一个双向视图对象


    // 使用左视图map<int,string>
    bm.left.insert(make_pair(1,"111"));
    bm.left.insert(make_pair(2,"222"));

    // 使用右视图map<string,int>
    bm.right.insert(make_pair("string",10));
    bm.right.insert(make_pair("bimap",20));

    // 对左视图使用迭代器迭代
    for(auto pos = bm.left.begin();
    pos!=bm.left.end();++pos)
    {
        cout<<"left["<<pos->first<<"]="<<pos->second<<endl;
    }

    return 0;
}
```

bimap的左右视图的基本用法与std::map相同,但也有一些区别.首先,因为它的双向性,key/value必须唯一,插入任何一个重复元素都是无效操作.

```c++
bm.left.insert(make_pair(2,"222"));
bm.left.insert(make_pair(2,"333"));// 无效插入操作
bm.right.insert(make_pair("string",2)); // 无效插入操作
```

bimap的两个视图的迭代器返回的值都是常量对象,相当于pair<const,const>,不能如std::map那样修改value的值,代码:

```c++
bm.right.begin()->second = 234;// 会导致编译错误,提醒你不能给常量赋值
```

最后一点区别是bimap不能使用operator[]和at(),不能像关联数组那样使用.

bimap有两个内部类型value_type和relation,它是bimap关系集合元素的类型,可以在不使用左右视图的情况下像操作集合一样插入bimap元素.

```c++
bimap<int, string> bm; 
typedef decltype(bm)::value_type vt; // 使用decltype
bm.insert(vt(3,"333"));
```

#### 值的集合类型

示范:

```c++
// 左组是有序集合,右组是无序集合
bimap<int, unordered_set_of<string>> bm1; // 默认使用set_of类型

// 左组和右组都是有序多值集合
bimap<multset_of<int>,multiset_of<string>> bm2;

// 左组是无序集合,右组是一个序列,只能有左视图
bimap<unordered_set_of<int>, list_of<string>> bm3;// 因为list_of不能作为索引,序列集合,无对应的标准容器
```



#### 集合类型的用法

如果要使用双向映射,左组和右组都必须是有序的,如果其中的一组是无序的,那么就没有相应方向的映射视图,如果两组都是无序的,那么只能用bimap的集合视图来访问元素.

```c++
#include <iostream>
#include <boost/bimap.hpp>
#include <boost/unordered_set.hpp>
using namespace std;
using namespace boost;

template<typename T>
void print_map(T &m)
{
    for(auto&x : m)
    {
        cout << x.first << "<->" <<x.second<<endl;
    }
}

// 接下来声明一个无序多组的bimap,它的左组和右组可以插入任意可重复的值
bimap<unordered_multiset_of<int>, unordered_multiset_of<string> bm;

int main()
{

    bm.left.insert(make_pair(1,"111"));
    bm.left.insert(make_pair(2,"222"));
    bm.left.insert(make_pair(2,"555"));

    bm.right.insert(make_pair("string",10));
    bm.right.insert(make_pair("bimap",20));
    bm.right.insert(make_pair("bimap",2));

    print_map(bm.left);

    // 如果声明一个右值的集合类型是序列或者随机访问类型的bimap
    bimap<set_of<int>,vector_of<string>> bm;
    // 只能使用左视图,企图使用右视图会引发编译错误.但有一个优点,可以在左视图使用[] at(),像操作一个关联数组.

    bm.left.insert(make_pair(1,"111"));
    bm.left[2] = "222";
    bm.left[3000]= "bimap";

    // bm.right.insert()-错误

    return 0;
}


```

