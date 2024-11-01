// ./add 10 20
/*
10 + 20 = 30
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 3) {
        printf("Usage : %s <one> <two>\n", argv[0]);
        exit(1);
    }

    printf("%s + %s = %d\n", argv[1], argv[2], atoi(argv[1]) + atoi(argv[2]));

    return 0;
}