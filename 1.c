#include <stdio.h>

int main() {

    char table[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
    
    unsigned char buf[3] = {0, 0, 0};
    unsigned char temp = 0;
    int i = 0, j = 0, k = 0;
    while(1) {
        i = 0;
        for(j = 0; j < 3; j++) {
            if(scanf("%2hhx", &temp) != EOF) {
                buf[j] = temp;
                i++;
            } else {
                for(k = j; k < 3; k++) {
                    buf[k] = 0;
                }
                break;
            }
        }
        if(i == 0) {
            break;
        }
        printf("%c%c%c%c", table[buf[0] >> 2], table[((buf[0] & 0x3 ) << 4) | (buf[1] >> 4)], table[((buf[1] & 0xf) << 2) | (buf[2] >> 6)], table[buf[2] & 0x3f]);
        if(i != 3) {
            break;
        }
    }
    return 0;
}
