/*
 * @lc app=leetcode.cn id=647 lang=cpp
 *
 * [647] 回文子串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countSubstrings(string s)
    {
        int n = 2 * s.length() + 1;

        vector<char> ss(n);
        for (int i = 0, j = 0; i < n; i++)
        {
            if (i & 1)
            {
                ss[i] = s[j++];
            }
            else
            {
                ss[i] = '#';
            }
        }

        vector<int> p(n);
        int ans = 0;
        for (int i = 0, c = 0, r = 0, len; i < n; i++)
        {
            len = (i < r? min(r - i, p[2 * c - i]): 1);
            while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len])
            {
                len++;
            }

            if (i + len > r)
            {
                r = i + len;
                c = i;
            }

            ans += len / 2;
            p[i] = len;
        }

        return ans;
    }
};
// @lc code=end

