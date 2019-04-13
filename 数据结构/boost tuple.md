

### boost tuple

tuple(元组)定义了一个有固定数目元素的容器,其中的每个元素类型都可以不相同.这与其他容器有着本质的区别.

tuple很有用,它是std:::pair的泛化,可以从函数返回任意数量的值,也可以代替struct组合数据.



#### 头文件

```c++
#include <boost/tuple/tuple.hpp;
using namespace boost;
```



#### 最简单的tuple:pair

标准库提供的std::pair是tuple的特例:2-tuple-仅能持有两个成员的元组,了解pair有助于我们接下来tuple的学习.

pair的声明:

```c++
template <typename T, typename U>
struct pair
{
    T first;
    U second;
}
```

定义: pair<int,string> a_pair;

pair的两个成员可以分别用first和second来访问,它们可以是任意的类型,pair重载了所有比较操作符,因此只要元素支持比较,那么同型的对象之间可以进行比较操作.工厂函数make_pair()还可以根据参数自动推导类型,创建pair对象.

pair是标准库中很多组件的基础,例如关联容器map和multi_map就使用pair来保存不同元素之间的映射关系.boost库的很多组件也使用了pair.



#### tuple类摘要

tuple是pair的泛化,声明很类似于pair,具有容纳不同元素的功能,摘要如下:

```c++
template<class T0,...,class T9> // Boost未使用可变参数模板
class tuple
{
    public:
    tuple();
    tuple(T0 t0,...);
    tuple(const tuple&);
    
    tuple& operator=(const tuple&); // 赋值操作
    tuple& operator=(const std::pair&);
    
    template<int N> T get();
}
```

声明简单,但用法不简单



#### 创建和赋值

tuple 默认最多支持10个模板类型参数,也就是说最多容纳10个不同类型的元素(10-tuple),对于绝大多数应用来说这已经足够了.

tuple对元素的类型没有特殊的要求,但如果类型不支持缺省构造或者赋值操作,那么tuple也会相应地缺失功能.特别的,元素也可以是tuple,也就是说tuple支持嵌套定义,例如:

```c++
typedef tuple<int, string> my_tuple1;
typedef tuple<int, my_tuple1> my_tuple2;
```



单从类声明来看,tuple与pair很相似,只是模板参数由两个变成了10个,把多少不同类型的值"打包"为一个整体.tuple的构造函数与pair也差不多,可以直接输入N个值构造,或者从另一个tuple拷贝.例如:

```c++
typedef tuple<int,string,double> my_tuple; //3-tuple
my_tuple t1; // 全部元素使用缺省构造
my_tuple t2(1,"123"); // 第三个元素使用缺省构造
my_tuple t3(t1); // 拷贝构造
t2=t3; // 赋值操作
```



如果tuple的元素类型是引用,那么在初始化时必须给予初值:

```c++
int x = 10;
tuple<int&> t4(x);
```

如果没有初值引起编译错误,因为无法创建一个空的引用:

```c++
tuple<int&> t4;
```



也存在不能实例化的tuple类型,例如当元素类型是void或者函数类型(不是类型指针)的时候,因为这两种类型没有实例(绝不会有一个类型为void的变量),因此也就不存在相应的tuple对象:

```c++
typedef tuple<void> no_instance_t1; // 没有tuple实例
typedef tuple<double(int)> no_instance_t2; // 没有tuple实例
```



但指向void或者函数类型的指针是可以的:

```c++
tuple<void*> t1; // void*指针1-tuple对象
tuple<double(*)(int)> t2; // 函数指针1-tuple对象
```



#### make_tuple

make_tuple()方便创建tuple对象.

```c++
template<typename ... T>
tuple<T...> make_tuple(const T1& ...);

make_tuple(2,3.0); // tuple<int, double>
make_tuple(string(),vector<int>()); //tuple<string,vector<int>>
```

如果想让make_tuple生产的tuple数据类型是引用,那么要用到ref库的ref()和cref()函数,它们可以包装变量,使tuple的类型为T&或者从const T&,这在用于不可拷贝的数据类型时是很有用的:

```c++
int i ;
string s;
tuple<int ,string> t1 = make_tuple(i,ref(s));
tuple<const int &,string&> t2 = make_tuple(cref(i),ref(s));
```



