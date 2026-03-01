/*
 * @lc app=leetcode.cn id=1755 lang=cpp
 *
 * [1755] 最接近目标值的子序列和
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    const int MAXN = 1 << 20;
    vector<int> lsum = vector<int>(MAXN), rsum = vector<int>(MAXN);
    int fill;

    int minAbsDifference(vector<int>& nums, int goal)
    {
        int n = nums.size();

        long long minn = 0, maxn = 0;
        for (int i = 0; i < n; i++)
        {
            if (nums[i] < 0)
            {
                minn += nums[i];
            }
            else
            {
                maxn += nums[i];
            }
        }

        if (minn >= goal)
        {
            return (int)abs(minn - goal);
        }
        
        if (maxn <= goal)
        {
            return (int)abs(maxn - goal);
        }

        sort(nums.begin(), nums.end());

        fill = 0;
        collection(nums, 0, n >> 1, 0, lsum);
        int lsize = fill;

        fill = 0;
        collection(nums, n >> 1, n, 0, rsum);
        int rsize = fill;

        sort(lsum.begin(), lsum.begin() + lsize);
        sort(rsum.begin(), rsum.begin() + rsize);

        int ans = abs(goal);
        for (int i = 0, j = rsize - 1; i < lsize; i++)
        {
            while (j > 0 && abs(goal - lsum[i] - rsum[j - 1]) <= abs(goal - lsum[i] - rsum[j]))
            {
                j--;
            }

            ans = min(ans, abs(goal - lsum[i] - rsum[j]));
        }

        return ans;
    }

    void collection(vector<int>& nums, int i, int e, int s, vector<int>& sum)
    {
        if (i == e)
        {
            sum[fill++] = s;
        }
        else
        {
            int j = i + 1;
            while (j < e && nums[j] == nums[i])
            {
                j++;
            }

            for (int k = 0; k <= j - i; k++)
            {
                collection(nums, j, e, s + k * nums[i], sum);
            }
        }
    }
};
// @lc code=end

