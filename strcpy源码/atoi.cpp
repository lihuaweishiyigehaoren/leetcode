#include <iostream>
#include <string>

void select(char* t)
{
    std::cout << *t << std::endl;
}

int main()
{
    std::string a = "woshiie";

    select(a.c_str());
    

    return 0;
}