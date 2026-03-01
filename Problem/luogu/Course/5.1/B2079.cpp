#include <cstdio>

int main()
{
    int n = 0;
    scanf("%d", &n);

    double e = 1;
    long long m = 1;
    for (int i = 1; i <= n; i++)
    {
        m *= i;
        e += (double)1 / m;
    }

    printf("%.10lf\n", e);
}