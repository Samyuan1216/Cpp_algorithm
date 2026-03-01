/*
 * @lc app=leetcode.cn id=2926 lang=cpp
 *
 * [2926] 平衡子序列的最大和
 */

// @lc code=start
#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 100010;
int sor[MAXN];
ll tree[MAXN];
int n, m;

class Solution
{
public:
    long long maxBalancedSubsequenceSum(std::vector<int> &nums)
    {
        build(nums);

        ll pre;
        for (int i = 0, k; i < n; i++)
        {
            k = find(nums[i] - i);
            pre = maxt(k);
            if (pre < 0)
            {
                update(k, nums[i]);
            }
            else
            {
                update(k, pre + nums[i]);
            }
        }

        return maxt(m);
    }

    int find(int v)
    {
        int ans = 0, l = 1, r = m, mid;
        while (l <= r)
        {
            mid = l + (r - l) / 2;
            if (sor[mid] <= v)
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

    void build(std::vector<int> &nums)
    {
        n = nums.size();
        for (int i = 1, j = 0; i <= n; i++, j++)
        {
            sor[i] = nums[j] - j;
        }

        std::sort(sor + 1, sor + n + 1);
        m = std::unique(sor + 1, sor + n + 1) - (sor + 1);

        std::fill(tree + 1, tree + m + 1, INT64_MIN);
    }

    int lowbit(int i)
    {
        return i & -i;
    }

    void update(int i, ll v)
    {
        while (i <= m)
        {
            tree[i] = std::max(tree[i], v);
            i += lowbit(i);
        }
    }

    ll maxt(int i)
    {
        ll ans = INT64_MIN;
        while (i > 0)
        {
            ans = std::max(ans, tree[i]);
            i -= lowbit(i);
        }

        return ans;
    }
};
// @lc code=end

