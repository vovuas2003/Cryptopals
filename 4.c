#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S 100

int check(char*, char*, char*, int);
int one(char*, int, int);

int main() {
    char inp[S];
    char buf[3];
    buf[2] = '\0';
    int i = 0, l;
    while(1) {
        if(scanf("%s", inp) == EOF) {
            break;
        }
        i++;
        l = strlen(inp) / 2;
        char* norm_inp = (char*)malloc(l * sizeof(char));
        for(int j = 0; j < l; j++) {
            buf[0] = inp[j * 2];
            buf[1] = inp[j * 2 + 1];
            sscanf(buf, "%2hhx", &norm_inp[j]);
        }
        one(norm_inp, l, i);
        free(norm_inp);
    }
    return 0;
}

int one(char* inp, int l, int i) {
    int ma = 0, res = 0;
    char x = 0, n;
    int f = 1;
    char etaoin_up[12] = {'U', 'L', 'D', 'R', 'H', 'S', 'N', 'I', 'O', 'A', 'T', 'E'};
    char etaoin_low[12] = {'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e'};
    char* brute = (char*)malloc(l * sizeof(char));
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < l; j++) {
            brute[j] = inp[j] ^ x;
        }
        res = check(etaoin_up, etaoin_low, brute, l);
        if(res > ma) {
            ma = res;
            n = x;
            f = 0;
        }
        x++;
    }
    free(brute);
    if(f) {
        return 0;
    }
    printf("%d %d ", i, n);
    for(int j = 0; j < l; j++) {
        printf("%c", inp[j] ^ n);
    }
    printf("\n");
    return 0;
}

int check(char* etaoin_up, char* etaoin_low, char* s, int l) {
    int otv = 0;
    char t;
    for(int i = 0; i < l; i++) {
        t = s[i];
        if(((t >= 32) && (t <= 126)) || (t == '\n')) {
            for(int j = 0; j < 12; j++) {
                if((t == etaoin_up[j]) || (t == etaoin_low[j])) {
                    otv += 12 + 3 * (j + 1);
                    break;
                }
                if(((t >= 'a') && (t <= 'z')) || ((t >= 'A') && (t <= 'Z')) || (t == ' ')) {
                    otv += 7;
                } else {
                    otv -= 30;
                }
            }
        } else {
            return -1;
        }
    }
    return otv;
}
