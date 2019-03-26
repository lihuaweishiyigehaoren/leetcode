/*
*快排原理：从一组数组中任意选出一个数，将大于它的数放右边，小于它的数放左边
*然后再从左边和右边的两数组中分别执行此操作，直到数组中元素数为1，此时就是有序的
*/

#include <iostream>
#include <memory.h>

void printArray(int a[],int low, int high)
{
    for(int i = low; i < high; i++)
    {
        std::cout << a[i] <<" ";
    }
    std::cout<<std::endl;
}

void quickSorted(int b[], int low, int high)
{
    if(low >= high) return;

    int middle = (low+high)/2;
    std::cout<< middle<< std::endl;
    
    int copyB[high-low+1], start = low;
    for(int i = 0;i < high-low+1; i++)
    {
        copyB[i] = b[start];
        start++;
    }

    // printArray(copyB,0,high-low+1);

    int thisIndex = low;
    for(int i = low; i <high-low+1; i++)
    {
        if(copyB[i] < copyB[middle])
        {
            b[thisIndex] = copyB[i];
            thisIndex++;
        }
    }

    int whichindex = thisIndex;
    b[thisIndex] = copyB[middle];
    thisIndex++;

    for(int i = low; i<high-low+1;i++)
    {
        if(copyB[i] >= copyB[middle] && i!=middle)
        {
            b[thisIndex] = copyB[i];
            thisIndex++;
        }
    }

    // printArray(b,low,high+1);

    std::cout << "(" << low << "," << whichindex-1 << ")" <<std::endl;
    std::cout << "(" << whichindex+1 << "," << high << ")" <<std::endl;

    quickSorted(b,low,whichindex-1);
    quickSorted(b,whichindex+1,high);
}

int main()
{
    // std::cout<<"helloworld!"<<std::endl;

    int a[] = {1,5,6,3,5,6,8};

    quickSorted(a,0,6);
    
    // printArray(a,0,7);
    return 0;
}