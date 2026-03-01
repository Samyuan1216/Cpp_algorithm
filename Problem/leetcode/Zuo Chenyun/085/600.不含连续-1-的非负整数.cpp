/*
 * @lc app=leetcode.cn id=600 lang=cpp
 *
 * [600] 不含连续1的非负整数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findIntegers(int n)
    {
        vector<int> cnt(31);
        cnt[0] = 1;
        cnt[1] = 2;
        for (int i = 2; i <= 30; i++)
        {
            cnt[i] = cnt[i - 1] + cnt[i - 2];
        }

        int ans = 0;
        for (int i = 30; i >= -1; i--)
        {
            if (i == -1)
            {
                ans++;
                break;
            }

            if ((n & (1 << i)) != 0)
            {
                ans += cnt[i];
                if ((n & (1 << (i + 1))) != 0)
                {
                    break;
                }
            }
        }

        return ans;
    }
};
// @lc code=end

