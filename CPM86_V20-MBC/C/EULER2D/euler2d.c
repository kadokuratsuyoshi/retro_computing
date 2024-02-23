#include "stdio.h"

int main()
{
    double t = 0.0;
    double x = 1.0;
    double v = 0.0;
    double dt = 0.01;
    double dx, dv;
    double k = 1.0;
    double m = 1.0;
    double gamma = 0.2;
    int i;
    int px, py;
    static int xy[40][20];

    printf("Now calculating\n");
    for (i=0; i<=2000; i++) {
        dx = dt * v;
        dv = dt * ((-k*x-gamma*v)/m);
        t = t + dt;
        x = x + dx;
        v = v + dv;

        px = 20 + (int)(20*x);
        py = 10 - (int)(10*v);
        xy[px][py] = 1;
        if (i % 100 == 0) {
            printf("%4.0f%%\r", (float)i/2000.0*100.0);
        }
    }
    printf("\nDone\n");
    for (py=0; py<20; py++) {
        for (px=0; px<40; px++) {
            if (xy[px][py] == 0) {
                printf(" ");
            }
            else {
                printf("o");
            }
        }
        printf("\n");
    }
    return 0;
}
