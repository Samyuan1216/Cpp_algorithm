#include <bits/stdc++.h>

const int MAXN = 61, MAXP = 64, NA = INT32_MAX;
bool st[MAXN][MAXN][MAXP + 1];
int tim[MAXN][MAXN];
int n, m;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            tim[i][j] = NA;
        }
    }

    for (int i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;

        st[u][v][0] = true;
        tim[u][v] = 1;
    }

    for (int p = 1; p <= MAXP; p++)
    {
        for (int jump = 1; jump <= n; jump++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (st[i][jump][p - 1] && st[jump][j][p - 1])
                    {
                        st[i][j][p] = true;
                        tim[i][j] = 1;
                    }
                }
            }
        }
    }

    if (tim[1][n] != 1)
    {
        for (int jump = 1; jump <= n; jump++)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (tim[i][jump] != NA && tim[jump][j] != NA)
                    {
                        tim[i][j] = std::min(tim[i][j], tim[i][jump] + tim[jump][j]);
                    }
                }
            }
        }
    }

    std::cout << tim[1][n] << "\n";
}