// https://vjudge.net/problem/POJ-1265

#include <bits/stdc++.h>

int t, n, edges, inners;
double area;

int gcd(int a, int b)
{
    return (b == 0? a: gcd(b, a % b));
}

int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        scanf("%d", &n);
        edges = 0, area = 0;

        for (int j = 1, x = 0, y = 0, dx, dy; j <= n; j++)
        {
            scanf("%d %d", &dx, &dy);

            edges += gcd(std::abs(dx), std::abs(dy));
            area += x * (y + dy) - y * (x + dx);
            x += dx, y += dy;
        }

        area /= 2;
        inners = int(area) - edges / 2 + 1;

        printf("Scenario #%d:\n%d %d %.1lf\n\n", i, inners, edges, area);
    }
}