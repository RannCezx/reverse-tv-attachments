#include <stdio.h>
#include <string.h>

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

