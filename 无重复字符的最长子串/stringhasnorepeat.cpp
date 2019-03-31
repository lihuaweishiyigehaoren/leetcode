#include <iostream>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int count = 0;
        int len = s.length();
        while(len != 0){
            int diff = s.length()-len;
            for(int index=0;index<diff+1;index++)
            {
                for(int start=index;start<len+index;start++)
                {
                    // 判断字符是否重复
                    char a = s[start];
                    int init_count = 0;
                    for(int child_start=index;child_start<len+index;child_start++)
                    {
                        if(s[child_start]==a) init_count++;
                    }

                    if(init_count>1){
                        break;
                    }
                    else
                    {
                        if(start==len+index-1)
                        {
                            count = len;
                            len=1;
                            index = diff;
                            // 为什么要加这个break，我自己也很懵逼
                            break;
                        }
                    }
                }
            }
            len--;
        }
        return count;
    }
};

int main()
{
    Solution A;
    
    return 0;
}