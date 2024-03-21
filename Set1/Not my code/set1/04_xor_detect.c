#include <stdio.h>
#include <float.h>
#include <string.h>

#include "utils.h"

int main() {
    char str[62];
    char byte_str[30];
    char buf[30];
    char result[32];
    double min_score = DBL_MAX;
    double score;

    int n;
    FILE *file = fopen("4.txt", "r");
    while(!feof(file)) {
        fgets(str, 62, file);
        n = scan_bytes(byte_str, str, 30);
        for (unsigned char i = 0; i < 255; ++i) {
           for (int j = 0; j < n; ++j)
                  buf[j] = byte_str[j] ^ i; 
           score = freq_score(buf, n);
           if (score < min_score) {
                min_score = score;
                strncpy(result, buf, n);
           }
        }
    }
    result[31] = '\0';
    printf("%s", result);

    fclose(file); 
}
