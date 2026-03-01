/*
 * @lc app=leetcode.cn id=316 lang=cpp
 *
 * [316] 去除重复字母
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        vector<int> cnt(26);
        for (auto &c: s)
        {
            cnt[c - 'a']++;
        }

        vector<int> st(26), enter(26);
        int r = -1;

        for (auto &c: s)
        {
            if (enter[c - 'a'] == 0)
            {
                while (r >= 0 && c < st[r] && cnt[st[r] - 'a'] > 0)
                {
                    enter[st[r] - 'a'] = 0;
                    r--;
                }

                st[++r] = c;
                enter[c - 'a'] = 1;
            }

            cnt[c - 'a']--;
        }

        string ans;
        for (int i = 0; i <= r; i++)
        {
            ans += st[i];
        }

        return ans;
    }
};
// @lc code=end

