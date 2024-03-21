#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define INPUT_LEN 200
int main() {
    char *a = (char*)malloc(INPUT_LEN);
    char *b = (char*)malloc(INPUT_LEN);
    char *output = (char*)malloc(INPUT_LEN); 

    int n = read_bytes(a, INPUT_LEN);
    read_bytes(b, INPUT_LEN);
    
    for(int i = 0; i < n; ++i) {
        output[i] = a[i] ^ b[i];
    } 
    print_bytes(output, n); 

    free(a); free(b);
}
