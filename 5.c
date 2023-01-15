/*
Here is the opening stanza of an important work of the English language:

Burning 'em, if you ain't quick and nimble
I go crazy when I hear a cymbal

Encrypt it, under the key "ICE", using repeating-key XOR.

In repeating-key XOR, you'll sequentially apply each byte of the key;
the first byte of plaintext will be XOR'd against I, the next C, the next E,
then I again for the 4th byte, and so on.

It should come out to:
0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272
a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
*/

#include <stdio.h>
#include <string.h>

#define S 33 /* max len of key */

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