#### 访问元素

get<>() 是tuple访问内部的值,超过tuple内部的元素个数则会导致编译错误.例如:

```c++
auto t = make_tuple(1,"char[]",100.0); // 3-tuple
assert(t.get<0>() == 1);
assert(t.get<2>() == 100.0);

cout<<t.get<1>(); // 第二个元素,const char 类型
cout<< ++t.get<0>();
```



在了解了get<>()用法之后,初学者往往会犯一个错误,企图像遍历数组那样用for循环打印出tuple的所有元素,写出如下的代码:

```c++
for(int i = 0;i<3;++i)
{
    cout<<t.get<i>();
}
```

**这段代码是无法通过编译的**,get<>()是一个模板函数,编译运行模板实例化时要求模板参数<int N>必须是编译器可确定的,而for循环中的变量i只能在运行时确定,因此无法变异模板代码--提供递归遍历tuple的方法.



#### boost::get<>()

```c++
auto t = make_tuple(1,"char[]",100.0);
get<0>(t);
get<1>(t);
```



#### 比较操作

tuple全面支持比较操作,包括相等和不等的各种测试,它将比较操作符转发到内部各个元素进行比较.因此要求tuple的元素必须能够执行比较操作,否则会引发编译错误.作为比较对象的两个tuple也必须有相同的元素个数,否则也会引发编译错误.

tuple的大小比较是基于"字典序"的,而且是"短路"操作,从第一个元素开始,一旦得出比较结果就停止比较操作.例如:

```c++
#include <boost/tuple/tuple_comparision.hpp>
using namespace boost;

int main()
{
    typedef tuple<int, double, string> my_tuple ; // 3-tuple
    
    my_tuple t1 = make_tuple(1, 100.0,string("abc"));
    my_tuple t2 = make_tuple(1,200.0 string("def"));
    assert(t1<t2);
    
    my_tuple t3(t2);
    assert(t2 == t3);
}
```



下面的代码定义了一个空类A,它没有定义比较操作,因此无法通过编译:

```c++
struct A{};
tuple<A> ta1,ta2; // 1-tuple
ta1 == ta2; // 编译错误
```



#### 输入输出

tuple 支持输入输出,与比较操作不同,对tuple内的所有元素诸葛调用operator<<或operator>>,因此要求每个元素都支持流输入输出,否则也会引发编译错误.

流输入输出头文件:<boost/tuple/tuple_io.hpp>

```c++
#include <boost/tuple/tuple_io.hpp>
using namespace boost;

int main()
{
 	typedef tuple<int ,double,string> my_tuple;
    my_tuple t1(1,2.0,"string");
    cout<<t1<<endl;// 输入输出格式为用圆括号包围,(1,2,string)
    
    cout<< "please input tuple";
    cin>>t1;
    
    cout<<t1 <<endl; //..
}
```



#### 联结变量

tuple 库提供了一个类似make_tuple()的函数tie(),正如名字,它可以把变量联结到tuple上,生成一个元素类型全是引用的tuple,相当于make_tuple(ref(a),ref(b),...),可以用于左值,如果有:

```c++
int i ;double d;
```

那么tie(i,d)将生成一个临时的tuple变量,其类型为tuple<int &,double&>.

tie()可以方便地利用现有普通变量创建一个可赋值的tuple对象,因此可以对tuple执行"解包"操作,这在接受返回tuple的函数返回值时特别有用:

```c++
#include <boost/tuple/tuple.hpp>
using namespace boost;
typedef tuple<int,double,string> my_tuple;

my_tuple func(){
	return make_tuple(1,2.0,"string");
}

int main()
{
    int i; double d; string s;
    tie(i,d,s) = func();// 3个普通变量
    cout<<i; /// 使用tie()接受函数返回的tuple
}
```



tie()不仅能够应用于tuple,它也可以应用于std::pair;

```c++
int i; string s;
tie(i,s) = make_pair(100,"abc");
```



tie()还有一个特殊的对象tuples::ignore, 它相当于一个占位符,可以在复制时"忽略"某些对象,在只关心tuple中极少数元素值的时候就可以使用,从而不必声明一堆必须声明又不用的变量.例如:下面的代码忽略了函数返回的int和string结果,只接受了double值.

