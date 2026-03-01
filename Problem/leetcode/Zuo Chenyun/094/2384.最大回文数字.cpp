/*
 * @lc app=leetcode.cn id=2384 lang=cpp
 *
 * [2384] 最大回文数字
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string largestPalindromic(string num)
    {
        int n = num.length();

        vector<int> cnt(10);
        for (auto &c: num)
        {
            cnt[c - '0']++;
        }

        string s, mid = "10";
        for (int i = 9; i >= 1; i--)
        {
            if ((cnt[i] & 1) == 1 && mid == "10")
            {
                mid = to_string(i);
            }

            for (int j = cnt[i] / 2; j > 0; j--)
            {
                s += to_string(i);
            }
        }

        if (s.empty())
        {
            if (mid == "10")
            {
                return "0";
            }
            else
            {
                return mid;
            }
        }

        if ((cnt[0] & 1) == 1 && mid == "10")
        {
            mid = "0";
        }

        for (int j = cnt[0] / 2; j > 0; j--)
        {
            s += "0";
        }

        string ans;
        ans += s;

        if (mid != "10")
        {
            ans += mid;
        }

        reverse(s.begin(), s.end());
        ans += s;

        return ans;
    }
};
// @lc code=end

