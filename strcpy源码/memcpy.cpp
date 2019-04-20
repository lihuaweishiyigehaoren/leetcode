#include <iostream>
#include <assert.h>

// void memcpy(void* dest, const void* src,size_t count)
// {
//     assert(count>0 && dest != nullptr && src != nullptr);
//     while(count != 0)
//     {
//         *dest++ = *src++;
//         count--;
//     }
// }

void memcpy(void* dest, const void* src, size_t count)
{
    if(dest == NULL || src == NULL)
    {
        return;
    }

    void * ret = dest;
    
    // 没有内存重叠，从低到高复制
    if(dest <= src || (char *)dest >= (char*)src +count)
    {
        while(count--)
        {
            *(char*)dest++ = *(char*)src++;
        }
    }
    else
    {
        // 有内存重叠
        src = (char*)src + count-1;
        dest = (char*)dest +count-1;
        while(count--)
        {
            *(char*)dest-- = *(char*)src--;
        }
    }

    return ret;
}

int main()
{
    char a[5] = {"1","2","3","4","5"};
    char b[5];
    memcpy(b,a,5);
    for(int i = 0; i<5; i++)
    {
        std::cout<<b[i]<<std::endl;
    }
    return 0;
}