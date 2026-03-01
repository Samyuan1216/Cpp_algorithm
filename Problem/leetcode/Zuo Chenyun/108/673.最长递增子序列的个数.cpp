/*
 * @lc app=leetcode.cn id=673 lang=cpp
 *
 * [673] 最长递增子序列的个数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 2010;
vi diff(MAXN), arr_s(MAXN);
int n, m;

namespace BIT
{
    vi tree1(MAXN), tree2(MAXN);

    int lowbit(int i)
    {
        return i & -i;
    }

    int max_len, max_len_cnt;
    void query(int i)
    {
        max_len = max_len_cnt = 0;
        while (i > 0)
        {
            if (max_len == tree1[i])
            {
                max_len_cnt += tree2[i];
            }
            else if (max_len < tree1[i])
            {
                max_len = tree1[i];
                max_len_cnt = tree2[i];
            }

            i -= lowbit(i);
        }
    }

    void add(int i, int len, int cnt)
    {
        while (i <= m)
        {
            if (len == tree1[i])
            {
                tree2[i] += cnt;
            }
            else if (len > tree1[i])
            {
                tree1[i] = len;
                tree2[i] = cnt;
            }

            i += lowbit(i);
        }
    }
}

class Solution
{
public:
    int findNumberOfLIS(vector<int>& nums)
    {
        build(nums);

        for (int i = 1; i <= n; i++)
        {
            BIT::query(diff[i] - 1);
            BIT::add(diff[i], BIT::max_len + 1, max(BIT::max_len_cnt, 1));
        }

        BIT::query(m);
        return BIT::max_len_cnt;
    }

    void build(vi &nums)
    {
        n = nums.size();
        for (int i = 1; i <= n; i++)
        {
            diff[i] = arr_s[i] = nums[i - 1];
        }

        sort(arr_s.begin() + 1, arr_s.begin() + n + 1);
        m = unique(arr_s.begin() + 1, arr_s.begin() + n + 1) - arr_s.begin() - 1;

        for (int i = 1; i <= n; i++)
        {
            diff[i] = fin(diff[i]);
        }

        fill(BIT::tree1.begin(), BIT::tree1.end(), 0);
        fill(BIT::tree2.begin(), BIT::tree2.end(), 0);
    }

    int fin(int v)
    {
        int ans = 0;
        for (int l = 1, r = m, mid; l <= r;)
        {
            mid = l + ((r - l) >> 1);
            if (arr_s[mid] <= v)
            {
                ans = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }

        return ans;
    }
};
// @lc code=end

