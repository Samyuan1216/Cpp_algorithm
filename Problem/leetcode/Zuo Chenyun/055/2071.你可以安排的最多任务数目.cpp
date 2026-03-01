/*
 * @lc app=leetcode.cn id=2071 lang=cpp
 *
 * [2071] 你可以安排的最多任务数目
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength)
    {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());

        int tn = tasks.size(), wn = workers.size(), ans = 0;
        for (int l = 0, r = min(tn, wn), m = 0; l <= r;)
        {
            m = (l + r) / 2;
            if (ok(tasks, workers, 0, m - 1, wn - m, wn - 1, pills, strength) == true)
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

    bool ok(vector<int> &tasks, vector<int> &workers, int tl, int tr, int wl, int wr, int pills, int strength)
    {
        vector<int> dq(tr - tl + 1);
        int h = 0, t = 0;

        int cnt = 0;
        for (int i = wl, j = tl; i <= wr; i++)
        {
            for (; j <= tr && tasks[j] <= workers[i]; j++)
            {
                dq[t++] = j;
            }

            if (h < t && tasks[dq[h]] <= workers[i])
            {
                h++;
            }
            else
            {
                for (; j <= tr && tasks[j] <= workers[i] + strength; j++)
                {
                    dq[t++] = j;
                }

                if (h < t)
                {
                    cnt++;
                    t--;
                }
                else
                {
                    return false;
                }
            }
        }

        return cnt <= pills;
    }
};
// @lc code=end

