#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 200010, LIMIT = 18;
vvi lines(MAXN << 1, vi(3)), st(MAXN << 1, vi(LIMIT));
vi ans(MAXN);
int n, m, power;

void log2()
{
    while ((1 << power) <= (n >> 1))
    {
        power++;
    }
}

void build()
{
    log2();

    for (int i = 1; i <= n; i++)
    {
        if (lines[i][1] > lines[i][2])
        {
            lines[i][2] += m;
        }
    }

    std::sort(lines.begin() + 1, lines.begin() + n + 1, [](vi &a, vi &b)
    {
        return a[1] < b[1];
    });

    for (int i = 1; i <= n; i++)
    {
        lines[i + n][0] = lines[i][0];
        lines[i + n][1] = lines[i][1] + m;
        lines[i + n][2] = lines[i][2] + m;
    }

    int e = n << 1;
    for (int i = 1, arrive = 1; i <= e; i++)
    {
        while (arrive + 1 <= e && lines[arrive + 1][1] <= lines[i][2])
        {
            arrive++;
        }

        st[i][0] = arrive;
    }

    for (int p = 1; p <= power; p++)
    {
        for (int i = 1; i <= e; i++)
        {
            st[i][p] = st[st[i][p - 1]][p - 1];
        }
    }
}

int jump(int i)
{
    int aim = lines[i][1] + m, cur = i, next, ans = 1;
    for (int p = power; p >= 0; p--)
    {
        next = st[cur][p];
        if (next != 0 && lines[next][2] < aim)
        {
            ans += 1 << p;
            cur = next;
        }
    }

    return ans + 1;
}

int main()
{
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        lines[i][0] = i;
        std::cin >> lines[i][1] >> lines[i][2];
    }

    build();

    for (int i = 1; i <= n; i++)
    {
        ans[lines[i][0]] = jump(i);
    }

    for (int i = 1; i <= n; i++)
    {
        std::cout << ans[i] << " \n"[i == n];
    }
}