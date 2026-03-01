// http://poj.org/problem?id=2947

#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 310, MOD = 7;
std::string days[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
int mat[MAXN][MAXN], inv[MOD];
int n, m, s;

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

int day(std::string str)
{
    for (int i = 0; i < 7; i++)
    {
        if (str == days[i])
        {
            return i;
        }
    }

    return -1;
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
                std::swap(mat[j], mat[i]);
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
                        for (int k = j; k < i; k++)
                        {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
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
            bool flag = false;
            for (int j = i + 1; j <= n; j++)
            {
                if (mat[i][j] != 0)
                {
                    flag = true;
                    break;
                }
            }

            if (!flag)
            {
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    build_inv();

    while (n != 0 && m != 0)
    {
        s = std::max(n, m);
        for (int i = 1; i <= s; i++)
        {
            for (int j = 1; j <= s + 1; j++)
            {
                mat[i][j] = 0;
            }
        }

        for (int i = 1, k; i <= m; i++)
        {
            std::cin >> k;

            std::string st, et;
            std::cin >> st >> et;

            for (int j = 1, tool; j <= k; j++)
            {
                std::cin >> tool;

                mat[i][tool] = (mat[i][tool] + 1) % MOD;
            }

            mat[i][s + 1] = ((day(et) - day(st) + 1) % MOD + MOD) % MOD;
        }

        gauss(s);

        int sign = 1;
        for (int i = 1; i <= s; i++)
        {
            if (mat[i][i] == 0 && mat[i][s + 1] != 0)
            {
                sign = -1;
                break;
            }

            if (i <= n && mat[i][i] == 0)
            {
                sign = 0;
            }
        }

        if (sign == -1)
        {
            std::cout << "Inconsistent data.\n";
        }
        else if (sign == 0)
        {
            std::cout << "Multiple solutions.\n";
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (mat[i][s + 1] < 3)
                {
                    mat[i][s + 1] += 7;
                }
            }

            for (int i = 1; i <= n; i++)
            {
                std::cout << mat[i][s + 1] << " \n"[i == n];
            }
        }

        std::cin >> n >> m;
    }
}