/*
 * @lc app=leetcode.cn id=947 lang=cpp
 *
 * [947] 移除最多的同行或同列石头
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int removeStones(vector<vector<int>>& stones)
    {
        int n = stones.size();
        int sets = n;

        map<int, int> row_first, col_first;

        vector<int> father(n);
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

        function<void (int, int)> un = [&](int a, int b) -> void
        {
            int ua = find(a), ub = find(b);
            if (ua != ub)
            {
                father[ua] = ub;
                sets--;
            }
        };

        for (int i = 0; i < n; i++)
        {
            int row = stones[i][0];
            int col = stones[i][1];

            if (row_first.find(row) == row_first.end())
            {
                row_first[row] = i;
            }
            else
            {
                un(row_first[row], i);
            }

            if (col_first.find(col) == col_first.end())
            {
                col_first[col] = i;
            }
            else
            {
                un(col_first[col], i);
            }
        }

        return n - sets;
    }
};
// @lc code=end

