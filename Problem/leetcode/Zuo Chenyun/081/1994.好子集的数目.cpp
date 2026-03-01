/*
 * @lc app=leetcode.cn id=1994 lang=cpp
 *
 * [1994] 好子集的数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 30, LIMIT = (1 << 10), MOD = 1000000007;
vector<int> own
{
    0b0000000000, // 0
    0b0000000000, // 1
    0b0000000001, // 2
    0b0000000010, // 3
    0b0000000000, // 4
    0b0000000100, // 5
    0b0000000011, // 6
    0b0000001000, // 7
    0b0000000000, // 8
    0b0000000000, // 9
    0b0000000101, // 10
    0b0000010000, // 11
    0b0000000000, // 12
    0b0000100000, // 13
    0b0000001001, // 14
    0b0000000110, // 15
    0b0000000000, // 16
    0b0001000000, // 17
    0b0000000000, // 18
    0b0010000000, // 19
    0b0000000000, // 20
    0b0000001010, // 21
    0b0000010001, // 22
    0b0100000000, // 23
    0b0000000000, // 24
    0b0000000000, // 25
    0b0000100001, // 26
    0b0000000000, // 27
    0b0000000000, // 28
    0b1000000000, // 29
    0b0000000111 // 30
};

vector<int> cnt(MAXV + 1), dp(LIMIT);

class Solution
{
public:
    int numberOfGoodSubsets(vector<int>& nums)
    {
        fill(cnt.begin(), cnt.end(), 0);
        fill(dp.begin(), dp.end(), 0);

        for (auto &num: nums)
        {
            cnt[num]++;
        }

        dp[0] = 1;
        for (int i = 0; i < cnt[1]; i++)
        {
            dp[0] = (dp[0] << 1) % MOD;
        }

        for (int i = 2, cur, times; i <= MAXV; i++)
        {
            cur = own[i];
            times = cnt[i];

            if (cur != 0 && times != 0)
            {
                for (int status = LIMIT - 1; status >= 0; status--)
                {
                    if ((status & cur) == cur)
                    {
                        dp[status] = (int)(((long long)dp[status ^ cur] * times + dp[status]) % MOD);
                    }
                }
            }
        }

        int ans = 0;
        for (int s = 1; s < LIMIT; s++)
        {
            ans = (ans + dp[s]) % MOD;
        }

        return ans;
    }
};
// @lc code=end

