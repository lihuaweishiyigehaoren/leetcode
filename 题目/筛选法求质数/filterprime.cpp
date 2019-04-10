/*
从2开始的整数区间筛选法质数
*/

#include <boost/dynamic_bitset.hpp>
#include <iostream>
using namespace std;
using namespace boost;

int main()
{
    int n;
    cin >> n;
    dynamic_bitset<> db(n);

    
    // 使用set()置集合中的所有位标志
    db.set();

    // 筛选时跳过了0和1,因为他们既不是质数也不是合数,使用find_next()来查找集合中的元素,运用筛选法删除它的倍数
    for(dynamic_bitset<>::size_type i = db.find_next(1);
    i!=dynamic_bitset<>::npos;
    i=db.find_next(i))
    {

        // cout<< i <<endl;      
        // cout<< dynamic_bitset<>::npos <<endl;

        for(dynamic_bitset<>::size_type j = db.find_next(i);
        j != dynamic_bitset<>::npos;
        j = db.find_next(j))
        {
            cout<<i <<" "<< j <<endl; 
            if(j%i == 0)
            {
                db[j]=0; // 被整除,非质数
            }
        }
    }

    for(dynamic_bitset<>::size_type i = db.find_next(2);
    i != dynamic_bitset<>::npos;
    i = db.find_next(i))
    {
        cout<<i<<",";
    }

    cout << endl;
}
