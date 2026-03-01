// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int countEval(string s, int result)
    {
        int n = s.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));
        vector<int> ft = fa(dp, s, 0, n - 1);

        return ft[result];
    }

    vector<int> fa(vector<vector<vector<int>>> &dp, string &s, int l, int r)
    {
        if (dp[l][r].empty() == false)
        {
            return dp[l][r];
        }

        int f = 0, t = 0;
        if (l == r)
        {
            f = (s[l] == '0'? 1: 0);
            t = (s[l] == '1'? 1: 0);
        }
        else
        {
            vector<int> tmp;
            for (int k = l + 1, a = 0, b = 0, c = 0, d = 0; k < r; k += 2)
            {
                tmp = fa(dp, s, l, k - 1);
                a = tmp[0];
                b = tmp[1];

                tmp = fa(dp, s, k + 1, r);
                c = tmp[0];
                d = tmp[1];

                if (s[k] == '&')
                {
                    f += a * c + a * d + b * c;
                    t += b * d;
                }
                else if (s[k] == '|')
                {
                    f += a * c;
                    t += a * d + b * c + b * d;
                }
                else
                {
                    f += a * c + b * d;
                    t += a * d + b * c;
                }
            }
        }

        dp[l][r] = vector<int>{f, t};

        return dp[l][r];
    }
};
// @lc code=end

