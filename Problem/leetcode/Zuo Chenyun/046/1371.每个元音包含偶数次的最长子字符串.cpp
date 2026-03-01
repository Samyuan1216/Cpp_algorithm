/*
 * @lc app=leetcode.cn id=1371 lang=cpp
 *
 * [1371] 每个元音包含偶数次的最长子字符串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findTheLongestSubstring(string s)
    {
        int n = s.length();

        vector<int> mp(32, -2);
        mp[0] = -1;

        int ans = 0;
        for (int i = 0, status = 0, m = 0; i < n; i++)
        {
            m = move(s[i]);
            if (m != -1)
            {
                status ^= (1 << m);
            }

            if (mp[status] != -2)
            {
                ans = max(ans, i - mp[status]);
            }
            else
            {
                mp[status] = i;
            }
        }

        return ans;
    }

    int move(char cha)
    {
        switch(cha)
        {
        case 'a':
            return 0;
        case 'e':
            return 1;
        case 'i':
            return 2;
        case 'o':
            return 3;
        case 'u':
            return 4;
        default:
            return -1;
        }
    }
};
// @lc code=end

