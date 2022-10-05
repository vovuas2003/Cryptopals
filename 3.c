#include <stdio.h>
#include <stdlib.h>

#define S 100

int check(char *, char* , char* , int);

int main() {
    char inp[S], temp;
    int i = 0;
    while(1) {
        if(scanf("%2hhx", &temp) != EOF) {
            inp[i] = temp;
            i++;
        } else {
            break;
        }
    }
    int n = 256, ma = 0, res = 0;
    char etaoin_up[12] = {'U', 'L', 'D', 'R', 'H', 'S', 'N', 'I', 'O', 'A', 'T', 'E'};
    char etaoin_low[12] = {'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e'};
    char* brute = (char*)malloc(i * sizeof(char));
    for(int x = 0; x < 256; x++) {
        for(int j = 0; j < i; j++) {
            brute[j] = inp[j] ^ x;
        }
        res = check(etaoin_up, etaoin_low, brute, i);
        if(res > ma) {
            ma = res;
            n = x;
        }
    }
    free(brute);
    if(n == 256) {
        printf("No printable strings!\n");
        return 0;
    }
    printf("%d ", n);
    for(int j = 0; j < i; j++) {
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
