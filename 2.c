#include <stdio.h>
#include <string.h>

#define S 100

int main() {
    char s1[S], s2[S], buf1[3], buf2[3], t1 = 0, t2 = 0;
    buf1[2] = '\0';
    buf2[2] = '\0';
    scanf("%s %s", s1, s2);
    int l = strlen(s1);
    for(int i = 0; i < l; i += 2) {
        buf1[0] = s1[i];
        buf1[1] = s1[i + 1];
        buf2[0] = s2[i];
        buf2[1] = s2[i + 1];
        sscanf(buf1, "%hhx", &t1);
        sscanf(buf2, "%hhx", &t2);
        printf("%02hhx", t1 ^ t2);
    }
    return 0;
}
