/*
 * @lc app=leetcode.cn id=878 lang=cpp
 *
 * [878] 第 N 个神奇数字
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int nthMagicalNumber(int n, int a, int b)
    {
        auto gcd = [](auto &self, int a, int b) -> long long
        {
            return (b == 0? a: self(self, b, a % b));
        };

        auto lcm = [&](int a, int b) -> long long
        {
            return (long long)a / gcd(gcd, a, b) * b;
        };

        long long lcm_n = lcm(a, b);
        long long ans = 0;

        for (long long l = 0, r = (long long)n * min(a, b), m = 0; l <= r;)
        {
            m = (l + r) / 2;
            if (m / a + m / b - m / lcm_n >= n)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return (int)(ans % 1000000007);
    }
};
// @lc code=end

