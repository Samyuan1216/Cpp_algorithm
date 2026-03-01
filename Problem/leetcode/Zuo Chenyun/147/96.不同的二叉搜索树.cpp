/*
 * @lc app=leetcode.cn id=96 lang=cpp
 *
 * [96] 不同的二叉搜索树
 */

// @lc code=start
#include <bits/stdc++.h>

template<typename T>
T catalan(int n, T mod = std::numeric_limits<int>::max())
{
    std::vector<T> f(n + 1);
    f[0] = f[1] = 1;

    for (int i: views::iota(2, n + 1))
    {
        for (int l = 0, r = i - 1; l < i; l++, r--)
        {
            f[i] = (f[i] + f[l] * f[r] % mod) % mod;
        }
    }

    return f[n];
}

class Solution
{
public:
    int numTrees(int n)
    {
        return catalan<int>(n);
    }
};
// @lc code=end

