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

	int count = 7; // 这里这样写返回的是int*报错了兄弟
	//std::cout<<count<<std::endl;
    int copyB[count];
	memcpy(copyB,b,count*sizeof(int));

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
    //std::cout<< whichindex<< std::endl;
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

    quickSorted(b,low,whichindex-1);
    quickSorted(b,whichindex+1,high);
}
int OnceSort(int arr[], int first, int end){
    int i = first,j = end;
    //当i<j即移动的点还没到中间时循环
    while(i < j){
        //右边区开始，保证i<j并且arr[i]小于或者等于arr[j]的时候就向左遍历
        while(i < j && arr[i] <= arr[j]) --j;
        //这时候已经跳出循环，说明j>i 或者 arr[i]大于arr[j]了，如果i<j那就是arr[i]大于arr[j]，那就交换
        if(i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        //对另一边执行同样的操作
        while(i < j && arr[i] <= arr[j]) ++i;
        if(i < j){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //返回已经移动的一边当做下次排序的轴值
    return i;
}

void QuickSort(int arr[], int first, int end){
    if (first < end) {
        int pivot = OnceSort(arr,first,end);
        //已经有轴值了，再对轴值左右进行递归
        QuickSort(arr,first,pivot-1);
        QuickSort(arr,pivot+1,end);
        }
}

int main()
{

    int a[] = {1,5,6,3,5,6,8};

    QuickSort(a,0,6);

    printArray(a,0,7);
    return 0;
}
