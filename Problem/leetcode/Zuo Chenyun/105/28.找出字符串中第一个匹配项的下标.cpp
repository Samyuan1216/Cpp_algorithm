/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 找出字符串中第一个匹配项的下标
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vull = vector<ull>;

const int MAXN = 10010, BASE = 499;
vull power(MAXN), ha(MAXN);

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        build(haystack);

        ull h2 = needle[0] - 'a' + 1;
        for (int i = 1; i < needle.length(); i++)
        {
            h2 = h2 * BASE + needle[i] - 'a' + 1;
        }

        for (int l = 0, r = needle.length() - 1; r < haystack.length(); l++, r++)
        {
            if (h2 == h(l, r))
            {
                return l;
            }
        }

        return -1;
    }

    void build(string &haystack)
    {
        power[0] = 1;
        for (int i = 1; i < haystack.length(); i++)
        {
            power[i] = power[i - 1] * BASE;
        }

        ha[0] = haystack[0] - 'a' + 1;
        for (int i = 1; i < haystack.length(); i++)
        {
            ha[i] = ha[i - 1] * BASE + haystack[i] - 'a' + 1;
        }
    }

    ull h(int l, int r)
    {
        ull ans = ha[r];
        if (l > 0)
        {
            ans -= ha[l - 1] * power[r - l + 1];
        }

        return ans;
    }
};
// @lc code=end

