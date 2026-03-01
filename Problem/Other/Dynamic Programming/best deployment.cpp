#include <bits/stdc++.h>

using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 1010;
vi no(MAXN), one(MAXN), both(MAXN);
int n;

int dfs(vvi &dp, int l, int r)
{
    if (l == r)
    {
        return no[l];
    }

    if (dp[l][r] != -1)
    {
        return dp[l][r];
    }

    int ans = std::max(dfs(dp, l + 1, r) + one[l], dfs(dp, l, r - 1) + one[r]);
    for (int i = l + 1; i < r; i++)
    {
        ans = std::max(ans, dfs(dp, l, i - 1) + dfs(dp, i + 1, r) + both[i]);
    }

    dp[l][r] = ans;
    return ans;
}

int best1()
{
    vvi dp(n + 1, vi(n + 1, -1));

    return dfs(dp, 1, n);
}

int best2()
{
    vvi dp(n + 1, vi(2));
    dp[n][0] = no[n], dp[n][1] = one[n];

    for (int i = n - 1; i >= 1; i--)
    {
        dp[i][0] = std::max(dp[i + 1][1] + no[i], dp[i + 1][0] + one[i]);
        dp[i][1] = std::max(dp[i + 1][1] + one[i], dp[i + 1][0] + both[i]);
    }

    return dp[1][0];
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution dis(0.0, 1.0);

void random(int size, int v)
{
    n = size;
    for (int i = 1; i <= size; i++)
    {
        no[i] = dis(gen) * v;
        one[i] = dis(gen) * v;
        both[i] = dis(gen) * v;
    }
}

int main()
{
    int maxn = 100, maxv = 100, test_time = 10000;

    std::cout << "测试开始" << std::endl;
    for (int i = 1; i <= test_time; i++)
    {
        int size = dis(gen) * maxn + 1;
        random(size, maxv);

        int ans1 = best1(), ans2 = best2();
        if (ans1 != ans2)
        {
            std::cout << "出错了" << std::endl;
            std::cout << ans1 << " " << ans2 << std::endl;

            break;
        }
    }
    std::cout << "测试结束" << std::endl;
}