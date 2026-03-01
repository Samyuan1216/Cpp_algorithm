/*
 * @lc app=leetcode.cn id=466 lang=cpp
 *
 * [466] 统计重复个数
 */

// @lc code=start
#include <bits/stdc++.h>

using ll = long long;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vll = std::vector<ll>;
using vvll = std::vector<vll>;

class Solution
{
public:
    int getMaxRepetitions(std::string s1, int n1, std::string s2, int n2)
    {
        int n = s1.length();
        
        vvi next(n, vi(26));
        if (!find(s1, s2, next, n))
        {
            return 0;
        }

        vvll st(n, vll(30));
        for (int i = 0, cur = 0; i < n; i++, cur = i)
        {
            for (auto &c: s2)
            {
                st[i][0] += next[cur][c - 'a'];
                cur = (cur + next[cur][c - 'a']) % n;
            }
        }

        for (int p = 1; p < 30; p++)
        {
            for (int i = 0; i < n; i++)
            {
                st[i][p] = st[i][p - 1] + st[(i + st[i][p - 1]) % n][p - 1];
            }
        }

        ll ans = 0;
        for (int p = 29, start = 0; p >= 0; p--)
        {
            if (st[start % n][p] + start <= n * n1)
            {
                ans += 1 << p;
                start += st[start % n][p];
            }
        }

        return (int)(ans / n2);
    }

    bool find(std::string &s1, std::string &s2, vvi &next, int n)
    {
        vi right(26, -1);
        for (int i = n - 1; i >= 0; i--)
        {
            right[s1[i] - 'a'] = i + n;
        }

        for (int i = n - 1; i >= 0; i--)
        {
            right[s1[i] - 'a'] = i;
            for (int j = 0; j < 26; j++)
            {
                if (right[j] != -1)
                {
                    next[i][j] = right[j] - i + 1;
                }
                else
                {
                    next[i][j] = -1;
                }
            }
        }

        for (auto &c: s2)
        {
            if (next[0][c - 'a'] == -1)
            {
                return false;
            }
        }

        return true;
    }
};
// @lc code=end

