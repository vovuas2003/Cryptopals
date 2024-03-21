#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>

#include "utils.h"

// 'a'-'z', last value is a frequency of non-alphaber symbols
const double eng_freq[] = {0.08167,0.01492,0.02782,0.04253,0.12702,0.02228,0.02015,0.06094,0.06966,0.00153,0.00772,0.04025,0.02406,0.06749,0.07507,0.01929,0.00095,0.05987,0.06327,0.09056,0.02758,0.00978,0.02360,0.00150,0.01974,0.00074,0};

void freq(char *str, int n, double* freqs, char min, char max) {
       for (int i = 0; i < n; ++i) {
               if (str[i] >= min && str[i] <= max)
                    freqs[str[i] - min]++;
               else
                    freqs[max - min + 1]++;
       }
    
       for (int j = 0; j < max - min + 2; ++j)
            freqs[j] /= n;
}

double std(double *a, const double *b, int n) {
        double result = 0;
        for (int i = 0; i < n; ++i)
            result += (a[i] - b[i]) * (a[i] - b[i]); 
        result /= n;
        return result;
}

double freq_score(char *str, int n) {
        double score = 0;
        char* str_copy = (char*)malloc(n); 
        strncpy(str_copy, str, n);

        // last value is a frequency of non-alphaber symbols
        double* freqs = (double*)malloc(('z' - 'a' + 2) * sizeof(double));

        for (int i = 0; i < n; ++i)
            if (str_copy[i] >= 'A' && str_copy[i] <='Z')
                str_copy[i] = tolower(str[i]);  

        freq(str_copy, n, freqs, 'a', 'z');

        score = std(freqs, eng_freq, 'z' - 'a' + 2); 
        free(str_copy);
        free(freqs);
        return score;
}

int main() {
        char *input = (char*)malloc(34); 
        read_bytes(input, 34);

        char *result = (char*)malloc(35);
        char *buf = (char*)malloc(34);
        double score = 0; double min_score = DBL_MAX;

        for (unsigned char i = 0; i < 255; ++i) {
           for (int j = 0; j < 34; ++j)
                  buf[j] = input[j] ^ i; 
           score = freq_score(buf, 34);
           if (score < min_score) {
                min_score = score;
                strncpy(result, buf, 34);
           }
        }
        result[34] = '\0';
        printf("%s\n", result);

        free(input); free(result); free(buf);
}
