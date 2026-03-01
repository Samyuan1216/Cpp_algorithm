/*
 * @lc app=leetcode.cn id=514 lang=cpp
 *
 * [514] 自由之路
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 110, MAXC = 26;
vvi where(MAXC, vi(MAXN)), dp(MAXN, vi(MAXN));
vi r(MAXN), k(MAXN), siz(MAXC);
int n, m;

class Solution
{
public:
    void build(string &ring, string &key)
    {
        fill(siz.begin(), siz.end(), 0);

        n = ring.length();
        m = key.length();

        for (int i = 0, v; i < n; i++)
        {
            v = ring[i] - 'a';
            where[v][siz[v]++] = i;
            r[i] = v;
        }

        for (int i = 0; i < m; i++)
        {
            k[i] = key[i] - 'a';
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                dp[i][j] = -1;
            }
        }
    }

    int findRotateSteps(string ring, string key)
    {
        build(ring, key);
        return f(0, 0);
    }

    int f(int i, int j)
    {
        if (j == m)
        {
            return 0;
        }

        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }

        int ans;
        if (r[i] == k[j])
        {
            ans = 1 + f(i, j + 1);
        }
        else
        {
            int jump1 = clo(i, k[j]);
            int distance1 = (jump1 > i? (jump1 - i): (n - i + jump1));

            int jump2 = cclo(i, k[j]);
            int distance2 = (i > jump2? (i - jump2): (n - jump2 + i));

            ans = min(distance1 + f(jump1, j), distance2 + f(jump2, j));
        }

        dp[i][j] = ans;
        return ans;
    }

    int clo(int i, int v)
    {
        int l = 0, r = siz[v] - 1, m;
        vi sorted = where[v];
        int find = -1;
        while (l <= r)
        {
            m = l + ((r - l) >> 1);
            if (sorted[m] > i)
            {
                find = m;
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        return (find != -1? sorted[find]: sorted[0]);
    }

    int cclo(int i, int v)
    {
        int l = 0, r = siz[v] - 1, m;
        vi sorted = where[v];
        int find = -1;
        while (l <= r)
        {
            m = l + ((r - l) >> 1);
            if (sorted[m] < i)
            {
                find = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        return (find != -1? sorted[find]: sorted[siz[v] - 1]);
    }
};
// @lc code=end

