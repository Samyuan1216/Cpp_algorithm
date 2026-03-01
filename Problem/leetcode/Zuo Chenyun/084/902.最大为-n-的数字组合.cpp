/*
 * @lc app=leetcode.cn id=902 lang=cpp
 *
 * [902] 最大为 N 的数字组合
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n)
    {
        int m = digits.size();
        vector<int> nums(m);
        for (int i = 0; i < m; i++)
        {
            nums[i] = stoi(digits[i]);
        }

        int offset = 1, len = 1, tmp = n / 10;
        while (tmp > 0)
        {
            len++;
            offset *= 10;
            tmp /= 10;
        }

        vector<int> cnt(len);
        cnt[0] = 1;
        int ans = 0;
        for (int i = m, k = 1; k < len; k++, i *= m)
        {
            cnt[k] = i;
            ans += i;
        }

        return ans + f(nums, cnt, n, offset, len);
    }

    int f(vector<int> &nums, vector<int> &cnt, int n, int offset, int len)
    {
        if (len == 0)
        {
            return 1;
        }

        int cur = (n / offset) % 10, ans = 0;
        for (auto &x: nums)
        {
            if (x < cur)
            {
                ans += cnt[len - 1];
            }
            else if (x == cur)
            {
                ans += f(nums, cnt, n, offset / 10, len - 1);
            }
            else
            {
                break;
            }
        }

        return ans;
    }
};
// @lc code=end

