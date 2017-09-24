#include <cstdio>
#include <stdio.h>

int main()
{
    int a = 0;
    int b = 0;
    std::scanf("%f %f", &a, &b);
    int x = -b / a;
    std::printf("solution: %f\n", x);
}