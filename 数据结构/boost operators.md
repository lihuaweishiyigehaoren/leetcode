### boost operators

其实不必定义所有的操作符,比如定义了== ,!=就自动出来了,因此只需要定义少量的操作,就能够实现大部分的操作.

boost.operators在自己类中仅定义了少量的操作付(如<),就可以方便地自动生成其他操作符重载,而且保证了正确的语义实现.

#### 头文件

```c++
#include <boost/operators.hpp>
using namespace boost;
```



#### 基本运算概念

由于C++可重载的操作符非常多,因此operators 库由多个类组成的,分别来实现不同的运算概念,比如less_than_comparable定义了<系列操作符,left_shiftable定义了<<系列操作符.

- equality_comparable : 要求提供== ,可自动实现!=,相等语义;
- less_than_comparable:  要求提供<,可以自动实现> ,<=,>=
- ... 自己查阅书本

这些概念在空中以同名类的形式提供,用户需要以继承的方式来使用它们,继承的修饰符并不重要(private public都可以),因为operators库里的类都是空类,没有成员变量和成员函数,仅定义了数个友元操作符函数.



例如:less_than_comparable的形式是:

```c++
template <class T>
    struct less_than_comparable{
        friend bool operator> (const T&x,const T &y);
        ....
    }
```



如果要同时实现多个运算概念则可以使用多重继承技术,把自定义类作为多个概念的子类,但多重继承在使用时存在很多问题,稍后使用operators特别的技巧来解决这个问题.



#### 算术操作符的用法

point类,例如:

```c++
class point
{
    int x, y, z;
public:
    explicit point(int a = 0,int b = 0,int c= 0):x(a),y(b),z(c){}
    void print() const
    {
        cout<<x<<","<<y<<","<<z<<endl;
    }
}
```

我们先来实现less_than_comparable,它要求point类提供<操作符,并由它继承.

假定point的小于关系是由三个坐标值的平方和决定的

下面的代码示范了less_than_comparable的用法,只需要为point增加父类,并定义less_than_comparable概念所要求的operator<;

```c++
#include <boost/operators.hpp>
class point : boost::less_than_comparable<point> // 小于关系,私有继承
{
    public:
    frient bool operator<(const point &1, const point& r)
    {
        return (1.x*1.x+1.y*1.y+1.z*1.z < r.x*r.x+r.y*r*y);
    }
    ... // 其他成员函数
}
```

less_than_comparable 作为基类的用法可能稍微有点奇怪,它把子类point作为模板父类的模板参数,less_than_comparable<point>,看起来好像是个"循环继承",实际上,point类作为less_than_comparable的模板类型参数,只是用来实现内部的比较操作符,用做操作符函数的类型,没有任何继承关系.less_than_comparable生成的代码可以理解成这样:

less_than_comparable生成的代码可以理解成这样：

```c++
// template <T = point>
struct less_than_comparable
{
    friend bool operator>=(const point&x,const point& y)
    {
        return !(x<y);
	}
}
```



明白了less_than_comparable的继承用法，剩下的就很简单了：point 类定义了一个友元operator<操作符，然后其余的>,<=,>=就由less_than_comparable自动生成，几乎不费什么力气，在没有污染名字空间的情况下，我们就获得了四个操作符的能力。



同样也可以定义相等关系，自行实现operator==

```c++
class point: boost::less_than_comparable<point>,boost::equality_comparable<point>
{
public:
	friend bool operator<(const point &1,const point&r)
	{
		//同前面
	}
	
	friend bool operator==(const point& 1,const point& r)
    {
    	return r.x == 1.x && r.y == 1.y&& r.z == 1.z;
    }
}
```



然后我们就自动获得了operator != 的定义。

在使用operators库时要注意一点，模板类型参数必须是子类本身，特别是当子类本身也是个模板类的时候，不要错写成子类模板参数或者子类不带模板参数的名称，否则会造成编译错误。例如

```c++
template<typename T> class point{...};
// 那么下列的形式都是错误的
template<typename T> class pont: boost::less_than_comparable<T>
template<typename T> class pont: boost::less_than_comparable<point>
// 正确的写法应该是
template<typename T> class pont: boost::less_than_comparable<point<T>>
```



#### 基类链

多重继承使用不当会引发诸多问题。

operators库使用泛型编程的“基类链”技术解决了多重继承的问题，这种技术通过模板把多继承转换成了链式的单继承。

前面讨论到less_than_comparable<point>这种用法时，我们说它不是继承，然后，现在我们将看到它居然真的可以实现继承的功能，这从一个方面展示了泛型编程的强大威力。

operators库的操作符除了接受子类作为比较类型外，还可以接受另外一个类，作为他的父类，由此可以无限串联链接在一起（但受到编译器模板的编译能力限制),像这样：

```c++
demo: x<demo, y<demo,z<demo,...>>>
```

使用基类链技术，point类的基类部分可以是这样：

```c++
boost::less_than_comparable<point,boost::equality_comparable<point>>
```

对比多重继承写法，代码非常相似，区别仅仅在于模板参数列表结束符号（>）的位置，正是因为这样写，使基类链通过模板组成了一连串的单继承链表，而不是多个父类的多重继承。



#### 复合运算的概念

基类链技术解决了多重继承的效率问题，但是为了使用操作符概念就要写出很长的基类链代码。因此operators库使用基类链把一些简单的运算概念组合成了复杂的概念，即复合运算。这是个很自然的要求，如果有<，则当然会需要==，如果有了+，则当然还可能有-,*和/.复合运算不仅进一步简化了代码的编写，给出更明确的语义，它也可以避免用户代码中基类链过长的问题。

operators库提供的常用复合运算概念如下：

- totally_ordered ： 全序概念，组合了equality_comparable和less_than_comparable:
- additive ：可加减概念，组合了addable和subtractable
- ...

使用复合链技术，point类只需要很少的代码就可以容易的获得完全的算术运算能力。

```c++
class point: totally_ordered<point, additive<point>>
{
public:
	friend bool operator<(const point& 1, const point& r)
    {
    	...;
    }
    
    friend bool operator==(const point& r)
    {
    	...;
    }
    
    point& operator+=(const point& r) // 支持addable概念
    {
    	x += r.x;
    	y += r.y;
    	z += z.y;
    	return *this;
	}
	
	...//等等
    
}；
```

验证代码

```c++
point p0, p1(1,2,3),p2(5,6,7),p3(3,2,1);
using namespace boost::assign;
vector<point> v = (list_of(p0),p1,p2,p3);

auto pos = std::find(v.begin(),v.end(),point(1,2,3)); // find算法使用operator==

pos->print();

(p1+p2).print();
(p3-p1).print();

```



point类很好地示范了复合运算操作符的用法：一般情况下，类型T继承boost::totally_ordered<T>，再定义<，==操作符即可获得完全的比较运算功能，能够用于标准容器和算法。



#### 相等和等价

相等是基于操作符== ，等价是基于<,即！(x<y) && !(x>y)

对于简单类型（如int)相等和等价是一致的，但是对于大多数复杂类型和自定义类型，由于==和<是两个不同的运算，比较原则可能不同，从而两者具有不同的意义

比如:point(1,2,3)和point(3,2,1)两者完全不相等，但等价，因为等价使用的是<,它比较的一句是成员变量的平方和。

了解相等和等价的区别非常重要，特别是自定义类被用做容器的元素的时候，标准库中的关联容器（如set，map）和排序算法使用的是等价关系的<操作符，而unordered_set/map和find查找算法使用到的是==操作符.