#include <stdio.h>
#include <string.h>

#define S 33

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
    while(1) {
        t = getchar();
        if(t == EOF) {
            break;
        }
        printf("%02hhx", t ^ key[i % l]);
        i++;
    }
    return 0;
}
