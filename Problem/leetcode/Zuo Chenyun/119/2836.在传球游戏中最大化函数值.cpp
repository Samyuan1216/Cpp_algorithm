/*
 * @lc app=leetcode.cn id=2836 lang=cpp
 *
 * [2836] 在传球游戏中最大化函数值
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010, LIMIT = 34;
int stjump[MAXN][LIMIT], kbits[LIMIT];
long long stsum[MAXN][LIMIT];
int power, m;

class Solution
{
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k)
    {
        build(k);

        int n = receiver.size();
        for (int i = 0; i < n; i++)
        {
            stjump[i][0] = receiver[i];
            stsum[i][0] = receiver[i];
        }

        for (int p = 1; p <= power; p++)
        {
            for (int i = 0; i < n; i++)
            {
                stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
                stsum[i][p] = stsum[i][p - 1] + stsum[stjump[i][p - 1]][p - 1];
            }
        }

        long long sum, ans = 0;
        for (int i = 0, cur; i < n; i++)
        {
            sum = cur = i;

            for (int j = 0; j < m; j++)
            {
                sum += stsum[cur][kbits[j]];
                cur = stjump[cur][kbits[j]];
            }

            ans = max(ans, sum);
        }

        return ans;
    }

    void build(long long k)
    {
        power = 0;
        while ((1ll << power) <= (k >> 1))
        {
            power++;
        }

        m = 0;
        for (int p = power; p >= 0; p--)
        {
            if ((1ll << p) <= k)
            {
                kbits[m++] = p;
                k -= (1ll << p);
            }
        }
    }
};
// @lc code=end

