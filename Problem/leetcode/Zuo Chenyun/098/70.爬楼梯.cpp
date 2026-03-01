/*
 * @lc app=leetcode.cn id=70 lang=cpp
 *
 * [70] 爬楼梯
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int climbStairs(int n)
    {
        if (n == 0 || n == 1)
        {
            return 1;
        }

        vector<vector<long long>> start{{1, 1}}, m{{1, 1}, {1, 0}};

        return multiply(start, power(m, n - 1))[0][0];
    }

    vector<vector<long long>> multiply(const vector<vector<long long>> &a, const vector<vector<long long>> &b)
    {
        long long n = a.size(), m = b[0].size(), k = a[0].size();
        vector<vector<long long>> ans(n, vector<long long>(m));

        for (long long i = 0; i < n; i++)
        {
            for (long long j = 0; j < m; j++)
            {
                for (long long c = 0; c < k; c++)
                {
                    ans[i][j] += a[i][c] * b[c][j];
                }
            }
        }

        return ans;
    }

    vector<vector<long long>> power(vector<vector<long long>> &m, long long p)
    {
        long long n = m.size();
        vector<vector<long long>> ans(n, vector<long long>(n));
        for (long long i = 0; i < n; i++)
        {
            ans[i][i] = 1;
        }

        for (; p != 0; p >>= 1)
        {
            if ((p & 1) == 1)
            {
                ans = multiply(ans, m);
            }

            m = multiply(m, m);
        }

        return ans;
    }
};
// @lc code=end

