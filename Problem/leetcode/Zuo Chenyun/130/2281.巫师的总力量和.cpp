/*
 * @lc app=leetcode.cn id=2281 lang=cpp
 *
 * [2281] 巫师的总力量和
 */

// @lc code=start
#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;

const int MOD = 1000000007;

class Solution
{
public:
    int totalStrength(vi &strength)
    {
        int n = strength.size(), pre = strength[0] % MOD;
        
        vi sumsum(n);
        sumsum[0] = pre;
        for (int i = 1; i < n; i++)
        {
            pre = (pre + strength[i]) % MOD;
            sumsum[i] = (sumsum[i - 1] + pre) % MOD;
        }

        vi sta(n);
        int size = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            while (size > 0 && strength[sta[size - 1]] >= strength[i])
            {
                int m = sta[--size];
                int l = (size > 0? sta[size - 1]: -1);
                ans = (ans + sum(strength, sumsum, l, m, i)) % MOD;
            }

            sta[size++] = i;
        }

        while (size > 0)
        {
            int m = sta[--size];
            int l = (size > 0? sta[size - 1]: -1);
            ans = (ans + sum(strength, sumsum, l, m, n)) % MOD;
        }

        return ans;
    }

    int sum(vi &strength, vi &sumsum, int l, int m, int r)
    {
        ll left = sumsum[r - 1];
        if (m - 1 >= 0)
        {
            left = (left - sumsum[m - 1] + MOD) % MOD;
        }
        
        left = (left * (m - l)) % MOD;

        ll right = 0;
        if (m - 1 >= 0)
        {
            right = (right + sumsum[m - 1]) % MOD;
        }

        if (l - 1 >= 0)
        {
            right = (right - sumsum[l - 1] + MOD) % MOD;
        }

        right = (right * (r - m)) % MOD;
        return (int)(((left - right + MOD) % MOD * strength[m]) % MOD);
    }
};
// @lc code=end

