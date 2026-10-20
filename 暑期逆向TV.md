# 逆向TV-1

逆向TV之小白蠕动学习逆向

平台为NSSCTF，标题前为id

彩笔。。

## .2956[HNCTF 2022 WEEK2]e@sy_flower

题目描述：

我的IDA坏了???



题目提示为花指令

花指令即为了迷惑分析而在正常的代码中插入垃圾代码（不承担真实业务逻辑）干扰静态分析、甚至起到破坏反编汇的作用

https://blog.csdn.net/Sciurdae/article/details/133750478 这篇大佬的文章有花指令的介绍和处理方法

分析程序，在反汇编窗口找到爆红语句

![image-20260608201056510](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260608201056510.png)

上面有jz和jnz这一对互补跳转语句，结尾的地址都+1了

jz和jnz互补语句，不论条件是否成立程序都会从地址+1处开始执行，然而ida静态分析字节会从原地址开始分析，以致代码字节分割错位，造成反编译混乱

选中地址，Edit -> Patch program -> Change byte直接改字节码

![image-20260610081717888](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610081717888.png)

![image-20260610081832652](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610081832652.png)

既然它是地址+1，我们就把第一个字节给nop掉，让字节分割顺序恢复正常

（90一般是机器码的nop字节）

![image-20260610082133270](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610082133270.png)

恢复正常

![image-20260610082524153](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610082524153.png)

找到main函数，确定入口按p重建函数

![image-20260610083341573](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610083341573.png)

都恢复了，直接看伪码

![image-20260610083508975](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610083508975.png)

主要逻辑是这一段

![image-20260610084447575](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610084447575.png)

反写脚本

```
int main()
{
char v8[] = "c~scvdzKCEoDEZ[^roDICUMC";
signed int v3 = strlen(v8);
char v5;
    for (int j = 0; j < strlen(v8); ++j )
   {
    v8[j] ^= 0x30u;
   }
    for (int i = 0; i < v3 / 2; ++i )
  {
    v5 = v8[2 * i];
    v8[2 * i] = v8[2 * i + 1];
    v8[2 * i + 1] = v5;
  }
  printf("%s",v8);
}
```

![屏幕截图 2026-06-10 090723](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 090723.png)

NSSCTF{Just_junk_Bytess}

## .1127[MTCTF 2021]Random

ida看伪码

![image-20260610093231127](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260610093231127.png)

在异或随机数，建议动调

找点核心逻辑（异或）处下F2下断点，F9开始运行

![屏幕截图 2026-06-10 153927](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 153927.png)

输入任意字符串

![屏幕截图 2026-06-10 154238](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 154238.png)

Debugger -> Debugger windows -> General registers打开寄存器窗口，EAX会记录每一次的随机数值

![屏幕截图 2026-06-10 154456](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 154456.png)

运行到断点处，每一次EAX都寄存了不同的随机数值

![屏幕截图 2026-06-10 155112](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155112.png)

![屏幕截图 2026-06-10 155134](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155134.png)

![屏幕截图 2026-06-10 155154](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155154.png)

![屏幕截图 2026-06-10 155223](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155223.png)

不嫌麻烦的话可以手记

但我们可以右键断点处选择edit breakpoint

![屏幕截图 2026-06-10 155535](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155535.png)

点三个点

![屏幕截图 2026-06-10 155724](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155724.png)

粘贴c语言代码

```
msg("%02d: %08X\n", ESI, EAX);
return 0;
```

![屏幕截图 2026-06-10 155826](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 155826.png)

这样就可以把 ESI 和 EAX 按格式打印到 Output 窗口

![屏幕截图 2026-06-10 160559](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 160559.png)

不断运行直至结束

![屏幕截图 2026-06-10 160805](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 160805.png)

由前面的伪码可知有42个随机数

![屏幕截图 2026-06-10 153906](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 153906.png)

去除噪声，保留0~41位

> 00: 00000258
> 01: 000039A1
> 02: 000074CB
> 03: 000049E9
> 04: 000049ED
> 05: 0000682C
> 06: 000011EC
> 07: 000009FB
> 08: 000038E9
> 09: 00001EC4
> 10: 00001116
> 11: 00004797
> 12: 00004399
> 13: 000076B1
> 14: 000070A4
> 15: 000003E9
> 16: 000000C3
> 17: 000054C6
> 18: 00000B80
> 19: 000014BF
> 20: 0000073E
> 21: 00004F44
> 22: 00002D18
> 23: 00005C2E
> 24: 00006B73
> 25: 00000956
> 26: 00003752
> 27: 00000BB8
> 28: 0000635B
> 29: 00002066
> 30: 00007DED
> 31: 00005BBC
> 32: 00006C8A
> 33: 000067D8
> 34: 00005236
> 35: 0000478F
> 36: 000059E6
> 37: 00004ED3
> 38: 00002EB1
> 39: 00005F51
> 40: 000057B9
> 41: 00000159

由前面可知用的是al，只用aex的低8位，即最后两个字母

![屏幕截图 2026-06-10 153927](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-10 153927.png)

整理

> 58 A1 CB E9 ED 2C EC FB E9 C4 16 97 99 B1 A4 E9
> C3 C6 80 BF 3E 44 18 2E 73 56 52 B8 5B 66 ED BC
> 8A D8 36 8F E6 D3 B1 51 B9 59

密钥拿到了再与原密文逐项异或

![image-20260707133427334](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260707133427334.png)

![image-20260707133448504](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260707133448504.png)

脚本

```
int main() {
     char a[] = {
        0x3E, 0xCD, 0xAA, 0x8E, 0x96, 0x1F, 0x89, 0xCD,
        0xDB, 0xF1, 0x70, 0xF2, 0xA9, 0x9C, 0xC2, 0x8B,
        0xF2, 0xFE, 0xAD, 0x8B, 0x58, 0x7C, 0x2F, 0x03,
        0x4A, 0x65, 0x31, 0x89, 0x76, 0x57, 0x88, 0xDF,
        0xB8, 0xE9, 0x01, 0xE9, 0xDE, 0xE5, 0x86, 0x68,
        0x8F, 0x24
    };
     char b[] = {
        0x58, 0xA1, 0xCB, 0xE9, 0xED, 0x2C, 0xEC, 0xFB,
        0xE9, 0xC4, 0x16, 0x97, 0x99, 0xB1, 0xA4, 0xE9,
        0xC3, 0xC6, 0x80, 0xBF, 0x3E, 0x44, 0x18, 0x2E,
        0x73, 0x56, 0x52, 0xB8, 0x5B, 0x66, 0xED, 0xBC,
        0x8A, 0xD8, 0x36, 0x8F, 0xE6, 0xD3, 0xB1, 0x51,
        0xB9, 0x59
    };
    char c[43];

    for (int i = 0; i < 42; i++) {
        c[i] = a[i] ^ b[i];
    }

    c[42] = '\0';

    printf("%s\n", c);
    return 0;
}
```

flag{3e625fe0-fb18-4f87-93c1-1ec217f86796}

![image-20260707133122971](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260707133122971.png)

## .6522[GHCTF 2025]Canon

题目描述：Kanon und Gigue in D-Dur für drei Violinen und Basso Continuo

依旧ida看伪码

