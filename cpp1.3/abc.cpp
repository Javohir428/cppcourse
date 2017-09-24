#include <cstdio>

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    std::puts("Vvedite chisla:");
    std::scanf("%d %d %d", &a, &b, &c);
    int z = a + b + c;
    std::printf("%d + %d + %d = %d\n", a, b, c, z);
}