/*
 * @lc app=leetcode.cn id=327 lang=cpp
 *
 * [327] 区间和的个数
 */

// @lc code=start
#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 100010;
ll sor[MAXN];
int tree[MAXN];
int n, m;

// 树状数组
class Solution
{
public:
    int countRangeSum(std::vector<int> &nums, int lower, int upper)
    {
        build(nums);

        ll sumn = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            sumn += nums[i];
            ans += sum(find(sumn - lower)) - sum(find(sumn - upper - 1));
            if (sumn >= lower && sumn <= upper)
            {
                ans++;
            }

            add(find(sumn), 1);
        }

        return ans;
    }

    void build(std::vector<int> &nums)
    {
        n = nums.size();
        for (int i = 1; i <= n; i++)
        {
            sor[i] = sor[i - 1] + nums[i - 1];
        }

        std::sort(sor + 1, sor + n + 1);
        m = std::unique(sor + 1, sor + n + 1) - (sor + 1);

        std::fill(tree + 1, tree + m + 1, 0);
    }

    int find(ll v)
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

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(int i, int c)
    {
        while (i <= m)
        {
            tree[i] += c;
            i += lowbit(i);
        }
    }

    int sum(int i)
    {
        int ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }
};

// 归并分治
// const int MAXN = 100010;
// ll sum[MAXN], help[MAXN];
// int low, up;

// class Solution
// {
// public:
//     int countRangeSum(std::vector<int>& nums, int lower, int upper)
//     {
//         int n = nums.size();
//         sum[0] = nums[0];
//         for (int i = 1; i < n; i++)
//         {
//             sum[i] = sum[i - 1] + nums[i];
//         }

//         low = lower, up = upper;
//         return dfs(0, n - 1);
//     }

//     int dfs(int l, int r)
//     {
//         if (l == r)
//         {
//             return (sum[l] >= low && sum[l] <= up? 1: 0);
//         }

//         int mid = l + (r - l) / 2;
//         return dfs(l, mid) + dfs(mid + 1, r) + merge(l, mid, r);
//     }

//     int merge(int l, int mid, int r)
//     {
//         int ans = 0, wl = l, wr = l;
//         ll maxn, minn;
//         for (int i = mid + 1; i <= r; i++)
//         {
//             maxn = sum[i] - low, minn = sum[i] - up;
//             while (wr <= mid && sum[wr] <= maxn)
//             {
//                 wr++;
//             }

//             while (wl <= mid && sum[wl] < minn)
//             {
//                 wl++;
//             }

//             ans += wr - wl;
//         }

//         int i = l, p1 = l, p2 = mid + 1;
//         while (p1 <= mid && p2 <= r)
//         {
//             help[i++] = (sum[p1] <= sum[p2]? sum[p1++]: sum[p2++]);
//         }

//         while (p1 <= mid)
//         {
//             help[i++] = sum[p1++];
//         }

//         while (p2 <= r)
//         {
//             help[i++] = sum[p2++];
//         }

//         for (i = l; i <= r; i++)
//         {
//             sum[i] = help[i];
//         }

//         return ans;
//     }
// };
// @lc code=end

