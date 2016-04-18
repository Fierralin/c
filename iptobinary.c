#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    char a[100], b[4], c[9];
    int i, j, k, m;
    while(~scanf("%s", a)) {
        i = 0;
        j = 0;
        while(1) {
            if(isdigit(a[i])) b[j++] = a[i];
            else if(a[i] == '.') {
                b[j] = '\0';
                k = atoi(b);
                for(j = 0, m = 1; j < 8; j++) {
                    c[7 - j] = (k / m % 2) + '0';
                    m *= 2;
                }
                c[8] = '\0';
                printf("%s:", c);
                j = 0;
            }
            else if(a[i] == '\0') {
                b[j] = '\0';
                k = atoi(b);
                for(j = 0, m = 1; j < 8; j++) {
                    c[7 - j] = (k / m % 2) + '0';
                    m *= 2;
                }
                c[8] = '\0';
                printf("%s\n", c);
                j = 0;
                break;
            }
            i++;
        }
    }
}
