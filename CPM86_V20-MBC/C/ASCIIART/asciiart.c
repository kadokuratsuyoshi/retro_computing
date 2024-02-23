#include "stdio.h"

main()
{
    int x, y, i;
    float ca, cb, a, b, t;

    for (y=-12; y<=12; y++) {
        for (x=-39; x<=39; x++) {
            ca = (float)x * 0.0458;
            cb = (float)y * 0.08333;
            a = ca;
            b = cb;
            for (i=0; i<16; i++) {
                t = a*a - b*b + ca;
                b = 2*a*b + cb;
                a = t;
                if ((a*a + b*b)>4) {
                    if (i>9) {
                        i = i + 7;
                    }
                    printf("%c", 48+i);
                    break;
                }
            }
            if (i==16) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
