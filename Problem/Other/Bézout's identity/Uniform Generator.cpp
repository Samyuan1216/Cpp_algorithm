// https://vjudge.net/problem/POJ-1597

#include <bits/stdc++.h>

int step, mod;

int gcd(int a, int b)
{
    return (b == 0? a: gcd(b, a % b));
}

int main()
{
    while (scanf("%d %d", &step, &mod) != EOF)
    {
        printf("%10d%10d %s\n \n", step, mod, (gcd(step, mod) == 1? "Good Choice": "Bad Choice"));
    }
}