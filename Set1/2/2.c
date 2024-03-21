/*
Fixed XOR
Write a function that takes two equal-length buffers and produces their XOR combination.

If your function works properly, then when you feed it the string:
1c0111001f010100061a024b53535009181c
... after hex decoding, and when XOR'd against:
686974207468652062756c6c277320657965
... should produce:
746865206b696420646f6e277420706c6179
*/

#include <stdio.h>
#include <string.h>

#define S 37 //Max len of one input string + 1 for '\0'

int main() {
    char s1[S], s2[S], buf1[3], buf2[3], t1, t2;
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