```
sub_140002470("Enter the flag: ", argv, envp);
  sub_1400024F0("%36s", Str);
  if ( strlen(Str) == 36 )
  {
    strncpy(Destination, Str, 0xCu);
    n12 = 12;
    Destination[12] = 0;
    strncpy(Str1, Source, 0xCu);
    n12_1 = 12;
    Str1[12] = 0;
    strncpy(Destination_, Source_, 0xCu);
    n12_2 = 12;
    Destination_[12] = 0;
    v15 = 0x500000001LL;
    n6 = 6;
    n3 = 3;
    n4 = 4;
    v19 = 1;
    n4_1 = 4;
    n5 = 5;
    v22[0] = 0;
    v22[1] = 1;
    v22[2] = 2;
    v11[0] = 0;
    v11[1] = 0;
    v11[2] = 0;
    for ( n8_1 = 0; n8_1 < 8; ++n8_1 )
    {
      for ( n2 = 0; n2 < 3; ++n2 )
      {
        if ( n8_1 >= v22[n2] )
        {
          n8 = v11[n2];
          if ( n8 < 8 )
          {
            if ( n2 )
            {
              if ( n2 == 1 )
              {
                sub_1400015D0(Str1, Destination_, *((unsigned int *)&v15 + n8));
              }
              else if ( n2 == 2 )
              {
                sub_1400015D0(Destination_, Destination, *((unsigned int *)&v15 + n8));
              }
            }
            else
            {
              sub_1400015D0(Destination, Str1, *((unsigned int *)&v15 + n8));
            }
            ++v11[n2];
          }
        }
      }
    }
    if ( !strcmp(Destination, "WgvDmssEvcY326bHo3nNro3vXvvfmgrz")
      && !strcmp(Str1, "gX+Ri9PG=bt5=00B6hscPQOL")
      && !strcmp(Destination_, "T6bHgUPL2gXUd=xT=FNHtPzV") )
    {
      sub_140002470("Congratulations! You have found the flag!\n", argv_1, envp_1);
    }
    else
    {
      sub_140002470("Invalid flag!\n", argv_1, envp_1);
    }
    return 0;
  }
  else
  {
    sub_140002470("Invalid flag!\n", argv_2, envp_2);
    return 0;
  }
}
```

一步一步来

![image-20260708090517940](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708090517940.png)

确认Str为36位长

![image-20260708090554556](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708090554556.png)

将Str分成Destination，Str1，Destination_三份，每份12位长

![image-20260708090838114](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708090838114.png)

结合前面对v22和v11的定义，这一段是用函数sub_1400015D0处理字符串，再取一数，循环8次



