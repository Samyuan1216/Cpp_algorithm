/*
 * @lc app=leetcode.cn id=2463 lang=cpp
 *
 * [2463] 最小移动总距离
 */

// @lc code=start
#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAXN = 110;
const ll NA = INT64_MAX;
int rob[MAXN], fac[MAXN][2], q[MAXN];
ll sum[MAXN], dp[MAXN][MAXN];
int n, m, l, r;

class Solution
{
public:
    ll minimumTotalDistance(vi &robot, vvi &factory)
    {
        build(robot, factory);

        for (int i = 1, cap; i <= n; i++)
        {
            cap = fac[i][1];
            for (int j = 1; j <= m; j++)
            {
                sum[j] = sum[j - 1] + dist(i, j);
            }

            l = r = 0;
            for (int j = 1; j <= m; j++)
            {
                dp[i][j] = dp[i - 1][j];

                add(i, j);
                del(j - cap);

                if (l < r)
                {
                    dp[i][j] = std::min(dp[i][j], value(i, q[l]) + sum[j]);
                }
            }
        }

        return dp[n][m];
    }

    void build(vi &robot, vvi &factory)
    {
        std::sort(robot.begin(), robot.end());
        std::sort(factory.begin(), factory.end(), [](vi &a, vi &b)
        {
            return a[0] < b[0];
        });

        n = factory.size(), m = robot.size();
        for (int i = 1; i <= n; i++)
        {
            fac[i][0] = factory[i - 1][0];
            fac[i][1] = factory[i - 1][1];
        }

        for (int i = 1; i <= m; i++)
        {
            rob[i] = robot[i - 1];
        }

        std::fill(dp[0] + 1, dp[0] + m + 1, NA);
    }

    ll dist(int i, int j)
    {
        return std::abs((ll)fac[i][0] - rob[j]);
    }

    ll value(int i, int j)
    {
        if (dp[i - 1][j - 1] == NA)
        {
            return NA;
        }

        return dp[i - 1][j - 1] - sum[j - 1];
    }

    void add(int i, int j)
    {
        if (value(i, j) != NA)
        {
            while (l < r && value(i, q[r - 1]) >= value(i, j))
            {
                r--;
            }

            q[r++] = j;
        }
    }

    void del(int i)
    {
        if (l < r && q[l] == i)
        {
            l++;
        }
    }
};
// @lc code=end

