#include <cstdio>
#include <cmath>

int main()
{
    int x = 0, n = 0;
    scanf("%d %d", &x, &n);

    printf("%.4lf\n", pow(1.001, n) * x);
}