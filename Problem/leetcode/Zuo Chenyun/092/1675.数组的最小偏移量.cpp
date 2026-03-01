/*
 * @lc app=leetcode.cn id=1675 lang=cpp
 *
 * [1675] 数组的最小偏移量
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minimumDeviation(vector<int>& nums)
    {
        set<int> s;
        for (auto &num: nums)
        {
            if ((num & 1) == 0)
            {
                s.insert(num);
            }
            else
            {
                s.insert(num * 2);
            }
        }

        int ans = *s.rbegin() - *s.begin();
        while (ans > 0 && (*s.rbegin() & 1) == 0)
        {
            int maxn = *s.rbegin();
            s.erase(maxn);
            s.insert(maxn / 2);
            
            ans = min(ans, *s.rbegin() - *s.begin());
        }

        return ans;
    }
};
// @lc code=end

