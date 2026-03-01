/*
 * @lc app=leetcode.cn id=357 lang=cpp
 *
 * [357] 统计各位数字都不同的数字个数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countNumbersWithUniqueDigits(int n)
    {
        if (n == 0)
        {
            return 1;
        }

        int ans = 10;
        for (int s = 9, i = 9, k = 2; k <= n; i--, k++)
        {
            s *= i;
            ans += s;
        }

        return ans;
    }
};
// @lc code=end