*((unsigned int *)&v15 + n8结合前面的定义

![image-20260708091236537](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708091236537.png)

v15 = 0x500000001LL 64位数，被int定义从8字节拆为4字节，分为5和1，小端存储按顺序就是1和5

相当于数组{1,5,6,3,4,1,4,5}8个数刚好对应前面的8次循环

即：

n2==0时，Destination为字符串，Str1为key，数组内取一数

n2==1时，Str1为字符串，Destination_为key，数组内取一数

n2==2时，Destination_为字符串，Destination为key，数组内取一数



![image-20260708092403924](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708092403924.png)

最后把校验的字符串给出来了



我们对函数sub_1400015D0进行分析

一个switch语句，给出了1~7的情况，前面的数组内没有2和7，不用管，分析1,3,4,5,6

```
v9 = strlen(p_Str1);
  v21 = strlen(Destination);
  switch ( a3 )
  {
    case 1:
      for ( i = 0; i < v9; ++i )
      {
        v22 = Destination[i % v21];
        if ( p_Str1[i] < 65 || p_Str1[i] > 90 )
        {
          if ( p_Str1[i] < 97 || p_Str1[i] > 122 )
          {
            if ( p_Str1[i] >= 48 && p_Str1[i] <= 57 )
              p_Str1[i] = (p_Str1[i] + v22 - 48) % 10 + 48;
          }
          else
          {
            p_Str1[i] = (p_Str1[i] + v22 - 97) % 26 + 97;
          }
        }
        else
        {
          p_Str1[i] = (p_Str1[i] + v22 - 65) % 26 + 65;
        }
      }
      break;
    case 2:
      v32[0] = 1;
      v32[1] = 3;
      v32[2] = 5;
      v32[3] = 7;
      v32[4] = 9;
      v32[5] = 11;
      v32[6] = 15;
      v32[7] = 17;
      v32[8] = 19;
      v32[9] = 21;
      v32[10] = 23;
      v32[11] = 25;
      for ( j = 0; j < v9; ++j )
      {
        if ( p_Str1[j] < 65 || p_Str1[j] > 90 )
        {
          if ( p_Str1[j] >= 97 && p_Str1[j] <= 122 )
            p_Str1[j] = (Destination[j % v21] + v32[j % 12] * (p_Str1[j] - 97)) % 26 + 97;
        }
        else
        {
          p_Str1[j] = (Destination[j % v21] + v32[j % 12] * (p_Str1[j] - 65)) % 26 + 65;
        }
      }
      break;
    case 3:
      v10 = *Destination % 10 + 2;
      v33 = v10;
      Block = malloc(saturated_mul(v10, 8u));
      for ( k = 0; k < v10; ++k )
      {
        Block[k] = malloc(v9 + 1);
        memset((void *)Block[k], 0, v9 + 1);
      }
      for ( m = 0; v10 * m < v9; ++m )
      {
        for ( n = 0; n < v10 && n + v10 * m < v9; ++n )
          *(_BYTE *)(Block[n] + m) = p_Str1[n + v10 * m];
      }
      v18 = 0;
      for ( ii = 0; ii < v10; ++ii )
      {
        for ( jj = 0; jj < m; ++jj )
        {
          if ( *(_BYTE *)(Block[ii] + jj) && v18 < v9 )
            p_Str1[v18++] = *(_BYTE *)(Block[ii] + jj);
        }
      }
      p_Str1[v18] = 0;
      for ( kk = 0; kk < v10; ++kk )
        free((void *)Block[kk]);
      free(Block);
      break;
    case 4:
      v25 = *Destination % 10 + 2;
      for ( mm = 0; mm < v25; ++mm )
      {
        v11 = p_Str1[v9 - 1];
        for ( nn = v9 - 1; nn > 0; --nn )
          p_Str1[nn] = p_Str1[nn - 1];
        *p_Str1 = v11;
      }
      break;
    case 5:
      v34 = v9;
      v26 = malloc(saturated_mul(v9, 4u));
      for ( i1 = 0; i1 < v9; ++i1 )
        v26[i1] = (Destination[i1 % v21] + 57) ^ p_Str1[i1];
      Source = sub_140001470((__int64)v26, v9);
      strcpy(p_Str1, Source);
      free(v26);
      free(Source);
      break;
    case 6:
      Size = saturated_mul(strlen(p_Str1), 4u);
      v27 = malloc(Size);
      sub_140001020((__int64)p_Str1, Destination, (__int64)v27);
      v4 = strlen(p_Str1);
      p_Str1_1 = sub_140001470((__int64)v27, v4);
      strcpy(p_Str1, p_Str1_1);
      free(v27);
      free(p_Str1_1);
      break;
    case 7:
      Size_1 = saturated_mul(strlen(p_Str1), 4u);
      v28 = malloc(Size_1);
      sub_140001250(p_Str1, Destination, v28);
      v6 = strlen(p_Str1);
      p_Str1_2 = sub_140001470((__int64)v28, v6);
      strcpy(p_Str1, p_Str1_2);
      free(v28);
      free(p_Str1_2);
      break;
  }
}
```

ps：函数sub_140001470（base64）

![image-20260708112702289](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708112702289.png)

函数sub_140001020（仿rc4）![image-20260708155609507](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708155609507.png)



最阴的来了，开头调用了一次函数sub_140001F60，是一段base64换表，往后偏移了20位

（多看汇编少看伪码）

![image-20260708173250386](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708173250386.png)

![image-20260708173510708](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260708173510708.png)



反写脚本（长脚本写出来一堆问题，写吐了，最后ai修了好多，尤其是rc4和换表那里）

```
#include<bits/stdc++.h>
using namespace std;

int mod26(int x){
    x %= 26;
    if(x < 0) x += 26;
    return x;
}

int mod10(int x){
    x %= 10;
    if(x < 0) x += 10;
    return x;
}

string base64_decode(const string &in) {
    string table = "stuvwxyz0123456789+/ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqr";
    vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[(unsigned char)table[i]] = i;

    string out;
    int val = 0, valb = -8;
    for (int i = 0; i < (int)in.size(); i++) {
        unsigned char c = (unsigned char)in[i];
        if (in[i] == '=') break;
        if (T[c] == -1) continue;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}
//一个base64解码的函数，后面会用到，这里要用换表后的base64

void rc4_init(int S[256], const char *Destination){
    int j = 0;
    int keylen = strlen(Destination);

    for (int i = 0; i < 256; ++i)
        S[i] = i;//定义并初始化s盒 

    for (int i = 0; i < 256; ++i)
    {
        j = (j + S[i] + (unsigned char)Destination[i % keylen]) % 256;
        swap(S[i], S[j]);
    }
}
//用来解仿rc4的函数 

void reverse_sub_1400015D0(char *p_Str1, const char *Destination, int a3)
{
    int i, j, k, ii, jj, kk, mm, nn, i1;
    int v9, v10, v11, v18, v21, v22, v25;
    char **Block;

    v9 = strlen(p_Str1);
    v21 = strlen(Destination);
    switch ( a3 )
    {
        case 1:
            for ( i = 0; i < v9; ++i )
            {
                v22 = (unsigned char)Destination[i % v21];
                if ( p_Str1[i] < 65 || p_Str1[i] > 90 )
                {
                    if ( p_Str1[i] < 97 || p_Str1[i] > 122 )
                    {
                        if ( p_Str1[i] >= 48 && p_Str1[i] <= 57 )
                            p_Str1[i] = mod10(p_Str1[i] - 48 - v22) + 48;
                    }
                    else
                    {
                        p_Str1[i] = mod26(p_Str1[i] - 97 - v22) + 97;
                    }
                }
                else
                {
                    p_Str1[i] = mod26(p_Str1[i] - 65 - v22) + 65;
                }
            }
            break;
            //+ v22全部改成- v22 

        case 3:
        {
            v10 = (unsigned char)*Destination % 10 + 2;
            int rows = (v9 + v10 - 1) / v10;
            int rem = v9 % v10;
            int pos = 0;

            Block = (char **)malloc(v10 * sizeof(char *));
            for ( k = 0; k < v10; ++k )
            {
                Block[k] = (char *)malloc(rows + 1);
                memset(Block[k], 0, rows + 1);
            }

            for ( k = 0; k < v10; ++k )
            {
                int len;
                if ( rem == 0 || k < rem )
                    len = rows;
                else
                    len = rows - 1;

                for ( j = 0; j < len; ++j )
                    Block[k][j] = p_Str1[pos++];
            }

            v18 = 0;
            for ( ii = 0; ii < rows; ++ii )
            {
                for ( jj = 0; jj < v10; ++jj )
                {
                    if ( Block[jj][ii] && v18 < v9 )
                        p_Str1[v18++] = Block[jj][ii];
                }
            }

            p_Str1[v18] = 0;
            for ( kk = 0; kk < v10; ++kk )
                free(Block[kk]);
            free(Block);
            break;
        }
            //原来是按行读，按列输出，反写为按列读，按行输出 

        case 4:
            v25 = (unsigned char)*Destination % 10 + 2;
            for ( mm = 0; mm < v25; ++mm )
            {
                v11 = p_Str1[0];
                for ( nn = 0; nn < v9 - 1; ++nn )
                    p_Str1[nn] = p_Str1[nn + 1];
                p_Str1[v9 - 1] = v11;
            }
            break;
            //指针循环右移,把循环里的顺序反过来 ,子循环改为逐增,nn-1改为nn+1 

        case 5:
        {
            string tmp = base64_decode(p_Str1);   // 前面的解码函数
            for (i1 = 0; i1 < (int)tmp.size(); ++i1)
                p_Str1[i1] = (unsigned char)tmp[i1] ^ (((unsigned char)Destination[i1 % v21] + 57) & 0xFF);
            p_Str1[tmp.size()] = 0;
            break;
        }
            //sub_140001470是base64编码的函数。这一段是xor+base64 

        case 6:
        {
            string tmp = base64_decode(p_Str1);//解base64 
            int S[256];
            rc4_init(S, Destination);

            int x = 0, y = 0;
            for (i = 0; i < (int)tmp.size(); ++i)
            {
                x = (x + 1) % 256;
                y = (y + S[x]) % 256;
                swap(S[x], S[y]);

                int t = S[(S[x] + S[y]) % 256];
                p_Str1[i] = (unsigned char)((((unsigned char)tmp[i] - 57 + 256) % 256) ^ t);
            }
            p_Str1[tmp.size()] = 0;
            break;
        }
            //原函数是rc4，异或+57，base64编码 （函数sub_140001020是仿rc4再异或再+57） 
    }
}

int main() {
    char Destination[256] = "WgvDmssEvcY326bHo3nNro3vXvvfmgrz";
    char Str1[256] = "gX+Ri9PG=bt5=00B6hscPQOL";
    char Destination_[256] = "T6bHgUPL2gXUd=xT=FNHtPzV";

    int a[] = {1,5,6,3,4,1,4,5};
    int v22[] = {0,1,2};
    int v11[] = {7,6,5};

    for (int n8_1 = 7; n8_1 >= 0; --n8_1)
    {
        for (int n2 = 2; n2 >= 0; --n2)
        {
            if ( n8_1 >= v22[n2] && v11[n2] >= 0 )
            {
                if ( n2 == 2 )
                {
                    reverse_sub_1400015D0(Destination_, Destination, a[v11[n2]]);
                }
                else if ( n2 == 1 )
                {
                    reverse_sub_1400015D0(Str1, Destination_, a[v11[n2]]);
                }
                else
                {
                    reverse_sub_1400015D0(Destination, Str1, a[v11[n2]]);
                }
                --v11[n2];
            }
        }
    }
	//仿制主函数写一个循环 
    printf("%s%s%s", Destination, Str1, Destination_);
    return 0;
}

```

（本来想着分三次出结果，但是Str1,Destination，Destination_都会变，只能写一坨、仿制主函数套个循环了）

![image-20260709091701011](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709091701011.png)

NSSCTF{P4ch3Lbel's_C@n0n_1n_D_mAjOr}



ps：另外标题的Canon应该指的是卡农的复调技法

Destination，Str1，Destination_好比三个声部，依次进入同一个循环（按时间依次进入同一段旋律）

此外{1,5,6,3,4,1,4,5}是和弦级数1-5-6m-3m-4-1-4-5，是D大调卡农里低音声部循环和弦D-A-Bm-F#m-G-D-G-A

## .7032[VNCTF 2025]Fuko's starfish

一个exe一个dll

![image-20260709152319257](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709152319257.png)

进程序加载dll，过完剧情进函数sub_140001490

![image-20260709152444808](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709152444808.png)

函数sub_140001270为第一关逻辑

![image-20260709152758960](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709152758960.png)

逻辑为10次以内猜到在1~100的一个随机数（要调试就在寄存器里抓，要玩也可以二分法7步以内过）



接下来看第二关逻辑play_snake，在dll里

是一个贪吃蛇游戏

![image-20260709154733348](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709154733348.png)

通关后进入函数sub_1800025F0，然而这个函数是空的

![image-20260709154841921](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709154841921.png)

而我们按流程走发现有第三关，开头的提示也是有三关

![image-20260709154951230](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709154951230.png)

搜索字符串找到u win，找到其汇编地址

![image-20260709161828406](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709161828406.png)

翻到底下找到sub_1800025F0的汇编地址

![image-20260709161925527](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709161925527.png)

互相跳转，经典花指令

![image-20260709162036406](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260709162036406.png)

选中jz那一句

![屏幕截图 2026-07-10 093819](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-10 093819.png)

第一句改成jmp，第二句nop



![屏幕截图 2026-07-10 093842](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-10 093842.png)

![屏幕截图 2026-07-10 093942](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-10 093942.png)

爆红的地方按U取消定义

![屏幕截图 2026-07-10 094320](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-10 094320.png)

汇编里找到push rax改成jmp loc_180002666确定边界

最后Edit -> Functions -> Delete function删除函数，找到sub_1800025F0 开头，按P重建函数



正常看到sub_1800025F0的伪码

```
void __noreturn sub_1800025F0()
{
  size_t i; // rdi
  __int64 v1; // rcx
  __int64 v2; // rax
  const char *right; // rcx
  _BYTE n8[16]; // [rsp+20h] [rbp-60h] BYREF
  __int128 v5; // [rsp+30h] [rbp-50h]
  char Str[16]; // [rsp+90h] [rbp+10h] BYREF
  _BYTE v7[30]; // [rsp+A0h] [rbp+20h]
  __int128 v8; // [rsp+C0h] [rbp+40h]
  char v9; // [rsp+D0h] [rbp+50h]
  _BYTE v10[31]; // [rsp+D1h] [rbp+51h] BYREF
  char v11; // [rsp+F0h] [rbp+70h]
  __int128 v12; // [rsp+100h] [rbp+80h] BYREF
  unsigned __int8 v13; // [rsp+110h] [rbp+90h]

  *(_OWORD *)&v7[14] = *(__int128 *)((char *)&xmmword_18000A9C0 + 14);
  *(_OWORD *)v7 = xmmword_18000A9C0;
  *(_OWORD *)Str = xmmword_18000A9B0;
  for ( i = 0; strlen(Str) > i; ++i )
    Str[i] ^= 0x17u;
  puts(Str);
  sub_180002780(v1, n8);
  v11 = 0;
  v12 = 0;
  v13 = 0;
  *(_OWORD *)&v10[15] = v5;
  sub_180001650(&v10[15], &v12);
  v5 = 0;
  sub_180001650(n8, &v10[15]);
  v9 = v11;
  v8 = *(_OWORD *)&v10[15];
  *(_OWORD *)v10 = v12;
  *(_WORD *)&v10[16] = v13;
  v2 = 0;
  while ( *((_BYTE *)&v8 + 2 * v2) == byte_18000A890[2 * v2]
       && *((_BYTE *)&v8 + 2 * v2 + 1) == byte_18000A890[2 * v2 + 1] )
  {
    if ( ++v2 == 16 )
    {
      right = "right!";
      goto LABEL_10;
    }
  }
  right = "wrong";
LABEL_10:
  puts(right);
  Sleep(0xFA0u);
  exit(0);
}

```

v2 *2，要处理32个字节

![image-20260710113648906](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260710113648906.png)

要校验的密文在byte_18000A890（正好32字节）

![image-20260710113538422](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260710113538422.png)

校验逻辑是函数sub_180001650

反复*2和异或，有点像aes

![image-20260713092240163](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713092240163.png)

反复在查表byte_18000A8B0

![image-20260713093316652](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713093316652.png)

搜索了解到开头63 7C 77 7B F2 6B 6F C5 ...是aes的s盒特征

![image-20260713093413480](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713093413480.png)

开头定义了16个key字节，对应aes128中16位key

![image-20260713094104359](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713094104359.png)

找到对应字节，但是发现960，962，970没有数，初始值未知

![image-20260713094320195](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713094320195.png)

![image-20260713094428920](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713094428920.png)

没思路了，回到dllmain

搜索了解到if ( fdwReason == 1 )是dll被加载时的情况

这里创建了一个线程函数ThreadProc（其实经验丰富的话可以反应过来第一步就应该看ThreadProc）

![image-20260713105318462](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713105318462.png)

单看ThreadProc的伪码一头雾水

![image-20260713151011640](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713151011640.png)

他的明文是固定的，那么key肯定是固定的，rand()本身就是伪随机，需要看设立的状态

依旧多看汇编少看伪码

不知为何这一段伪码没写出来

![image-20260713152054661](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713152054661.png)

这一段翻译过来就是srand(114514) （1BF52h十六进制转十进制为114514）

srand设立了一个状态，种子为114514，相当于把rand()随机数的调用给固定了



再看下面，结合伪码中的v+v/255

cl是取字节的最后8位，就相当于x%255

![image-20260713155540075](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713155540075.png)

再回到之前的校验函数sub_180001650

![image-20260713160239625](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713160239625.png)

总结逻辑：srand(114514)种子下取16次rand()-->%255-->^0x17

求key脚本

```
int main(){
  int key[16];
  srand(114514);
  for(int i=0;i<16;i++){
   key[i] = rand()%255;
   key[i] ^= 0x17;  	
  }
  
  for(int i=0;i<16;i++){  
  	printf("%x",key[i]);
  }
  
  	return 0;	
} 
```

9e5fdeb683175b6b13b84891eb78d2

![image-20260713161811232](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260713161811232.png)

之前分析过是AES128

要校验的密文在byte_18000A890

![image-20260710113538422](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260710113538422.png)

填入key和密文，模式选ECB/NoPadding（没有iv选ECB，key是16字节的倍数的话就不用改变其填充）

![image-20260710170655639](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260710170655639.png)

VNCTF{W0w_u_g0t_Fuk0's_st4rf1sh}

# .7309[SWPUCTF 2025 秋季新生赛]ez_tea

从start开始一路跳到sub_140013D60

一个key：1145141919810!!!

与目标密文byte_140020000

![image-20260715110808487](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260715110808487.png)

看校验函数sub_140011483再一路跳到sub_140014500

这一段已经有TEA的特征了

> v11 = (DWORD *)(i + a1);
> v12 = (DWORD *)(a1 + i + 4);

这段是把每8个字节拆成两个4字节再进行处理

![image-20260715150546204](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260715150546204.png)

从sub_14001132F再一路跳到sub_1400138B0

![image-20260715152045015](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260715152045015.png)

额到这里我以为已经出来了，反写完脚本发现是乱码



在call    cs:IsDebuggerPresent下断点（IsDebuggerPresent是判断是否在进行反调试的函数）

![image-20260715165607408](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260715165607408.png)

直接运行被拦截了

![屏幕截图 2026-07-15 172716](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-15 172716.png)

搜字符串发现另一处调用的地点：sub_7FF7F8152B90（运行时地址会变，直接看后面四位左右是一样的）

![image-20260716092730499](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716092730499.png)

![image-20260716093616226](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716093616226.png)

但下了断点发现停不到位置，改用patch

sub_7FF7F8152B90把jz改成jmp

![image-20260716103903069](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716103903069.png)

![image-20260716103944030](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716103944030.png)

sub_7FF689E83D60同理

![image-20260716104051779](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716104051779.png)

ctrl alt b打开断点窗口，把断点都删掉

![image-20260716105814133](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716105814133.png)

结果还是一如既往的弹窗拦截，

红温了把调用了IsDebuggerPresent的全部nop掉还是一样

那应该不只有IsDebuggerPresent这一条反调试



（后来发现是在sub_140014500里有变化key）



换个思路在Imports里面找到弹窗函数

![image-20260716150528710](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716150528710.png)

查看调用

![image-20260716150814678](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716150814678.png)

一路追到sub_140011285

![image-20260716151943599](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716151943599.png)

跳板函数，找调用

![image-20260716152613195](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716152613195.png)

把jz改成jmp（前两个要改，最后一个原本就是jmp）

![image-20260716153617451](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716153617451.png)

![image-20260716153702546](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716153702546.png)

之后运行，发现弹窗没了，可以正常输入数字了

![image-20260716154052554](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716154052554.png)

sub_140014500里下断点

![image-20260716161000297](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716161000297.png)

运行，随便输一串字符，回车

寄存器里的key不是前面的114514，果然被改了

![image-20260716161254497](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716161254497.png)

key：13C67E4E4E137172



接下来针对魔改TEA去写脚本

（自己写的脑袋尖尖的，最后ai改的基本上没有手写的成分了。。）

```
#define DELTA  0x0D000721u
#define ROUNDS 32

uint32_t key[4];

/*
 * 从小端字节序读取 4 字节整数。
 * 逆向里 _DWORD * 强转通常就是按 4 字节小端读取。
 */
uint32_t read_u32_le(const unsigned char *p) {
    return ((uint32_t)p[0])
         | ((uint32_t)p[1] << 8)
         | ((uint32_t)p[2] << 16)
         | ((uint32_t)p[3] << 24);
}

/*
 * 把 32 位整数按小端字节序写回内存。
 */
void write_u32_le(unsigned char *p, uint32_t x) {
    p[0] = x & 0xff;
    p[1] = (x >> 8) & 0xff;
    p[2] = (x >> 16) & 0xff;
    p[3] = (x >> 24) & 0xff;
}

/*
 * sub_1400138B0 的逆过程。
 *
 * 原加密逻辑大概是：
 *   sum += DELTA;
 *   v0 += (v1 >> 5) ^ (key[(sum >> 11) & 3] + (v1 << 4));
 *   v1 += (v0 >> 5) ^ (key[((sum >> 11) ^ 1) & 3] + (v0 << 4));
 *
 * 逆向解密时：
 *   1. sum 从 DELTA * 32 开始
 *   2. 先逆 v1
 *   3. 再逆 v0
 *   4. sum -= DELTA
 */
void decrypt_block(unsigned char *block) {
    uint32_t v0 = read_u32_le(block);
    uint32_t v1 = read_u32_le(block + 4);
    uint32_t sum = DELTA * ROUNDS;

    for (int i = 0; i < ROUNDS; i++) {
        uint32_t idx2 = (((sum >> 11) & 0xff) ^ 1) & 3;
        v1 -= (v0 >> 5) ^ (key[idx2] + (v0 << 4));

        uint32_t idx1 = (sum >> 11) & 3;
        v0 -= (v1 >> 5) ^ (key[idx1] + (v1 << 4));

        sum -= DELTA;
    }

    write_u32_le(block, v0);
    write_u32_le(block + 4, v1);
}

/*
 * sub_140013320 的逆过程。
 *
 * 原程序在加密前会先改输入。
 * 偶数长度时：
 *   s[i]     = (s[i] + 1) ^ 0x72;
 *   s[i + 1] = (s[i + 1] - 2) ^ 0x02;
 *
 * 所以逆过程是：
 *   s[i]     = (s[i] ^ 0x72) - 1;
 *   s[i + 1] = (s[i + 1] ^ 0x02) + 2;
 */
void reverse_input_mutation(unsigned char *buf, int len) {
    for (int i = 0; i < len; i += 2) {
        buf[i] = ((buf[i] ^ 0x72) - 1) & 0xff;
        buf[i + 1] = ((buf[i + 1] ^ 0x02) + 2) & 0xff;
    }
}

int main() {
    /*
     * byte_140020000，程序里拿加密结果和它比较。
     */
    unsigned char enc[] = {
        0xE8,0x1C,0xEB,0xDD,0x91,0x66,0x69,0x46,
        0xFD,0xF5,0xBA,0x47,0xED,0x25,0xB6,0x73,
        0x99,0xC4,0x3D,0xFD,0xFB,0x7E,0x9E,0x01,
        0x40,0x73,0xF8,0x9B,0xB4,0x48,0x8B,0xF2,
        0x5A,0xBE,0x7F,0xC0,0x6E,0xBE,0x40,0xD2,
        0x6B,0xFF,0x91,0xB0,0xF8,0x0B,0x0F,0x7D
    };

    /*
     * 动调在 sub_140014500 入口看到的真实 key。
     * 静态的 "1145141919810!!!" 是误导。
     */
    unsigned char key_bytes[] = "13C67E4E4E137172";

    /*
     * 原程序把 key 当作 4 个 DWORD 使用。
     */
    for (int i = 0; i < 4; i++) {
        key[i] = read_u32_le(key_bytes + i * 4);
    }

    int enc_len = sizeof(enc);

    /*
     * 先对全部密文按 8 字节分组解密。
     */
    for (int i = 0; i < enc_len; i += 8) {
        decrypt_block(enc + i);
    }

    /*
     * 程序比较的是 v6 + 4 字节，所以密文末尾可能带调试填充/多余数据。
     * 这里枚举偶数长度，找到以 } 结尾的可打印结果。
     */
    for (int n = 2; n <= enc_len; n += 2) {
        unsigned char tmp[64];

        memcpy(tmp, enc, n);
        tmp[n] = 0;

        reverse_input_mutation(tmp, n);

        if (tmp[n - 1] == '}') {
            printf("%s\n", tmp);
        }
    }

    return 0;
}

```

![image-20260716165456432](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260716165456432.png)

NSSCTF{13ce5888-01b4-4287-8593-eb975ab6cf6a}



## .6526[GHCTF 2025]FishingKit

主函数找到第一关sub_140001150

![image-20260722112242000](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722112242000.png)

有15个线性方程

![image-20260722113818709](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722113818709.png)

用z3去求解多元方程，比较轻便，然后输出字符

```
from z3 import *

buf = [Int(f"buf_{i}") for i in range(10)]
s = Solver()

# buf 是 unsigned __int8，所以范围是 0~255
# 这里再限制成可打印字符，方便得到字符串
for i in range(10):
    s.add(buf[i] >= 32)
    s.add(buf[i] <= 126)

s.add(-17*buf[4] + 216*buf[5] - 268*buf[6] + 202*buf[8] - 330*buf[9] == -14982)

s.add(195*buf[0] + 101*buf[1] - 530*buf[6] + 325*buf[8] == 22606)

s.add(489*buf[1] + 105*buf[2] + 367*buf[3] - 135*buf[4] + 480*buf[6] - 482*buf[9] == 63236)

s.add(-177*buf[0] + 493*buf[1] - 121*buf[2] - 80*buf[4] - 253*buf[8] - 243*buf[9] == -39664)

s.add(-352*buf[4] - 72*buf[5] + 271*buf[6] + 473*buf[7] == 14255)

s.add(286*buf[0] + 442*buf[1] + 483*buf[2] - 351*buf[4] + 196*buf[7] - 495*buf[8] == 41171)

s.add(-150*buf[2] - 261*buf[6] + 283*buf[7] - 329*buf[8] - 429*buf[9] == -90284)

s.add(-225*buf[1] - 31*buf[2] + 92*buf[4] + 456*buf[5] + 592*buf[7] == 88447)

s.add(237*buf[0] + 8*buf[2] + 216*buf[6] + 278*buf[7] + 221*buf[9] == 83838)

s.add(-422*buf[0] + 121*buf[1] - 64*buf[4] + 370*buf[7] + 127*buf[9] == 26467)

s.add(90*buf[1] + 262*buf[2] + 301*buf[8] + 166*buf[9] == 88247)

s.add(355*buf[0] - 62*buf[3] + 282*buf[4] - 167*buf[5] + 359*buf[8] + 44*buf[9] == 76658)

s.add(-85*buf[1] - 39*buf[2] - 277*buf[5] + 488*buf[6] + 379*buf[9] == 35398)

s.add(40*buf[0] - 241*buf[1] + 281*buf[4] + 217*buf[5] - 716*buf[7] == -35436)

s.add(579*buf[1] + 870*buf[3] - 133*buf[7] + 96*buf[8] == 157448)

if s.check() == sat:
    m = s.model()

    ans = ""
    for i in range(10):
        value = m.evaluate(buf[i]).as_long()
        print(f"buf[{i}] = {value} -> {chr(value)}")
        ans += chr(value)

    print("answer =", ans)
else:
    print("unsat")
```

运行结果（记得装库 pip install z3-solver）

![image-20260722153147573](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722153147573.png)

去程序里试发现正确

![image-20260722114000507](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722114000507.png)

走第二关sub_140002460

![image-20260722153728312](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722153728312.png)

rc4-like，逻辑是rc4后再异或

![image-20260722155356557](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722155356557.png)

密文在下面的Str2

![image-20260722155756308](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722155756308.png)

厨子解出来是NSSCTF{Fake!Fake!Fake!}

。。。

![image-20260722160651072](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722160651072.png)

继续思考，汇编里是通过strcmp的返回值来决定是否进行跳转的

![image-20260722162844229](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722162844229.png)

call    strcmp下断点调试，输入前两关的答案来到strcmp，按F7单步单入进入hook函数，再按一次F7进入hook跳转的函数

![屏幕截图 2026-07-22 170226](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-22 170226.png)

跳到了一个陌生函数sub_7FF79C4F1CE0，也就是被hook了

![image-20260722170930649](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722170930649.png)

还有第二种方法找hook函数

因为代码原本是不可写，直接修改代码加hook会使程序无法运行

但如果用VirtualProtect修改内存的访问权限，将代码修改为可写，就能对程序进行修改

我们搜索字符串VirtualProtect，查找其交叉调用

![image-20260723092210314](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260723092210314.png)

hook函数sub_7FF79C4F1C00

![image-20260723092533043](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260723092533043.png)

查看sub_7FF79C4F1C00的调用

![image-20260723093457283](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260723093457283.png)

同样找到sub_7FF79C4F1CE0

![image-20260723093635072](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260723093635072.png)

接下来分析该函数

魔改tea

![image-20260722171827412](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722171827412.png)

密文

![image-20260722172101279](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722172101279.png)

![image-20260722172116745](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722172116745.png)

脚本

```
unsigned int r(unsigned char *a) {
    return a[0] |
           (a[1] << 8) |
           (a[2] << 16) |
           (a[3] << 24);
}

void w(unsigned char *a, unsigned int b) {
    a[0] = b;
    a[1] = b >> 8;
    a[2] = b >> 16;
    a[3] = b >> 24;
}

int main() {
    unsigned char a[20] = "DeluxeBait";

    unsigned char b[25] = {
        0x21, 0x56, 0x97, 0xa6, 0x1a, 0xd5, 0xc4, 0xde,
        0xa4, 0x9c, 0x82, 0x4d, 0xd1, 0x45, 0xc8, 0x56,
        0xa7, 0xb4, 0x96, 0x5c, 0x4d, 0x49, 0x87, 0x20,
        0
    };

    unsigned int c[4];

    for (int i = 0; i < 4; i++)
        c[i] = r(a + i * 4);

    for (int i = 0; i < 24; i += 8) {
        unsigned int d = r(b + i);
        unsigned int e = r(b + i + 4);
        unsigned int f = 0x66778899u * 24;

        for (int j = 0; j < 24; j++) {
            e -= (c[(f >> 11) & 3] + f) ^ (d + ((d >> 5) ^ (16 * d)));
            f -= 0x66778899u;
            d -= (c[f & 3] + f) ^ (e + ((e >> 5) ^ (16 * e)));
        }

        w(b + i, d);
        w(b + i + 4, e);
    }

    printf("%s\n", b);
    return 0;
}

```

![image-20260722172837040](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260722172837040.png)

NSSCTF{Wh@t_@_b1g_F1sh}

## .6525[GHCTF 2025]ASM?Signin!

汇编代码

有两个数据，后面可能会用到

![image-20260728103150097](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260728103150097.png)

START会执行DO1和ENC

![image-20260728103658816](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260728103658816.png)

DO1确定函数循环8次，SWAP_LOOP确定逻辑：每四个字节前后交换（会有回绕，SI=24时第六组与第零组交换，跳过第七组。第七组同理）

![image-20260728110411828](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260728110411828.png)

例如：

data1数据：

> G0 = 26 27 24 25
> G1 = 2A 2B 28 00
> G2 = 2E 2F 2C 2D
> G3 = 32 33 30 00
> G4 = 36 37 34 35
> G5 = 3A 3B 38 39
> G6 = 3E 3F 3C 3D
> G7 = 3F 27 34 11

处理

> 第1轮 SI=0,  DI=4   => G0 <-> G1
> 第2轮 SI=4,  DI=8   => G1 <-> G2
> 第3轮 SI=8,  DI=12  => G2 <-> G3
> 第4轮 SI=12, DI=16  => G3 <-> G4
> 第5轮 SI=16, DI=20  => G4 <-> G5
> 第6轮 SI=20, DI=24  => G5 <-> G6
> 第7轮 SI=24, DI=0   => G6 <-> G0
> 第8轮 SI=28, DI=4   => G7 <-> G1

 变成

> 26 27 24 25
> 3F 27 34 11
> 32 33 30 00
> 36 37 34 35
> 3A 3B 38 39
> 3E 3F 3C 3D
> 2A 2B 28 00
> 2E 2F 2C 2D

后面的DO2相当于去调用前面的内容对data1进行真正的修改



接下来看ENC

![image-20260728153153017](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260728153153017.png)

SI跳过前两个控制字节指向输入内容

DI指向刚刚变化的data1

CX设置循环为8次



LOOP2将输入与key都分为每4字节一组

data1连续用key异或SI+1两次，异或SI+2两次

即

> ```
> for (int i = 0; i < 8; i++) {
>     input[0] ^= DATA1[1];
>     input[1] ^= DATA1[2];
>     input[2] ^= DATA1[2];
>     input[3] ^= DATA1[3];
> 
>     input += 4;
>     DATA1 += 4;
> ```

脚本

```
int main() {
    unsigned char d1[32] = {
        0x26,0x27,0x24,0x25,0x2A,0x2B,0x28,0x00,
        0x2E,0x2F,0x2C,0x2D,0x32,0x33,0x30,0x00,
        0x36,0x37,0x34,0x35,0x3A,0x3B,0x38,0x39,
        0x3E,0x3F,0x3C,0x3D,0x3F,0x27,0x34,0x11
    };

    unsigned char d2[32] = {
        0x69,0x77,0x77,0x66,0x73,0x72,0x4F,0x46,
        0x03,0x47,0x6F,0x79,0x07,0x41,0x13,0x47,
        0x5E,0x67,0x5F,0x09,0x0F,0x58,0x63,0x7D,
        0x5F,0x77,0x68,0x35,0x62,0x0D,0x0D,0x50
    };

    for (int si = 0; si < 32; si += 4) {
        int di = si + 4;
        if (di >= 28) di -= 28;

        for (int i = 0; i < 4; i++) {
            unsigned char t = d1[si + i];
            d1[si + i] = d1[di + i];
            d1[di + i] = t;
        }
    }

    for (int i = 0; i < 32; i += 4) {
        putchar(d2[i]     ^ d1[i + 1]);
        putchar(d2[i + 1] ^ d1[i + 2]);
        putchar(d2[i + 2] ^ d1[i + 2]);
        putchar(d2[i + 3] ^ d1[i + 3]);
    }

    putchar('\n');
    return 0;
}
```

![image-20260728163222525](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260728163222525.png)

NSSCTF{W0w_y0u're_g00d_@t_@5M!!}



## .6799[LitCTF 2025]Robbie Wanna Revenge

题目描述

> 2023年的那个秋天，Robbie飞天出Flag... 吸收了上次的经验，这次Designer决定用IL2Cpp编译游戏程序，你还能够通过你高超的逆向技术来找到Flag吗？
>
> （关策他说估计把每个地方都设计成极限情况才能通过，所以一直都很期待有人能玩出Flag的）

一个2D横版闯关游戏，显然不开桂通不了关

第一种方法试着玩通关

CE启动

先说结论，来个最简单的办法，

激活mono，分析mono

![image-20260731112631400](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731112631400.png)

按图里路径点Execute/Invoke method，调用玩家胜利的函数直接拿flag

![image-20260731112830561](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731112830561.png)

![image-20260731113036290](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731113036290.png)

后面是来时路）：

一开始试着改坐标通关，因为坐标的地址好筛一点，左右上下动然后按“增加的数据”“减少的数据”“不动的数据“筛就是了

但发现两个问题：

1.不开无敌没有可以上下动的落脚点，开变速精灵来筛就有点麻烦了

2.后面改了无敌筛出来y轴，发现一调y轴的值它就会把你跩回原处，不知道是有意为之还是怎么的



后面干脆直接改无敌正常打，有问题了开新的桂

第一次改无敌我是找到了死亡计数的地址，01234一个一个筛很快就出来了几个地址

随便选一个地址，查调用，再死一次，选中第一个

![image-20260731103838223](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731103838223.png)

下断点

![屏幕截图 2026-07-29 153307](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-07-29 153307.png)

再死两次发现游戏卡住，选择调试-->步出到断点，找到位置，发现上面有一个跳板函数，把它nop掉

![image-20260731104110087](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731104110087.png)

发现进入了一个“伪无敌”，虽然死不掉但是捡不到东西，陷阱也都不会触发，类似于“虚化”了

后面发现这个伪无敌有点行不通（因为y坐标总是改不了，估计也触发不了胜利条件）



接下来改真无敌

先用激活mono功能，mono分析（现在ce的mono也能分析il2cpp的程序集了）

![image-20260731110645722](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731110645722.png)

点开Assembly-CSharp.dll类，见文知意这里就是作者写的C#的脚本程序集

![image-20260731110832673](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731110832673.png)

有很多种改无敌的办法，我这里是看到了playerhealth（玩家血量）下有个ontriggerenter2d（2d碰撞触发器应该是）

![image-20260731111211470](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731111211470.png)

进去把第一行直接改成return（ret），跳过触发改函数，发现就真无敌了

![image-20260731111304728](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731111304728.png)

有无敌收集完金球就到右上角通关

（作者估计本来限制了跳跃高度，但蹲下再起跳能解决这个问题。。。中间有个大跳很吃操作）

（改重力估计是一个好思路，但我找不到重力或者y速度的地址）

![image-20260731102143528](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260731102143528.png)



 第二种方法就正常逆向思路





## .5623[LitCTF 2024]hello_upx

看题目是upx的壳

![image-20260823224226429](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260823224226429.png)

看介绍，upx是一个可执行文件压缩壳，不是强保护壳，目的是压缩可执行文件体积，方便分发和存储，而非反逆向

不脱壳的话一开始看到的是 UPX 解压代码，不是程序真正逻辑

![image-20260823223948928](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260823223948928.png)

upx官方脱壳报错，有魔改

![屏幕截图 2026-08-30 011334](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-08-30 011334.png)

看了wp才知道去010把upx换成大写UPX就能正常脱壳了

UPX识别要正规格式才能正常脱壳

![image-20260830014131590](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830014131590.png)

![屏幕截图 2026-08-30 014529](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-08-30 014529.png)

![image-20260830014747914](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830014747914.png)

之后进ida伪码也很舒服，就是展示密文的伪码展示怪怪的：

qmemcpy(v4, "...", 16) → 前 16 字节
v4[2] = 0x4F5E4E601E5A4E20LL → 中间 8 字节
v101 = 101 → 最后 1 字节 0x65

逻辑后面讲

![image-20260830144749348](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830144749348.png)





下面是来时路

upx本质是压缩后的代码 + 解压 stub（壳里自带的解码程序）

这里用x64dbg跑过stub，再找原始代码区域

进来的地址都是乱的，还在壳里

标准思路是打开内存布局，在upx0前下断点

upx0 通常是解压后原程序所在区域，抓壳解压完返回代码的瞬间

但是这里返回异常，故用另一种方法

![image-20260830012826032](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830012826032.png)

f9运行到壳运行完到代码部分，这时程序弹出提示

![屏幕截图 2026-08-30 020721](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-08-30 020721.png)

搜索字符串定位到此地址

![image-20260830020917588](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830020917588.png)

![屏幕截图 2026-08-30 021020](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-08-30 021020.png)

1553大概是这个scanf执行完的地方，在此处下断点，不然会跑出去

![image-20260830132800059](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830132800059.png)

后面的循环条件是 i<=0x18，由于是访问下标所以不是24（0x18的十进制）个字符，而是要有0~24一共25个字符

![image-20260830133739304](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830133739304.png)

（这里我之前有一个误区以为不用输入字符继续往下看，但动调里看到的是当前时刻内存中的机器码，输入字符是为了让程序继续执行到后面的校验逻辑，不然会卡在校验逻辑那里）



下完断点，回车，发现下面的逻辑出来了

![image-20260830142907250](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830142907250.png)

> 0040155C  mov eax, dword ptr ss:[rbp-4]
> 00401561  cdqe
> 00401561  movzx eax, byte ptr ss:[rbp+rax-30]
> 00401566  mov edx, eax
> 00401568  mov eax, dword ptr ss:[rbp-4]
> 0040156B  sub edx, eax
> 00401576  mov byte ptr ss:[rbp+rax-30], dl

这一段汇编翻译过来就是

> input[i] = input[i] - i

和ida

里的伪码也对上了

![image-20260830145056225](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830145056225.png)

上面是密文，三段拼接，注意小端存储从后往前

![image-20260830143721495](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260830143721495.png)

反写脚本，减反过来就是加

（s[25] = 0是加个结束标记的，不加问题也不是很大）

```
int main() {
    char t[] = {
        0x4C,0x68,0x72,0x40,0x50,0x41,0x75,0x70,
        0x2B,0x63,0x59,0x25,0x61,0x58,0x51,0x65,
        0x20,0x4E,0x5A,0x1E,0x60,0x4E,0x5E,0x4F,0x65
    };
    char s[26] ;
    for (int i = 0; i < 25; i++) 
	s[i] = t[i] + i;
	s[25] = 0;
    printf("%s\n", s);
    return 0;
}
```

> LitCTF{w3lc0me_t0_l1tctf}



## .ex  Youngter-drive

这道题不在nss

题目给了一个 Youngter-drive.exe

拖进IDA看

先看字符串

```text
input flag:
%36s
flag{%s}
TOiZiZtOrYaToUwPnToBsOaOapsyS
QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm
```

其中这个一眼像密文

```text
TOiZiZtOrYaToUwPnToBsOaOapsyS
```

后面这个应该是换表

```text
QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm
```

开始找逻辑

可以超绝不经意马后炮地注意到main里面连续调用了两次 `CreateThread`

![image](<C:/Users/jzz11/Documents/New project/assets/youngter-drive-wp/ida-window/01-main-createthread-ida-window.png>)

后知后觉是双线程

`CreateThread` 的函数原型是

```c
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES   lpThreadAttributes,
  SIZE_T                  dwStackSize,
  LPTHREAD_START_ROUTINE  lpStartAddress,
  LPVOID                  lpParameter,
  DWORD                   dwCreationFlags,
  LPDWORD                 lpThreadId
);
```

x86里面参数是从右往左压栈，所以在 `call ds:CreateThread` 前面，倒数第四个 `push` 就是线程函数地址，也就是 `lpStartAddress`

图里能看到两次 `CreateThread`

第一次：

```asm
push offset StartAddress
call ds:CreateThread
```

第二次：

```asm
push offset j_thread_skip_index
call ds:CreateThread
```

所以这里不是普通顺序执行，而是开了两个线程

继续跟进去，两个线程实际对应：

```text
StartAddress -> thread_substitute_index
j_thread_skip_index -> thread_skip_index
```

也就是一个替换线程，一个跳过线程

先看第一个线程

![image](<C:/Users/jzz11/Documents/New project/assets/youngter-drive-wp/ida-window/02-thread1-substitute-ida-window.png>)

第一个线程大概逻辑：

```c
while (1)
{
    WaitForSingleObject(mutex, -1);

    if (g_index > -1)
    {
        substitute_one_char(input_buf, g_index);
        g_index--;
        Sleep(100);
    }

    ReleaseMutex(mutex);
}
```

变量 `g_index` 当下标，调用替换函数处理

然后把 `g_index` 减1

第二个线程：`thread_skip_index`

![image](<C:/Users/jzz11/Documents/New project/assets/youngter-drive-wp/ida-window/03-thread2-skip-ida-window.png>)

第二个线程大概逻辑：

```c
while (1)
{
    WaitForSingleObject(mutex, -1);

    if (g_index > -1)
    {
        Sleep(100);
        g_index--;
    }

    ReleaseMutex(mutex);
}
```

这个线程很搞，它不处理字符，只把同一个 `g_index` 减一

所以重点是：

```text
线程1：处理当前字符，然后 index--
线程2：不处理字符，只 index--
```

两个线程抢同一个全局下标 `g_index`

因此不是每个字符都会被替换，二是偶数位不动，奇数位替换

如果没注意双线程，只会做出不可读的结果

。。。

替换函数是 `substitute_one_char`

![image](<C:/Users/jzz11/Documents/New project/assets/youngter-drive-wp/ida-window/04-substitute-func-ida-window.png>)

里面有两个分支

小写字母：

```asm
mov cl, [eax+ecx-60h]
```

也就是

```c
ch = table[ch - 0x60];
```

大写字母：

```asm
mov cl, [eax+ecx-26h]
```

也就是

```c
ch = table[ch - 0x26];
```

表是这个

```text
QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm
```

这里阴完了

不是正常的abcd对应键盘的QWER

因为小写是减 `0x60`

```text
'a' = 0x61
0x61 - 0x60 = 1
table[1] = W
```

所以是abcd对应WERT

```text
a -> W
b -> E
c -> R
...
```

大写同理，是减 `0x26`

```text
'A' = 0x41
0x41 - 0x26 = 0x1b = 27
table[27] = w
```

大写野会跑到表后面的小写区域



懒得搓脚本，厨子有换表功能，再手动分奇偶出结果

![bb691ba7809387732922064e2f0f679c](C:\Users\jzz11\Documents\Tencent Files\1367918985\nt_qq\nt_data\Pic\2026-08\Ori\bb691ba7809387732922064e2f0f679c.png)

这时候就能看出来是可读句子了

flag：

```text
flag{ThisisthreadofwindowshahaIsES}
```



再补充一下这个陌生的函数CreateMutexW

![image-20260823015001794](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260823015001794.png)

这是建立互斥锁，一路抓过去就是互斥锁的函数内容

![image-20260823020141599](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260823020141599.png)

线程是并行的最小单位，单核cpu只会轮流执行每个线程，所以cpu在内核中会为每个线程提供虚拟cpu，使每个线程并发执行，可能导致线程甲还未将数据写入内存，线程乙就旧数据写回寄存器，导致程序混乱

所以要加上锁使线程有序进行（虽然这里只有两个线程应该用不上）

# 水题

## .2145[NSSCTF 2022 Spring Recruit]easy C

a进行逐位异或与b校验

![屏幕截图 2026-06-08 154325](C:\Users\jzz11\Pictures\Screenshots\屏幕截图 2026-06-08 154325.png)

反写脚本，先与2异或再减

```
int main(){
char a[] = "d`vxbQd";
for(int i=0;i<7;i++)
{ 
        a[i]=a[i]^2;
        a[i]--;
}
printf("%s",a);
}
```

NSSCTF{easy_re}

![image-20260608160817739](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260608160817739.png)

## .2903[HNCTF 2022 Week1]贝斯是什么乐器啊？

拖进IDA看伪码

![image-20260608161132051](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260608161132051.png)

定义了两个字符，str2存字符串，str存用户输入的数据

重点关注for那句循环语句：逻辑是第i位减i

例如输入abcdefg就会变成aaaaaaa

然后把输出的str进行base64编码放进str2，与enc"TlJRQFBBdTs4alsrKFI6MjgwNi5p"进行校验



我们反着来，先对enc进行base64解密

![image-20260608184058831](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260608184058831.png)

再写脚本，反过来第i位加i

```
 int main(){
 	char a[]="NRQ@PAu;8j[+(R:2806.i";
 	
 	for(int i=0;i<strlen(a);i++)
 	a[i] += i;
 	
 	printf("%s",a);	
 }
```

![image-20260608184506974](C:\Users\jzz11\AppData\Roaming\Typora\typora-user-images\image-20260608184506974.png)

NSSCTF{B@se64_HAHAHA}

## 



