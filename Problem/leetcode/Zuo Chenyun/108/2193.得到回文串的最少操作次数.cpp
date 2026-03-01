/*
 * @lc app=leetcode.cn id=2193 lang=cpp
 *
 * [2193] 得到回文串的最少操作次数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 2010, MAXV = 26;
vi eds(MAXV), pre(MAXN), diff(MAXN), help(MAXN);
int n;

namespace BIT
{
    vi tree(MAXN);

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(int i, int v)
    {
        while (i <= n)
        {
            tree[i] += v;
            i += lowbit(i);
        }
    }

    int query(int i)
    {
        int ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }
} // namespace BIT

class Solution
{
public:
    int minMovesToMakePalindrome(string s)
    {
        n = s.length();
        build();

        for (int i = 0, j = 1; i < n; i++, j++)
        {
            push(s[i] - 'a', j);
        }

        for (int i = 0, l = 1, r, k; i < n; i++, l++)
        {
            if (diff[l] == 0)
            {
                r = pop(s[i] - 'a');
                if (l < r)
                {
                    k = BIT::query(l);
                    diff[l] = k;
                    diff[r] = n - k + 1;
                }
                else
                {
                    diff[l] = (1 + n) / 2;
                }

                BIT::add(r, -1);
            }
        }

        return number(1, n);
    }

    void build()
    {
        fill(eds.begin(), eds.end(), 0);
        fill(diff.begin() + 1, diff.begin() + n + 1, 0);
        fill(BIT::tree.begin() + 1, BIT::tree.begin() + n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            BIT::add(i, 1);
        }
    }

    void push(int v, int j)
    {
        pre[j] = eds[v];
        eds[v] = j;
    }

    int pop(int v)
    {
        int ans = eds[v];
        eds[v] = pre[eds[v]];

        return ans;
    }

    int number(int l, int r)
    {
        if (l >= r)
        {
            return 0;
        }

        int m = l + ((r - l) >> 1);
        return number(l, m) + number(m + 1, r) + merge(l, m, r);
    }

    int merge(int l, int m, int r)
    {
        int ans = 0;
        for (int i = m, j = r; i >= l; i--)
        {
            while (j >= m + 1 && diff[i] <= diff[j])
            {
                j--;
            }

            ans += j - m;
        }

        int i = l, a = l, b = m + 1;
        while (a <= m && b <= r)
        {
            help[i++] = (diff[a] <= diff[b]? diff[a++]: diff[b++]);
        }

        while(a <= m)
        {
            help[i++] = diff[a++];
        }

        while (b <= r)
        {
            help[i++] = diff[b++];
        }

        for (int i = l; i <= r; i++)
        {
            diff[i] = help[i];
        }

        return ans;
    }
};
// @lc code=end

