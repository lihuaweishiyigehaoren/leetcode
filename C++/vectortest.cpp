#include <iostream>
#include <vector>
using namespace std;

int main()
{

    vector<int *> a;

    int *a1 = new int(1);
    int *a2 = new int(2);
    int *a3 = new int(3);

    a.push_back(a1);
    a.push_back(a2);
    a.push_back(a3);

    for(int i = 0;i<a.size();i++)
    {
        delete a[i];                
    }

    a.clear();
    vector<int *>().swap(a);

    cout <<*a1 <<" "<< *a2 << " "<<*a3 <<endl;

    return 0;
}
