/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int n = 2 * s.length() + 1;

        vector<char> ss = manacherss(s, n);

        vector<int> p(n);
        string ans;
        int maxn = 0;
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

            if (len > maxn)
            {
                maxn = len;

                string tmp;
                for (int j = i - len + 2; j <= i + len - 2; j += 2)
                {
                    tmp += ss[j];
                }
                ans = tmp;
            }

            p[i] = len;
        }

        return ans;
    }

    vector<char> manacherss(string &s, int n)
    {
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

        return ss;
    }
};
// @lc code=end

