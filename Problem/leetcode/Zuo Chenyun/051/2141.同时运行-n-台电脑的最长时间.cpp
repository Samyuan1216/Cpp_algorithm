/*
 * @lc app=leetcode.cn id=2141 lang=cpp
 *
 * [2141] 同时运行 N 台电脑的最长时间
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long maxRunTime(int n, vector<int>& batteries)
    {
        long long sum = 0;
        int maxn = 0;
        for (auto &x: batteries)
        {
            sum += x;
            maxn = max(maxn, x);
        }

        if (sum > (long long)maxn * n)
        {
            return sum / n;
        }

        int ans = 0;
        for (int l = 0, r = maxn, m = 0; l <= r;)
        {
            m = l + ((r - l) >> 1);
            if (f(batteries, n, m) == true)
            {
                ans = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        return ans;
    }

    bool f(vector<int> &batteries, int n, int m)
    {
        long long sum = 0;
        for (auto &x: batteries)
        {
            if (x >= m)
            {
                n--;
            }
            else
            {
                sum += x;
            }

            if (sum >= (long long)n * m)
            {
                return true;
            }
        }

        return false;
    }
};
// @lc code=end

