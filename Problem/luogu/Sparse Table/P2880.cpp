#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;
using v3i = std::vector<vvi>;

const int MAXN = 50010;
v3i st(MAXN, vvi(16, vi(2)));
vi arr(MAXN);
int n, q, a, b, power, m;

int log2(int n)
{
    power = 0;
    while ((1 << power) <= (n >> 1))
    {
        power++;
    }

    return power;
}

void build()
{
    log2(n);

    for (int i = 1; i <= n; i++)
    {
        st[i][0][0] = st[i][0][1] = arr[i];
    }

    for (int p = 1; p <= power; p++)
    {
        for (int i = 1; i + (int)std::pow(2, p - 1) - 1 <= n; i++)
        {
            st[i][p][0] = std::max(st[i][p - 1][0], st[i + (int)std::pow(2, p - 1)][p - 1][0]);
            st[i][p][1] = std::min(st[i][p - 1][1], st[i + (int)std::pow(2, p - 1)][p - 1][1]);
        }
    }
}

int main()
{
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    build();

    while (q--)
    {
        std::cin >> a >> b;
        std::cout << std::max(st[a][log2(b - a + 1)][0], st[b - (int)std::pow(2, log2(b - a + 1)) + 1][log2(b - a + 1)][0]) - std::min(st[a][log2(b - a)][1], st[b - (int)std::pow(2, log2(b - a)) + 1][log2(b - a)][1]) << std::endl;
    }
}