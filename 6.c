#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#define ONE 100
#define S 5000
#define MA_KS 40

void base64(char*, char*, char*, int, int, char*);
char find(char, char*);
int hamming(char*, char*, int);

int main() {

    char table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    char one[ONE], inp[S], buf[4], temp_write[3];
    int lo, l = 0, i, j;
    while(1) {
        if(scanf("%s", one) == EOF) {
            break;
        }
        lo = strlen(one);
        for(i = 0; i < (lo / 4); i++) {
            for(j = 0; j < 4; j++) {
                buf[j] = one[i * 4 + j];
            }
            if(buf[3] == '=') {
                buf[3] = 'A';
                if(buf[2] == '=') {
                    buf[2] = 'A';
                    base64(buf, table, inp, l, 1, temp_write);
                    l++;
                } else {
                    base64(buf, table, inp, l, 2, temp_write);
                    l += 2;
                }
                break;
            } else {
                base64(buf, table, inp, l, 3, temp_write);
                l += 3;
            }
        }
    }
    int ks = 0, n = 0;
    double ham = DBL_MAX, t_ham = 0;
    for(i = 2; i <= MA_KS; i++) {
        t_ham = 0;
        n = 0;
        for(j = 0; j < l - 2 * i; j += i) {
            n++;
            t_ham += (double) hamming(inp + j, inp + j + i, i);
        }
        t_ham /= n;
        t_ham /= i;
        if(t_ham < ham) {
            ham = t_ham;
            ks = i;
        }
    }
    printf("%d\n", ks);
    return 0;
}

char find(char c, char* table) {
    for(char i = 0; i < 64; i++) {
        if(c == table[(int) i]) {
            return i;
        }
    }
    return 64;
}

void base64(char* buf, char* table, char* write, int l, int n, char* temp_write) {
    for(int i = 0; i < 4; i++) {
        buf[i] = find(buf[i], table);
    }
    temp_write[0] = (buf[0] << 2) | (buf[1] >> 4);
    temp_write[1] = ((buf[1] & 0xf) << 4) | (buf[2] >> 2);
    temp_write[2] = ((buf[2] & 0x3) << 6) | (buf[3]);
    for(int i = 0; i < n; i++) {
        write[l + i] = temp_write[i];
    }
}

int hamming(char* a, char* b, int l) {
    int otv = 0;
    char t;
    for(int i = 0; i < l; i++) {
        t = a[i] ^ b[i];
        while(t != 0) {
            otv += t & 1;
            t = t >> 1;
        }
    }
    return otv;
}
