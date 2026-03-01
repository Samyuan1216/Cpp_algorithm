#include <cstdio>
using namespace std;

double f(double x, int n);

int main()
{
    double x = 0;
    int n = 0;
    scanf("%lf%d", &x, &n);

    printf("%.2lf\n", f(x, n));
}

double f(double x, int n)
{
    if (n == 1)
    {
        return x / (1 + x);
    }
    else
    {
        return x / (n + f(x, n - 1));
    }
}