/*
 * @lc app=leetcode.cn id=2370 lang=cpp
 *
 * [2370] 最长理想子序列
 */

// @lc code=start
#include <bits/stdc++.h>

const int n = 26;
int maxa[(n + 1) << 2];

class Solution
{
public:
    int longestIdealString(std::string s, int k)
    {
        std::fill(maxa, maxa + ((n + 1) << 2), 0);

        int ans = 0, v, p;
        for (auto &c: s)
        {
            v = c - 'a' + 1;
            p = query(std::max(v - k, 1), std::min(v + k, n), 1, n, 1);
            ans = std::max(ans, p + 1);

            update(v, p + 1, 1, n, 1);
        }

        return ans;
    }

    void up(int i)
    {
        maxa[i] = std::max(maxa[i << 1], maxa[i << 1 | 1]);
    }

    void update(int jobi, int jobv, int l, int r, int i)
    {
        if (l == r && l == jobi)
        {
            maxa[i] = jobv;
        }
        else
        {
            int mid = l + (r - l) / 2;

            if (jobi <= mid)
            {
                update(jobi, jobv, l, mid, i << 1);
            }
            else
            {
                update(jobi, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    int query(int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return maxa[i];
        }

        int mid = l + (r - l) / 2;

        int ans = 0;
        if (mid >= jobl)
        {
            ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
        }
        
        if (mid + 1 <= jobr)
        {
            ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
        }

        return ans;
    }
};
// @lc code=end

