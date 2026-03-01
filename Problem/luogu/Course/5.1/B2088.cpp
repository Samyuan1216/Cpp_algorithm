#include <cstdio>

int main()
{
    double a[10] = {28.9, 32.7, 45.6, 78, 35, 86.2, 27.8, 43, 56, 65};
    double sum = 0;
    for (auto &x: a)
    {
        int t = 0;
        scanf("%d", &t);

        sum += x * t;
    }

    printf("%.1f\n", sum);
}