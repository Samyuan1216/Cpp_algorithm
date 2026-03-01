/*
 * @lc app=leetcode.cn id=233 lang=cpp
 *
 * [233] 数字 1 的个数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countDigitOne(int n)
    {
        int ans = 0;
        for (long long right = 1, tmp = n, left, cur; tmp != 0; right *= 10, tmp /= 10)
        {
            left = tmp / 10;
            cur = tmp % 10;

            ans += left * right;
            if (cur > 1)
            {
                ans += right;
            }
            else if (cur == 1)
            {
                ans += n % right + 1;
            }
        }

        return ans;
    }
};
// @lc code=end

