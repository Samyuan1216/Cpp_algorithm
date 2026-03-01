/*
 * @lc app=leetcode.cn id=3251 lang=cpp
 *
 * [3251] 单调数组对的数目 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

template<typename T>
T power(T x, int n, T mod = 1)
{
    T ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = ((__int128_t)ans * x) % mod;
        }

        x = ((__int128_t)x * x) % mod;
        n >>= 1;
    }

    return ans;
}

class Solution
{
public:
    int countOfPairs(vector<int>& nums)
    {
        constexpr long long mod = 1000000007;
        auto C = [&](int n, int k)
        {
            long long fac = 1, inv1 = 1, inv2 = 1;
            for (int i = 1; i <= n; i++)
            {
                fac = (fac * i) % mod;
                if (i == k)
                {
                    inv1 = power(fac, mod - 2, mod);
                }

                if (i == n - k)
                {
                    inv2 = power(fac, mod- 2, mod);
                }
            }

            return int((((fac * inv1) % mod) * inv2) % mod);
        };

        int n = nums.size(), k = nums[0] + 1;
        for (int i = 1; i < n && k > 0; i++)
        {
            if (nums[i - 1] > nums[i])
            {
                k -= nums[i - 1] - nums[i];
            }
        }

        if (k <= 0)
        {
            return 0;
        }

        return C(k + n - 1, n);
    }
};
// @lc code=end

