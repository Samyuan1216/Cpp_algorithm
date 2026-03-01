/*
 * @lc app=leetcode.cn id=229 lang=cpp
 *
 * [229] 多数元素 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> majorityElement(vector<int>& nums)
    {
        return majority(nums, 3);
    }

    vector<int> majority(vector<int> &nums, int k)
    {
        vector<vector<int>> cands(--k, vector<int>(2));
        for (auto &num: nums)
        {
            update(cands, k, num);
        }

        vector<int> ans;
        collect(cands, k, nums, nums.size(), ans);

        return ans;
    }

    void update(vector<vector<int>> &cands, int k, int num)
    {
        for (int i = 0; i < k; i++)
        {
            if (cands[i][0] == num && cands[i][1] > 0)
            {
                cands[i][1]++;
                return;
            }
        }

        for (int i = 0; i < k; i++)
        {
            if (cands[i][1] == 0)
            {
                cands[i][0] = num;
                cands[i][1] = 1;
                return;
            }
        }

        for (int i = 0; i < k; i++)
        {
            if (cands[i][1] > 0)
            {
                cands[i][1]--;
            }
        }
    }

    void collect(vector<vector<int>> &cands, int k, vector<int> &nums, int n, vector<int> &ans)
    {
        for (int i = 0, cur, real; i < k; i++)
        {
            if (cands[i][1] > 0)
            {
                cur = cands[i][0];
                real = 0;

                for (auto &num: nums)
                {
                    if (num == cur)
                    {
                        real++;
                    }
                }

                if (real > n / (k + 1))
                {
                    ans.push_back(cur);
                }
            }
        }
    }
};
// @lc code=end

