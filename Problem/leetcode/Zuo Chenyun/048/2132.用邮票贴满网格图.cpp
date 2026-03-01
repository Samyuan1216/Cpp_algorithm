/*
 * @lc app=leetcode.cn id=2132 lang=cpp
 *
 * [2132] 用邮票贴满网格图
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth)
    {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> sum(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                sum[i][j] = grid[i - 1][j - 1];
            }
        }

        build(sum);

        vector<vector<int>> diff(n + 2, vector<int>(m + 2));
        for (int a = 1, c = a + stampHeight - 1; c <= n; a++, c++)
        {
            for (int b = 1, d = b + stampWidth - 1; d <= m; b++, d++)
            {
                if (sum_region(sum, a, b, c, d) == 0)
                {
                    add(diff, a, b, c, d);
                }
            }
        }

        build(diff);

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (grid[i - 1][j - 1] == 0 && diff[i][j] == 0)
                {
                    return false;
                }
            }
        }

        return true;
    }

    void build(vector<vector<int>> &a)
    {
        for (int i = 1; i < a.size(); i++)
        {
            for (int j = 1; j < a[0].size(); j++)
            {
                a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            }
        }
    }

    int sum_region(vector<vector<int>> &sum, int a, int b, int c, int d)
    {
        return sum[c][d] + sum[a - 1][b - 1] - sum[a - 1][d] - sum[c][b - 1];
    }

    void add(vector<vector<int>> &grid, int a, int b, int c, int d)
    {
        grid[a][b]++;
        grid[c + 1][d + 1]++;
        grid[a][d + 1]--;
        grid[c + 1][b]--;
    }
};
// @lc code=end

