#include <stdio.h>
main()
{
    printf("Reset ESC\n");
    printf("\x1b[0m");
    printf("Done.\n");
}
