/*
 * @lc app=leetcode.cn id=2719 lang=cpp
 *
 * [2719] 统计整数数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

const int MAXN = 23, MAXM = 410, MOD = 1000000007;
vvvi dp(MAXN, vvi(MAXM, vi(2)));
int minn, maxn, len;
string s;

class Solution
{
public:
    int count(string num1, string num2, int min_sum, int max_sum)
    {
        minn = min_sum;
        maxn = max_sum;

        s = num2;
        len = num2.length();        
        build();

        int ans = f(0, 0, 0);

        s = num1;
        len = num1.length();
        build();

        ans = (ans - f(0, 0, 0) + MOD) % MOD;

        if (check())
        {
            ans = (ans + 1) % MOD;
        }

        return ans;
    }

    void build()
    {
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j <= maxn; j++)
            {
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
            }
        }
    }

    int f(int i, int sum, int free)
    {
        if (sum > maxn)
        {
            return 0;
        }

        if (sum + (len - i) * 9 < minn)
        {
            return 0;
        }

        if (i == len)
        {
            return 1;
        }

        if (dp[i][sum][free] != -1)
        {
            return dp[i][sum][free];
        }

        int cur = s[i] - '0', ans = 0;
        if (free == 0)
        {
            for (int pick = 0; pick < cur; pick++)
            {
                ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
            }

            ans = (ans + f(i + 1, sum + cur, 0)) % MOD;
        }
        else
        {
            for (int pick = 0; pick <= 9; pick++)
            {
                ans = (ans + f(i + 1, sum + pick, 1)) % MOD;
            }
        }

        dp[i][sum][free] = ans;
        return ans;
    }

    bool check()
    {
        int sum = 0;
        for (auto &c: s)
        {
            sum += c - '0';
        }

        return sum <= maxn && sum >= minn;
    }
};
// @lc code=end

