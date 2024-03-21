#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "utils.h"
#define INPUT_LEN 200

const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main() {
       char *input = (char*)malloc(INPUT_LEN); 
       char *output = (char*)malloc((INPUT_LEN / 3 + INPUT_LEN % 3) * 4);
       char buf[3];
       char sixtet;
       int i; int j;
       int n = read_bytes(input, INPUT_LEN);

       // number of byte triples (n_triples * 4 - output size)
	   int n_triples = n / 3;
       // if n is not divided by 3 then we should add one more triple, we will fill remaining bytes with zeroes
       if (n % 3)
               n_triples++;

       // i - starting number of triple, j - starting number of quadriple
       for (i = 0, j = 0; i < 3 * n_triples; i += 3, j += 4) {
            // if it's the last triple (maybe not full)
            if (i == 3 * n_triples - 1) {
                buf[0] = input[i];
                if (n % 3 == 1)
                        buf[1] = buf[2] = 0;
                else if (n % 3 == 2) {
                        buf[1] = input[i + 1];                        
                        buf[2] = 0;
                }
                else {
                        buf[1] = input[i + 1];
                        buf[2] = input[i + 2];
                }
            }
            else {
                buf[0] = input[i]; buf[1] = input[i+1]; buf[2] = input[i+2];
            }
    	  	sixtet = (buf[0] & 0b11111100) >> 2;
			output[j] = b64[(int)sixtet];
			sixtet = ((buf[0] & 0b00000011) << 4) | ((buf[1] & 0b11110000) >> 4);
			output[j+1] = b64[(int)sixtet];
			sixtet = ((buf[1] & 0b00001111) << 2) | ((buf[2] & 0b11000000) >> 6);
			output[j+2] = b64[(int)sixtet];
			sixtet = buf[2] & 0b00111111;
			output[j+3] = b64[(int)sixtet]; 
       }
	for (int k = 0; k < n_triples * 4; ++k) {
		printf("%c", output[k]);
	}
	printf("\n");

}
