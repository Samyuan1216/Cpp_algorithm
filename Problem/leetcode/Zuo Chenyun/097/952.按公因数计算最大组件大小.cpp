/*
 * @lc app=leetcode.cn id=952 lang=cpp
 *
 * [952] 按公因数计算最大组件大小
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int largestComponentSize(vector<int>& nums)
    {
        int n = nums.size(), maxn = 0;
        for (int i = 0; i < n; i++)
        {
            maxn = max(maxn, nums[i]);
        }

        vector<int> father(n), size(n, 1), factor(maxn + 1, -1);
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }

        function<int (int)> find = [&](int i) -> int
        {
            if (i != father[i])
            {
                father[i] = find(father[i]);
            }

            return father[i];
        };

        auto un = [&](int a, int b)
        {
            int ua = find(a), ub = find(b);
            if (ua != ub)
            {
                father[ua] = ub;
                size[ub] += size[ua];
            }
        };

        for (int i = 0, x = 0; i < n; i++)
        {
            x = nums[i];
            for (int j = 2; j * j <= x; j++)
            {
                if (x % j == 0)
                {
                    if (factor[j] == -1)
                    {
                        factor[j] = i;
                    }
                    else
                    {
                        un(factor[j], i);
                    }

                    while (x % j == 0)
                    {
                        x /= j;
                    }
                }
            }

            if (x > 1)
            {
                if (factor[x] == -1)
                {
                    factor[x] = i;
                }
                else
                {
                    un(factor[x], i);
                }
            }
        }

        int maxa = 0;
        for (int i = 0; i < n; i++)
        {
            maxa = max(maxa, size[i]);
        }

        return maxa;
    }
};
// @lc code=end

