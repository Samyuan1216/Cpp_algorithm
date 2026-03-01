// https://acm.hdu.edu.cn/showproblem.php?pid=5755

#include <bits/stdc++.h>

using ll = long long;

const int MAXS = 1010, MOD = 3;
int mat[MAXS][MAXS], inv[MOD], dir[] = {0, -1, 0, 1, 0};
int t, n, m, s;

void build_inv()
{
    inv[1] = 1;
    for (int i = 2; i < MOD; i++)
    {
        inv[i] = (int)(MOD - (ll)inv[MOD % i] * (MOD / i) % MOD);
    }
}

int gcd(int a, int b)
{
    return (b == 0? a: gcd(b, a % b));
}

void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] != 0)
            {
                continue;
            }

            if (mat[j][i] != 0)
            {
                std::swap(mat[i], mat[j]);
                break;
            }
        }

        if (mat[i][i] != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != i && mat[j][i] != 0)
                {
                    int g = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / g, b = mat[j][i] / g;
                    if (j < i && mat[j][j] != 0)
                    {
                        mat[j][j] = (mat[j][j] * a) % MOD;
                    }

                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (mat[i][i] != 0)
        {
             mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
        }
    }
}

void solve()
{
    std::cin >> n >> m;
    s = n * m;

    for (int i = 1; i <= s; i++)
    {
        for (int j = 1; j <= s + 1; j++)
        {
            mat[i][j] = 0;
        }
    }

    for (int i = 0, cur, row, col; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cur = i * m + j + 1;

            mat[cur][cur] = 2;
            for (int d = 0; d <= 3; d++)
            {
                row = i + dir[d]; col = j + dir[d + 1];
                if (row >= 0 && row < n && col >= 0 && col < m)
                {
                    mat[cur][row * m + col + 1] = 1;
                }
            }
        }
    }

    for (int i = 1, x; i <= s; i++)
    {
        std::cin >> x;
        mat[i][s + 1] = (3 - x) % MOD;
    }

    gauss(s);

    int ans = 0;
    for (int i = 1; i <= s; i++)
    {
        ans += mat[i][s + 1];
    }

    std::cout << ans << "\n";

    for (int i = 1, id = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++, id++)
        {
            while (mat[id][s + 1]-- > 0)
            {
                std::cout << i << " " << j << "\n";
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    build_inv();

    std::cin >> t;
    while (t--)
    {
        solve();
    }
}