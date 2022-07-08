#include <stdio.h>

int main() {
    int ans = 0;

    unsigned int a = 1234;
    unsigned int b = 2;

    int i = 0;

    for (int i = 30; i > -1; i--) {
        if (b << i <= a && b << i != 0) {
            printf("%d %d\n",  b << i, i);
            a -= b << i;
            ans += 1 << i;
            // printf("%u\n", ans);
        }
    }

    printf("%u", ans);



    return 0;
}