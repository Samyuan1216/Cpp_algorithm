/*
 * @lc app=leetcode.cn id=509 lang=cpp
 *
 * [509] 斐波那契数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int fib(int n)
    {
        if (n == 0 || n == 1)
        {
            return n;
        }

        vector<vector<int>> start{{1, 0}}, m{{1, 1}, {1, 0}};

        return multiply(start, power(m, n - 1))[0][0];
    }

    vector<vector<int>> multiply(const vector<vector<int>> &a, const vector<vector<int>> &b)
    {
        int n = a.size(), m = b[0].size(), k = a[0].size();
        vector<vector<int>> ans(n, vector<int>(m));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int c = 0; c < k; c++)
                {
                    ans[i][j] += a[i][c] * b[c][j];
                }
            }
        }

        return ans;
    }

    vector<vector<int>> power(vector<vector<int>> &m, int p)
    {
        int n = m.size();
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; i++)
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

