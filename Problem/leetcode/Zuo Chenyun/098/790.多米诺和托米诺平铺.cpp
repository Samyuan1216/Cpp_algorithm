/*
 * @lc app=leetcode.cn id=790 lang=cpp
 *
 * [790] 多米诺和托米诺平铺
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numTilings(int n)
    {
        if (n == 1)
        {
            return 1;
        }
        else if (n == 2)
        {
            return 2;
        }
        else if (n == 3)
        {
            return 5;
        }

        vector<vector<int>> start{{5, 2, 1}}, m = {{2, 1, 0}, {0, 0, 1}, {1, 0, 0}};

        return multiply(start, power(m, n - 3))[0][0];
    }

    vector<vector<int>> multiply(const vector<vector<int>> &a, const vector<vector<int>> &b)
    {
        const int MOD = 1000000007;
        int n = a.size(), m = b[0].size(), k = a[0].size();
        vector<vector<int>> ans(n, vector<int>(m));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (int c = 0; c < k; c++)
                {
                    ans[i][j] = ((long long)a[i][c] * b[c][j] + ans[i][j]) % MOD;
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

