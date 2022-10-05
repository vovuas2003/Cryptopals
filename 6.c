#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ONE 100
#define S 5000

void base64(char*, char*);
void base64_2(char*, char*);
void base64_3(char*, char*);

/*
Написать функции перевода base64 в hex для 3 случаев:
    base64 - нет ни одного =
    base64_3 - если одно = в конце
    base64_2 - два = в конце

!!!Они должны дописывать в inp, который надо им передать
*/

int main() {

    char table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
    
    char one[ONE], inp[S], buf[4];
    int lo, l = 0, i, j;
    while(1) {
        if(scanf("%s", one) = EOF) {
            break;
        }
        lo = strlen(one);
        for(i = 0; i < (lo / 4); i++) {
            for(j = 0; j < 4; j++) {
                buf[j] = one[i * 4 + j];
            }
            if(buf[3] == '=') {
                if(buf[2] == '=') {
                    base64_2(buf, table);
                    l++;
                } else {
                    base64_3(buf, table);
                    l += 2;
                }
            } else {
                base64(buf, table);
                l += 3;
            }
        }
    }
    return 0;
}
