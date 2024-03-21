//I used bad scoring function (check). Just weight for every symbol.
//And output of this function for long input can be incorrect due to int overflow.
//Maybe for this task (short input and one-byte key) it even better than frequency check.
//E has got the biggest weight, and EEEEEEEEEEEE has the best score.
//I chose weights after several tests and it works for provided example.
//It is possible to convert frequency into weights. Maybe it will give better results.
//But it is not a solution of EEEEEEEEEEEE problem.
//Check function must take into account the frequency deviation in both directions.
//So, frequency check will be better, especially in task 6.
//Despite the fact that in tasks 4 and 6 I got the correct answer using the same function.

/*
Single-byte XOR cipher
The hex encoded string:

1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
... has been XOR'd against a single character. Find the key, decrypt the message.

You can do this by hand. But don't: write code to do it for you.

How? Devise some method for "scoring" a piece of English plaintext.
Character frequency is a good metric.
Evaluate each output and choose the one with the best score.
*/

#include <stdio.h>
#include <stdlib.h>
//#include <limits.h> //for INT_MIN

#define S 100 //Max input len (in hex bytes)

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
    int n = 256, ma = 0, res = 0; //ma = INT_MIN
    char etaoin_up[12] = {'U', 'L', 'D', 'R', 'H', 'S', 'N', 'I', 'O', 'A', 'T', 'E'};
    char etaoin_low[12] = {'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e'};
    char* brute = (char*)malloc(i * sizeof(char)); //need to add check of NULL malloc return
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
            return -1; //return INT_MIN
        }
    }
    return otv;
}
