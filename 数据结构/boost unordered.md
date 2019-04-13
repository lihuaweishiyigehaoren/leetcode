### unordered_set

boost.unordered库提供了完全符合c++11标准的散列容器实现,包括无序集合(set)和无序映射(map).

#### **头文件**

```c++
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
using namespace booost;
```

提供两个散列集合类:unordered_set和unordered_multiset,它们的接口/用法与C++标准里的关联容器set/multiset相同,只是内部使用散列表代替了二叉树实现,因此查找复杂度由对数降为常熟.

#### 基本用法

```C++
#include <boost/unordered_set.hpp>
using namespace boost;

int main()
{
    // 初始化
    unordered_set<int> s = {1,2,3,4,5};
    
    for(auto x : s)
    {
        cout<<x<<"";
	}
    
    cout<<endl;
    cout<<s.size()<<endl;
	
    s.clear();
    cout<<s.empty()<<endl;
    
    s.insert(8);
    s.insert(45);
    cout<<s.size()<<endl;
    cout<<*s.find(8)<<endl; // 查找元素
    
    s.erase(45); // 删除元素
}
```

unordered_set直接也可以执行比较运算

```c++
using namespace boost::assign;
unordered_set<int> us1 = list_of(1)(2)(3); // 使用assign库赋值
unordered_set<int> us2 = list_of(3)(2)(1); 
assert(us1 == us2); // 
```



#### emplace()示例

```c++
#include <iostream>
#include <boost/unordered_set.hpp>
using namespace boost;
using namespace std;

typedef complex<double> complex_t; // 使用标准库的复数类型

int main()
{
    
    unordered_set<complex_t> s; // 散列容器容纳复数

    s.emplace(1.0,2.0); // 直接使用多个参数构造元素并插入
    s.emplace(3.0,4.0); // 忽略返回值

    for(auto& x : s)
    {
        cout<< x <<",";
    }
    cout<< endl;
    s.emplace_hint(s.begin(),5.0,6.0); // 在容器前端插入,不能保证位置
    for(auto& x : s)
    {
        cout<< x <<",";
    }
    return 0;
}
```



### unordered_map

unordered_map属于关联式容器,采用std::pair保存key-value形式的数据,可以理解成一个关联数组,提供operator[]重载,用法与标准容器std::map完全相同.

#### 基本用法

unordered_map的基本用法和unordered_multimap类似,但是unordered_multimap允许有重复的key-value映射,因此不提供operator[]

```c++
#include <boost/unordered_map.hpp>
#include <iostream>
#include <boost/assign.hpp> 
using namespace std;
using namespace boost;

int main()
{
    // using namespace boost::assign;

    // 使用assign初始化
    unordered_map<int,string> um = assign::map_list_of(1,"one")(2,"two")(2,"three");

    um.insert(make_pair(10,"ten")); // 可以使用insert()函数
    cout<<um[10]<<endl; // 可以使用[]访问元素

    um[11] = "eleven"; // 关联数组用法
    um[15] = "fifteen";

    auto p = um.begin();   // 使用auto获取迭代器
    for(; p != um.end();++p)
    {
        cout<<p->first<<"-"<<p->second<<",";
    }

    cout<<endl;

    um.erase(11); // 删除键值为11的元素
    cout<<um.size()<<endl;
}
```



unordered_map 同样支持比较运算:

同上.

#### emplace

```c++
/*
unordered库完全模仿实现了C++11标准,在boost::unordered名字空间定义了piecewise_construct_t类型和它的一个实例
*/

// 因此可以使用C++11风格的emplace方法了;
#include <iostream>
#include <boost/unordered_map.hpp>
using namespace std;
using namespace boost;

typedef complex<double> complex_t; // 标准复数类型
typedef unordered_map<int,complex_t> um_t; // 散列映射类型,散列容器

int main()
{
    um_t s;

    s.emplace(boost::unordered::piecewise_construct,
    make_tuple(1),make_tuple(1.0,2.0)); // 分段构造pair,使用make_tuple

    s.emplace(boost::unordered::piecewise_construct,
    make_tuple(3),make_tuple(3.0,4.0));

    for(auto& x:s)
    {
        cout<<x.first<<"<->"<<x.second<<",";
    }
    cout<<endl;

    s.emplace_hint(s.begin(),
    boost::unordered::piecewise_construct,
    make_tuple(5),make_tuple(5.0,6.0));

    for(auto &x : s)
    {
        cout<< x.first<<"<->" <<x.second<<",";
    }


    return 0;
}
```

#### 高级解释

unordered库使用"桶"来存储元素,散列值相同的元素被放入同一个桶中,当前散列容器的桶的数量可以用成员函数bucket_count()来获得,bucket_size()返回桶中的元素数量.

```c++
unordered_set<int> us = (list_of(1),2,3,4);
cout<< us.bucket_count()<<endl;

for(size_t i = 0; i<us.bucket_count();++i)
{
    cout<<us.bucket_size()<<",";
}
```

当散列容器中有大量的数据时,桶中的元素数量也会增多,会造成访问冲突.为了提高散列表的性能,unordered库会在插入元素时自动增加桶的数量,用户不能直接指定桶的数量,但课在构造函数或者rehash()函数指定最小的桶的数量;

例如:

```c++
unordered_set<int> us(100);
us.rehash(200) 
```

散列容器中还有一个函数max_load_factor(),它可以获取或设定散列容器的最大负载因子,即桶中元素的最大平均数量.通常最大负载因子都是1,不应改变它.



