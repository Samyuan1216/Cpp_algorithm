/*
 * @lc app=leetcode.cn id=1235 lang=cpp
 *
 * [1235] 规划兼职工作
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 50010;
vvi jobs(MAXN, vi(3));
vi dp(MAXN);

class Solution
{
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit)
    {
        int n = startTime.size();
        for (int i = 0; i < n; i++)
        {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }

        sort(jobs.begin(), jobs.begin() + n, [](vi &a, vi &b)
        {
            return a[1] < b[1];
        });

        dp[0] = jobs[0][2];
        for (int i = 1, start; i < n; i++)
        {
            start = jobs[i][0];
            dp[i] = jobs[i][2];

            if (jobs[0][1] <= start)
            {
                dp[i] += dp[find(i - 1, start)];
            }

            dp[i] = max(dp[i], dp[i - 1]);
        }

        return dp[n - 1];
    }

    int find(int i, int start)
    {
        int ans = 0;
        for (int l = 0, r = i, m; l <= r;)
        {
            m = l + ((r - l) >> 1);
            if (jobs[m][1] <= start)
            {
                ans = m;
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }

        return ans;
    }
};
// @lc code=end

