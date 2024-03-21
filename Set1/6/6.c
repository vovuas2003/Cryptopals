/*
cmd run command
a.exe < inp.txt > out.txt 2> key.txt
*/

//Check comments in code for task 3.
//It is hard to understand comments for defines and code without any comments.
//I hope that I will rewrite this task - make code more clear and edit check function (make frequency scoring).

/*
Break repeating-key XOR
It is officially on, now.
This challenge isn't conceptually hard, but it involves actual error-prone coding.
The other challenges in this set are there to bring you up to speed.
This one is there to qualify you. If you can do this one, you're probably just fine up to Set 6.

There's a file here. It's been base64'd after being encrypted with repeating-key XOR.
Decrypt it.

Here's how:

Let KEYSIZE be the guessed length of the key; try values from 2 to (say) 40.
Write a function to compute the edit distance/Hamming distance between two strings. The Hamming distance is just the number of differing bits. The distance between:
this is a test
and
wokka wokka!!!
is 37. Make sure your code agrees before you proceed.

For each KEYSIZE, take the first KEYSIZE worth of bytes, and the second KEYSIZE worth of bytes, and find the edit distance between them. Normalize this result by dividing by KEYSIZE.
The KEYSIZE with the smallest normalized edit distance is probably the key. You could proceed perhaps with the smallest 2-3 KEYSIZE values. Or take 4 KEYSIZE blocks instead of 2 and average the distances.
Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
Solve each block as if it was single-character XOR. You already have code to do this.
For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.

This code is going to turn out to be surprisingly useful later on. Breaking repeating-key XOR ("Vigenere") statistically is obviously an academic exercise, a "Crypto 101" thing.
But more people "know how" to break it than can actually break it, and a similar technique breaks something much more important.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

#define ONE 100 // max len of one string in input
#define S 5000 // max input len
#define MA_KS 40 // max possible len of key

void base64(char*, char*, char*, int, int, char*);
char find(char, char*);
int hamming(char*, char*, int);
int bruteforce(char*, char*, int, int, char*, char*);
int check(char*, char*, char*, int);

int main() {

    char table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    char etaoin_up[12] = {'U', 'L', 'D', 'R', 'H', 'S', 'N', 'I', 'O', 'A', 'T', 'E'};
    char etaoin_low[12] = {'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e'};

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
    char* brute = (char*)malloc(((l / ks) + 1) * sizeof(char));
    char* key = (char*)malloc(ks * sizeof(char));
    int l_brute = 0;
    for(i = 0; i < ks; i++) {
        l_brute = 0;
        for(j = i; j < l; j += ks) {
            brute[l_brute] = inp[j];
            l_brute++;
        }
        if(bruteforce(brute, key, l_brute, i, etaoin_up, etaoin_low)) {
            fprintf(stderr, "No printable strings in %d block!", i + 1);
            return 1;
        }
    }
    free(brute);
    for(i = 0; i < ks; i++) {
        fprintf(stderr, "%c", key[i]);
    }
    for(i = 0; i < l; i++) {
        printf("%c", inp[i] ^ key[i % ks]);
    }
    free(key);
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

int bruteforce(char* brute, char* key, int l_brute, int i, char* etaoin_up, char* etaoin_low) {
    char* temp = (char*)malloc(l_brute * sizeof(char));
    int ma = 0, res = 0, f = 1;
    char x = 0, n;
    for(int i = 0; i < 256; i++) {
        for(int j = 0; j < l_brute; j++) {
            temp[j] = brute[j] ^ x;
        }
        res = check(etaoin_up, etaoin_low, temp, l_brute);
        if(res > ma) {
            ma = res;
            n = x;
            f = 0;
        }
        x++;
    }
    free(temp);
    if(f) {
        return 1;
    }
    key[i] = n;
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
