/*
 * @lc app=leetcode.cn id=686 lang=cpp
 *
 * [686] 重复叠加字符串匹配
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using vull = vector<ull>;

const int MAXN = 30010, base = 499;
vull p(MAXN), ha(MAXN);
int n, m, k, len;

class Solution
{
public:
    int repeatedStringMatch(string a, string b)
    {
        n = a.length(), m = b.length();
        k = (m + n - 1) / n;

        string s;
        for (int cnt = 0; cnt <= k; cnt++)
        {
            s += a;
        }

        build(s);

        ull h2 = b[0] - 'a' + 1;
        for (int i = 1; i < m; i++)
        {
            h2 = h2 * base + b[i] - 'a' + 1;
        }

        for (int l = 0, r = m - 1; r < len; l++, r++)
        {
            if (h2 == h(l, r))
            {
                return (r < n * k? k: (k + 1));
            }
        }

        return -1;
    }

    void build(string &s)
    {
        len = s.length();

        p[0] = 1;
        for (int i = 1; i < len; i++)
        {
            p[i] = p[i - 1] * base;
        }

        ha[0] = s[0] - 'a' + 1;
        for (int i = 1; i < len; i++)
        {
            ha[i] = ha[i - 1] * base + s[i] - 'a' + 1;
        }
    }

    ull h(int l, int r)
    {
        ull ans = ha[r];
        if (l > 0)
        {
            ans -= ha[l - 1] * p[r - l + 1];
        }

        return ans;
    }
};
// @lc code=end

