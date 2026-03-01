#include <bits/stdc++.h>

const int MAXN = 40;
int mat[MAXN][MAXN], op[MAXN];
int n, m, ans;

void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] == 1)
            {
                continue;
            }

            if (mat[j][i] == 1)
            {
                std::swap(mat[i], mat[j]);
                break;
            }
        }

        if (mat[i][i] == 1)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != i && mat[j][i] == 1)
                {
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}

void dfs(int i, int num)
{
    if (num >= ans)
    {
        return;
    }

    if (i == 0)
    {
        ans = num;
    }
    else
    {
        if (mat[i][i] == 0)
        {
            op[i] = 0;
            dfs(i - 1, num);

            op[i] = 1;
            dfs(i - 1, num + 1);
        }
        else
        {
            int cur = mat[i][n + 1];
            for (int j = i + 1; j <= n; j++)
            {
                if (mat[i][j] == 1)
                {
                    cur ^= op[j];
                }
            }

            dfs(i - 1, num + cur);
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        mat[i][i] = mat[i][n + 1] = 1;
    }

    for (int i = 1, u, v; i <= m; i++)
    {
        std::cin >> u >> v;

        mat[u][v] = mat[v][u] = 1;
    }

    gauss(n);

    int sign = 1;
    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] == 0)
        {
            sign = 0;
            break;
        }
    }

    if (sign == 1)
    {
        ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (mat[i][n + 1] == 1)
            {
                ans++;
            }
        }
    }
    else
    {
        ans = n;
        dfs(n, 0);
    }

    std::cout << ans << "\n";
}