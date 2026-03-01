#include <bits/stdc++.h>

const int MAXN = 110, MAXM = 15, MAXS = 65;
int grid[MAXN][MAXM], dp[MAXN][MAXS][MAXS], sta[MAXS];
int n, m, k, ans;
std::string line;

void prepare(int j, int s)
{
    if (j >= m)
    {
        sta[k++] = s;
    }
    else
    {
        prepare(j + 1, s);
        prepare(j + 3, s | (1 << j));
    }
}

int count(int i, int s)
{
    int ans = 0;
    for (int j = 0; j < m; j++)
    {
        if (((s >> j) & 1) == 1 && grid[i][j] == 1)
        {
            ans++;
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        std::cin >> line;
        for (int j = 0; j < m; j++)
        {
            grid[i][j] = (line[j] == 'P'? 1: 0);
        }
    }

    prepare(0, 0);

    for (int a = 0, cnt; a < k; a++)
    {
        cnt = count(0, sta[a]);
        dp[0][a][0] = cnt;
    }

    for (int i = 1; i < n; i++)
    {
        for (int a = 0, cnt; a < k; a++)
        {
            cnt = count(i, sta[a]);
            for (int b = 0; b < k; b++)
            {
                if ((sta[a] & sta[b]) == 0)
                {
                    for (int c = 0; c < k; c++)
                    {
                        if ((sta[a] & sta[c]) == 0 && (sta[b] & sta[c]) == 0)
                        {
                            dp[i][a][b] = std::max(dp[i][a][b], dp[i - 1][b][c] + cnt);
                        }
                    }
                }
            }
        }
    }

    for (int a = 0; a < k; a++)
    {
        for (int b = 0; b < k; b++)
        {
            ans = std::max(ans, dp[n - 1][a][b]);
        }
    }

    std::cout << ans << "\n";
}