```c++
double d;
tie(tuples::ignore,d,tuples::ignore) = func();
```



#### 应用assign库

tuple_list_of初始化

```c++
typedef tuple<int,double,string> my_tuple;
using namespace boost::assign;

vector<my_tuple> v = tuple_list_of(1,1.0,"123")(2,2.0,"abc");
assert(v.size()==2);
```



其他的assign库操作函数需要使用make_tuple()或者tie()函数来创建可插入容器的tuple对象,例如:

```c++
v += make_tuple(3,3.0,"789"), make_tuple(4,4.0,"abc");

assert(v.size() == 4);
```



#### 内部结构

内部结构是一个部件(cons)的链表,cons位于名字空间boost::tuples,它的声明如下:

```c++
template<typename Head,typename Tail>
struct cons
{
    typedef Head head_type; // 头类型
    typedef Tail tail_type; // 尾类型
    head_type head; // 链表头
    tail_type tail; // 链表尾
    
    head_ref get_head() { return head;}
    tail_ref get_tail() {return tail;}// 获取链表尾
}
```

通过cons的模板类型Head和Tail,tuple使用了类似operators库的基类链技术,通过链式继承实现类型的容纳,例如:

tuple<int,double,string>

概念上相当于:

cons<int,cons<double,cons<string,null_type>>>

基类链的末尾是一个null_type,它是一个空类,起到哨兵的作用,等价于tuple<>// 0-tuple



tuple 利用 cons提供了两个很有用的函数:get_head()和get_tail(),它们分别tuple首元素和尾部件链表的引用,使用它们就可以递归地访问tuple的元素.

无法使用循环来处理tuple元素,现在我们改用递归来处理,用一个get_head()和get_tail()函数实现遍历输出tuple内的元素.

```c++
template <typename>
void print_tuple(const Tuple & t)
{
    cout<<t.get_head()<<","; // 输出tuple首元素
    print_tuple(t.get_tail()); // 递归输出剩余的tuple元素
}
```



print_tuple()是一个模板函数,因此可以接受任意的tuple对象,它先用get_head()获得tuple的第一个元素,然后递归的处理尾部链表get_tail().为了使递归能够停止.我们必须有一个处理null_type的模板特化函数,它什么都不用做,只是用来终止递归过程.



#### 使用访问者模式

我们可以使用访问者模式来封装对tuple的递归操作.可以分离数据的表示与操作.由于C++中的模板类不能自动推导参数,而可自动参数的模板函数不支持偏特化,因此这个访问者并不完美.

访问者函数visit_tuple()泛化了tuple的递归操作,增加了一个模板参数visitor,它是一个函数对象,具有operator(),可以被调用.函数的返回值使用boost.result_of来实现推导.

```c++
template<typename Vistor, typename Tuple>
typename Vistor::result_type // Vistor的返回值类型
visit_tuple(Visitor v, const Tuple & t)
{
    v(t.get_head()); // 访问者对象访问tuple的首元素
    return visit_tuple(v,t.get_tail()); // 递归访问剩余元素
}
```

为了操作tuple,还需要编写一个函数对象,同print_tuple()类似,向标准输出打印元素值.

```c++
struct print_visitor // 一个访问者函数对象
{
    typedef void result_type; // 返回值类型定义
    template<typename T>
    retult_type operator()(const T &t) // 调用操作符重载
    {
        cout<<t<<","; // 简单的输出元素值
    }
};
```

为了终止递归,我们还必须写出visit_tuple()针对null_type的重载形式:

```c++
template<>
void visit_tuple(print_visitor , const tuples::null_type &)
{}

// 访问者模式可以这样使用:
tuple<int,double,string> t(1,2.1,"string visitor");
visit_tuple(print_visitor(),t);

// 代码将输出
1,2.1,string visitor
```





这里没懂,访问者模式也没懂,需要花时间看!



#### 高级议题

跟struct相比,性能相同,代码简介,但是可能会增加编译时间(泛型编程的通病).

**tuple辅助类** 

tuple库在boost::tuples名字空间中提供了两个辅助类(元函数)element<>和length<>,它们可以获得tuple的一些相关信息.

element<N,T>::type 可以给处T中第N个元素k