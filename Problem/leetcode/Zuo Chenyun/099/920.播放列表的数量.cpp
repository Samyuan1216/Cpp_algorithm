/*
 * @lc app=leetcode.cn id=920 lang=cpp
 *
 * [920] 播放列表的数量
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    const int MOD = 1000000007;
    
    int numMusicPlaylists(int n, int goal, int k)
    {
        vector<long long> fac(goal + 1), inv(goal + 1);
        fac[0] = 1;
        for (int i = 1; i <= goal; i++)
        {
			fac[i] = ((long) i * fac[i - 1]) % MOD;
		}

		inv[goal] = power(fac[goal], MOD - 2);
		for (int i = goal - 1; i >= 0; i--)
        {
			inv[i] = ((long) (i + 1) * inv[i + 1]) % MOD;
		}

        long long cur, ans = 0, sign = 1;
		for (int i = 0; i < n - k; i++, sign = (sign == 1 ? (MOD - 1) : 1))
        {
			cur = (sign * power(n - i - k, goal - k)) % MOD;
			cur = (cur * fac[n]) % MOD;
			cur = (cur * inv[i]) % MOD;
			cur = (cur * inv[n - i - k]) % MOD;
			ans = (ans + cur) % MOD;
		}
		return (int)ans;
    }

    long long power(long long x, int n) 
    {
		long long ans = 1;
		while (n > 0)
        {
			if ((n & 1) == 1)
            {
				ans = (ans * x) % MOD;
			}

			x = (x * x) % MOD;
			n >>= 1;
		}

		return ans;
	}
};
// @lc code=end

