#include<bits/stdc++.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

