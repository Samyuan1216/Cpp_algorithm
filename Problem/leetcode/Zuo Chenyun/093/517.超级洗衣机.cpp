/*
 * @lc app=leetcode.cn id=517 lang=cpp
 *
 * [517] 超级洗衣机
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findMinMoves(vector<int>& machines)
    {
        int n = machines.size(), sum = 0;
        for (auto &x: machines)
        {
            sum += x;
        }

        if (sum % n != 0)
        {
            return -1;
        }

        int avg = sum / n, left_sum = 0, left_need = 0, right_need = 0, bottom_need = 0, ans = 0;
        for (int i = 0; i < n; i++)
        {
            left_need = i * avg - left_sum;
            right_need = (n - i - 1) * avg - (sum - left_sum - machines[i]);

            if (left_need > 0 && right_need > 0)
            {
                bottom_need = left_need + right_need;
            }
            else
            {
                bottom_need = max(abs(left_need), abs(right_need));
            }

            ans = max(ans, bottom_need);
            left_sum += machines[i];
        }

        return ans;
    }
};
// @lc code=end

