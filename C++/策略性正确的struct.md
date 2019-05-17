### 策略性正确的struct

把单一元素的数组放在一个struct的尾部，于是每个struct object可以拥有可变大小的数组：

```c
struct mumble
{
    /*stuff*/
    char pc[1];
}

// 从文件或标准输入装置中取得一个字符串
// 然后为 struct 本身和该字符串配置足够的内存

struct mumble * pmub1 = (struct mumble*)malloc(sizeof(struct mumble) + strlen(string) + 1);
strcpy(&mumble.pc,string);
```

