#include <cstdio>
#include <stdio.h>
#include <math.h>

int main()
{
    std::puts("Vvedite tri koeffitsientov kvadratnogo uravneniya:");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float x1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
    float x2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / 2 * a;
    std::printf("X1 = %f, X2 = %f", x1, x2);
}