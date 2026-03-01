/*
 * @lc app=leetcode.cn id=1220 lang=cpp
 *
 * [1220] 统计元音字母序列的数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    const int MOD = 1000000007;

    int countVowelPermutation(int n)
    {
        vector<vector<int>> start{{1, 1, 1, 1, 1}}, m{{0, 1, 0, 0, 0}, {1, 0, 1, 0, 0}, {1, 1, 0, 1, 1}, {0, 0, 1, 0, 1}, {1, 0, 0, 0, 0}};
        
        vector<vector<int>> ans = multiply(start, power(m, n - 1));

        int ret = 0;
        for (auto &x: ans[0])
        {
            ret = (ret + x) % MOD;
        }

        return ret;
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

