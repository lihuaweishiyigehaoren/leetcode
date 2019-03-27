#include <iostream>
// #include <Streams.h>
// #include <Wxdebug.h>
#include <assert.h>

char* strcpy(char* dst, const char* src)
{
    assert((dst != nullptr) || (src != nullptr));

    char* dest = dst;

    while((*dst++ = *src++) != '\0')
    {

    }

    return dest;

}

int main()
{
    // std::cout<< "helloworld" <<std::endl;
    char src[100] = "helloworld";
    char the[101];
    strcpy(the,src);
    std::cout<<*the<<std::endl;
    return 0;
}