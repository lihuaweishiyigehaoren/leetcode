#### Array

**缺点**：

1.没有构造函数，不能指定大小和初始值，只能用模板参数指定大小，再用fill()填充值

2.没有push_back()和push_front()，因为他不能动态增长

3.不能搭配插入迭代器功能，同样因为它不能动态增长

**应用**：

只能应用在已知数组大小，或者对运行速度要求很高的场合。

```c++
    pub.subscribe(0, "res", 0);
    std::string topic;
    std::stringstream ss;
    std::string msg;
    cout<<"input 'topic msg' to send:"<<endl;
    do{
        ss<<“0”<<","<<"0"<<",";
        ss<<endl;
        ss>>msg;

        pub.publish(nullptr,
                    "/realtime",
                    msg.length(),
                    msg.c_str(),
                    0,
                    false
                    );

        Sleep(1);
    }while(true);
```

**初始化**：

```c++
array<string,3> ar = {"1","2","3"};
// 也可以只初始化部分元素，其余元素将调用缺省构造函数完成初始化。
array<int,10> ar = {0};

array<string,3> ar2 = {"racer"};
assert(ar2.at(1).empty()) 第二个元素缺省构造，是个空字符串
```

**接口**：

```c++
template<class T,std::size_t N>
class array{
	T elems[N];
    iterator begin(); // 迭代器
    iterator end(); 
    reverse_iterator rbegin();
}
```

具体可参阅：

<http://www.cplusplus.com/reference/array/array/>