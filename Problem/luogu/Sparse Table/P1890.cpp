#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 1010;
vvi st(MAXN, vi(10));
vi arr(MAXN), lg2(MAXN);
int n, m, l, r;

int gcd(int a, int b)
{
    return b == 0? a: gcd(b, a % b);
}

void build()
{
    lg2[0] = -1;

    for (int i = 1; i <= n; i++)
    {
        lg2[i] = lg2[i >> 1] + 1;
        st[i][0] = arr[i];
    }

    for (int p = 1; p <= lg2[n]; p++)
    {
        for (int i = 1; i + (1 << p) - 1 <= n; i++)
        {
            st[i][p] = gcd(st[i][p - 1], st[i + (1 << (p - 1))][p - 1]);
        }
    }
}

int main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    build();

    while (m--)
    {
        std::cin >> l >> r;
        int p = lg2[r - l + 1];

        std::cout << gcd(st[l][lg2[r - l + 1]], st[r - (1 << p) + 1][p]) << std::endl;
    }
}