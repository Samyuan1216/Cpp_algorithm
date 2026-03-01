// https://acm.hdu.edu.cn/showproblem.php?pid=5833

#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 310, MAXV = 2000, MOD = 1000000007;
int mat[MAXN][MAXN], prime[MAXV + 1], pow2[MAXN];
ll arr[MAXN];
bool visited[MAXV + 1];
int t, n, cnt, times = 1;

void prepare()
{
    for (int i = 2; i * i <= MAXV; i++)
    {
        if (!visited[i])
        {
            for (int j = i * i; j <= MAXV; j += i)
            {
                visited[j] = true;
            }
        }
    }

    for (int i = 2; i <= MAXV; i++)
    {
        if (!visited[i])
        {
            prime[++cnt] = i;
        }
    }

    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }
}

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

void solve()
{
    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    for (int i = 1; i <= cnt; i++)
    {
        for (int j = 1; j <= cnt + 1; j++)
        {
            mat[i][j] = 0;
        }
    }

    ll cur;
    for (int i = 1; i <= n; i++)
    {
        cur = arr[i];
        for (int j = 1; j <= cnt && cur != 0; j++)
        {
            while (cur % prime[j] == 0)
            {
                mat[j][i] ^= 1;
                cur /= prime[j];
            }
        }
    }

    gauss(cnt);

    int mi = 0;
    for (int i = 1; i <= cnt; i++)
    {
        if (mat[i][i] == 1)
        {
            mi++;
        }
    }

    std::cout << "Case #" << times << ":\n";
    std::cout << pow2[n - mi] - 1 << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    std::cin >> t;
    prepare();

    for (times; times <= t; times++)
    {
        solve();
    }
}