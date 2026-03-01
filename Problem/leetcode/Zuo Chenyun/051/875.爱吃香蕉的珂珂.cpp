/*
 * @lc app=leetcode.cn id=875 lang=cpp
 *
 * [875] 爱吃香蕉的珂珂
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minEatingSpeed(vector<int>& piles, int h)
    {
        int maxn = 0;
        for (auto &x: piles)
        {
            maxn = max(maxn, x);
        }

        int ans = 0;
        for (int l = 1, r = maxn, m = 0; l <= r;)
        {
            m = l + ((r - l) >> 1);
            if (f(piles, m) <= h)
            {
                ans = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return ans;
    }

    long long f(vector<int> &piles, int speed)
    {
        long long ans = 0;
        for (int &pile: piles)
        {
            ans += (pile + speed - 1) / speed;
        }

        return ans;
    }
};
// @lc code=end

