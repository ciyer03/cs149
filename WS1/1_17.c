#include <stdio.h>

int main(int argc, char *argv[])
{
    int headInt;
    int baseInt;
    
    scanf("%d %d", &baseInt, &headInt);
    printf("    %d\n", headInt);
    printf("    %d%d\n", headInt, headInt);
    printf("%d%d%d%d%d%d%d\n", baseInt, baseInt, baseInt, baseInt, headInt, headInt, headInt);    
    printf("%d%d%d%d%d%d%d%d\n", baseInt,baseInt,baseInt, baseInt, headInt, headInt, headInt, headInt);    
    printf("%d%d%d%d%d%d%d\n", baseInt,baseInt,baseInt,headInt, headInt, headInt, headInt);    
    printf("    %d%d\n", headInt, headInt);    
    printf("    %d\n", headInt);    
    return 0;
}
