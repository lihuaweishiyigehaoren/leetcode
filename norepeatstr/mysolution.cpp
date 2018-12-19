/*
无重复字符串计算
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        /*理解错误，理解成无重复字符长度了*/
        // int count = 0;
        // string now = s;
        
        // while(now != "")
        // {
        //     string now_copy = "";
        //     for(unsigned int index=0;index<now.size();index=index+1)
        //     {
        //         char a = now[0];
        //         if(now[index]!=a){
        //             now_copy.push_back(now[index]);
        //         }              
        //     }
        //     now = now_copy;
        //     count++;
        // }
        
        // return count;
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

int main(){
    // string test_string = "pwwkew";
    //test2
    // string test_string = "abcabcbb";
    //test3
    string test_string = "bbbbbb";
    Solution a;
    int count = a.lengthOfLongestSubstring(test_string);
    cout<<count<<endl;
    return 0;
}