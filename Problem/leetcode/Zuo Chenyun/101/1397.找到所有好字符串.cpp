/*
 * @lc app=leetcode.cn id=1397 lang=cpp
 *
 * [1397] 找到所有好字符串
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

const int MAXN = 510, MAXM = 55, MOD = 1000000007;
vvvi dp(MAXN, vvi(MAXM, vi(2)));
vi ne(MAXM);

class Solution
{
public:
    void clear(int n, int m)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
            }
        }
    }

    int findGoodStrings(int n, string s1, string s2, string evil)
    {
        int m = evil.length();
        next_array(evil, m);

        clear(n, m);
        int ans = f(s2, evil, n, m, 0, 0, 0);

        clear(n, m);
        ans = (ans - f(s1, evil, n, m, 0, 0, 0) + MOD) % MOD;

        if (kmp(s1, evil, n, m) == -1)
        {
            ans = (ans + 1) % MOD;
        }

        return ans;
    }

    int f(string &str, string &evil, int n, int m, int i, int j, int free)
    {
        if (j == m)
        {
            return 0;
        }

        if (i == n)
        {
            return 1;
        }

        if (dp[i][j][free] != -1)
        {
            return dp[i][j][free];
        }

        char cur = str[i];
        int ans = 0;
        if (free == 0)
        {
            for (char pick = 'a'; pick < cur; pick++)
            {
                ans = (ans + f(str, evil, n, m, i + 1, jump(pick, evil, j) + 1, 1)) % MOD;
            }
            ans = (ans + f(str, evil, n, m, i + 1, jump(cur, evil, j) + 1, 0)) % MOD;
        }
        else
        {
            for (char pick = 'a'; pick <= 'z'; pick++)
            {
                ans = (ans + f(str, evil, n, m, i + 1, jump(pick, evil, j) + 1, 1)) % MOD;
            }
        }

        dp[i][j][free] = ans;
        return ans;
    }

    int jump(char pick, string &evil, int j)
    {
        while (j >= 0 && pick != evil[j])
        {
            j = ne[j];
        }

        return j;
    }

    void next_array(string &evil, int m)
    {
        ne[0] = -1;
        ne[1] = 0;

        int i = 2, cn = 0;
        while (i < m)
        {
            if (evil[i - 1] == evil[cn])
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
    }

    int kmp(string &str1, string &str2, int n, int m)
    {
        int x = 0, y = 0;
        while (x < n && y < m)
        {
            if (str1[x] == str2[y])
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
};
// @lc code=end

