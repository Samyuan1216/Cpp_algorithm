/*
 * @lc app=leetcode.cn id=52 lang=cpp
 *
 * [52] N 皇后 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalNQueens1(int n)
    {
        if (n < 1)
        {
            return 0;
        }

        vector<int> path(n);

        return f1(0, path, n);
    }

    int f1(int i, vector<int> &path, int n)
    {
        if (i == n)
        {
            return 1;
        }

        int res = 0;
        for (int j = 0; j < n; j++)
        {
            if (check(path, i, j) == true)
            {
                path[i] = j;
                res += f1(i + 1, path, n);
            }
        }

        return res;
    }

    bool check(vector<int> &path, int i, int j)
    {
        for (int k = 0; k < i; k++)
        {
            if (path[k] == j || abs(i - k) == abs(j - path[k]))
            {
                return false;
            }
        }

        return true;
    }

    int totalNQueens(int n)
    {
        if (n < 1)
        {
            return 0;
        }

        int limit = (1 << n) - 1;

        return f2(limit, 0, 0, 0);
    }

    int f2(int limit, int col, int left, int right)
    {
        if (col == limit)
        {
            return 1;
        }

        int ban = col | left | right;
        int candidate = limit & (~ban);
        int place = 0, ans = 0;
        while (candidate != 0)
        {
            place = candidate & -candidate;
            candidate ^= place;

            ans += f2(limit, col | place, (left | place) >> 1, (right | place) << 1);
        }

        return ans;
    }
};
// @lc code=end

