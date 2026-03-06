// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s)
    {
        using i64 = int64_t;
        string low = to_string(start), high = to_string(finish);

        int n = high.length();
        low = string(n - low.length(), '0') + low;
        cout << low << "\n" << high << "\n";

        int diff = n - s.length();
        cout << diff << "\n";
        vector<vector<vector<i64>>> dp(n, vector<vector<i64>>(2, vector<i64>(2, -1)));
        auto digit_dp = [&](auto &&self, int i, bool limit_low, bool limit_high) -> i64
        {
            if (i == n)
            {
                return 1;
            }

            if (dp[i][limit_low][limit_high] != -1)
            {
                return dp[i][limit_low][limit_high];
            }

            int lo = (limit_low? (low[i] - '0'): 0), hi = (limit_high? (high[i] - '0'): 9);
            i64 ans = 0;
            if (i < diff)
            {
                for (int d = lo; d <= min(hi, limit); ++d)
                {
                    ans += self(self, i + 1, limit_low && d == lo, limit_high && d == hi);
                }
            }
            else
            {
                int x = s[i - diff] - '0';
                if (x >= lo && x <= min(hi, limit))
                {
                    ans = self(self, i + 1, limit_low && x == lo, limit_high && x == hi);
                }
            }

            dp[i][limit_low][limit_high] = ans;
            return ans;
        };

        return digit_dp(digit_dp, 0, true, true);
    }
};
// @leet end
