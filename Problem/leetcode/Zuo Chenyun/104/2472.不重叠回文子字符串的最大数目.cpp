/*
 * @lc app=leetcode.cn id=2472 lang=cpp
 *
 * [2472] 不重叠回文子字符串的最大数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vc = vector<char>;

const int MAXN = 2010;
vc ss(MAXN << 1);
vi p(MAXN << 1);
int n;

class Solution
{
public:
    int maxPalindromes(string s, int k)
    {
        n = 2 * s.length() + 1;
        manacherss(s);

        int next = 0, ans = 0;
        while ((next = find(next, k)) != -1)
        {
            ans++;
        }

        return ans;
    }

    void manacherss(string &s)
    {
        for (int i = 0, j = 0; i < n; i++)
        {
            ss[i] = (i & 1? s[j++]: '#');
        }
    }

    int find(int l, int k)
    {
        for (int i = l, c = l, r = l, len; i < n; i++)
        {
            len = (i < r? min(r - i, p[2 * c - i]): 1);
            while (i + len < n && i - len >= l && ss[i + len] == ss[i - len])
            {
                if (++len > k)
                {
                    return i + k + (ss[i + k] == '#'? 0: 1);
                }
            }

            if (i + len > r)
            {
                r = i + len;
                c = i;
            }

            p[i] = len;
        }

        return -1;
    }
};
// @lc code=end

