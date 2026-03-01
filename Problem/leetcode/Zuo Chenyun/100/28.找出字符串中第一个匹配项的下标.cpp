/*
 * @lc app=leetcode.cn id=28 lang=cpp
 *
 * [28] 找出字符串中第一个匹配项的下标
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        int n = haystack.length(), m = needle.length(), x = 0, y = 0;
        vector<int> ne = next_array(needle, m);

        while (x < n && y < m)
        {
            if (haystack[x] == needle[y])
            {
                x++;
                y++;
            }
            else if (y == 0)
            {
                x++;
            }
            else
            {
                y = ne[y];
            }
        }

        return (y == m? x - y: -1);
    }

    vector<int> next_array(string &needle, int m)
    {
        if (m == 1)
        {
            return vector<int>{-1};
        }

        vector<int> ne(m);
        ne[0] = -1;
        ne[1] = 0;

        int i = 2, cn = 0;
        while (i < m)
        {
            if (needle[i - 1] == needle[cn])
            {
                ne[i++] = ++cn;
            }
            else if (cn > 0)
            {
                cn = ne[cn];
            }
            else
            {
                ne[i++] = 0;
            }
        }

        return ne;
    }
};
// @lc code=end

