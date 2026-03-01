/*
 * @lc app=leetcode.cn id=1125 lang=cpp
 *
 * [1125] 最小的必要团队
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people)
    {
        int n = req_skills.size(), m = people.size();
        
        unordered_map<string, int> mp;
        int cnt = 0;
        for (auto &s: req_skills)
        {
            mp[s] = cnt++;
        }

        vector<int> arr(m);
        for (int i = 0, status; i < m; i++)
        {
            status = 0;
            for (auto &s: people[i])
            {
                if (mp.find(s) != mp.end())
                {
                    status |= (1 << mp[s]);
                }
            }

            arr[i] = status;
        }

        vector<vector<int>> dp(m, vector<int>(1 << n, -1));
        int size = f(arr, n, m, 0, 0, dp);

        vector<int> ans(size);
        for (int i = 0, j = 0, s = 0; s != (1 << n) - 1; i++)
        {
            if (i == m - 1 || dp[i][s] != dp[i + 1][s])
            {
                ans[j++] = i;
                s |= arr[i];
            }
        }

        return ans;
    }

    int f(vector<int> &arr, int n, int m, int i, int s, vector<vector<int>> &dp)
    {
        if (s == (1 << n) - 1)
        {
            return 0;
        }

        if (i == m)
        {
            return INT32_MAX;
        }

        if (dp[i][s] != -1)
        {
            return dp[i][s];
        }

        int p1 = f(arr, n, m, i + 1, s, dp);

        int p2 = INT32_MAX;
        int next2 = f(arr, n, m, i + 1, s | arr[i], dp);
        if (next2 != INT32_MAX)
        {
            p2 = 1 + next2;
        }

        int ans = min(p1, p2);
        dp[i][s] = ans;
        return ans;
    }
};
// @lc code=end

