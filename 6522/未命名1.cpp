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
}//用来解仿rc4的函数 

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

