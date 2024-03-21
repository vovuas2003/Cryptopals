//Input format: first string is a key as ASCII char string,
//second string is a hex bytes which will be encrypted
//and printed as string (ASCII chars).

#include <stdio.h>
#include <string.h>

#define S 33 //max key len

int main() {
    char t;
    int l = 0;
    char key[S];
    while(1) {
        t = getchar();
        if(t == '\n') {
            break;
        }
        key[l] = t;
        l++;
    }
    int i = 0;
    unsigned char temp;
    while(1) {
        if(scanf("%2hhx", &temp) == EOF) {
            break;
        }
        printf("%c", temp ^ key[i % l]); //key[i] - see comments below
        i++; //can overflow for VERY long input
        //if(i == l) i = 0;
    }
    return 0;
}
