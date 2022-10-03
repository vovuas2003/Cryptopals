#include <stdio.h>
#include <stdlib.h>

int check(char *, char* , char* , int);
int one();

int main() {
    for(int i = 0; i < 327; i++) {
        printf("%d ", i + 1);
        one();
    }
    return 0;
}

int one() {
    char inp[30], temp;
    int i = 30;
    for(int on = 0; on < 30; on ++) {
        scanf("%2hhx", &temp);
        inp[on] = temp;
    }
    /*
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
    */
    for(int on = 0; on < 30; on ++) {
        printf("%2x", inp[on]);
    }
    printf("\n");
    return 0;
}

int check(char* etaoin_up, char* etaoin_low, char* s, int l) {
    int otv = 0;
    char t;
    for(int i = 0; i < l; i++) {
        t = s[i];
        if(((t >= '0') && (t <= '9')) || ((t >= 'a') && (t <= 'z')) || ((t >= 'A') && (t <= 'Z')) || (t == ' ') || (t == '\n')) {
            for(int j = 0; j < 12; j++) {
                if((t == etaoin_up[j]) || (t == etaoin_low[j])) {
                    otv += 1 + j;
                    break;
                }
            }
        } else {
            return -1;
        }
    }
    return otv;
}
