/*
 * @lc app=leetcode.cn id=1792 lang=cpp
 *
 * [1792] 最大平均通过率
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct compare
    {
        bool operator()(vector<double> &a, vector<double> &b)
        {
            return a[2] < b[2];
        }
    };
    
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents)
    {
        priority_queue<vector<double>, vector<vector<double>>, compare> heap;
        for (auto &p: classes)
        {
            double a = p[0], b = p[1];
            heap.push(vector<double>{a, b, (a + 1) / (b + 1) - a / b});
        }

        while (extraStudents--)
        {
            double a = heap.top()[0] + 1, b = heap.top()[1] + 1;
            heap.pop();

            heap.push(vector<double>{a, b, (a + 1) / (b + 1) - a / b});
        }

        double ans = 0;
        while (!heap.empty())
        {
            ans += heap.top()[0] / heap.top()[1];
            heap.pop();
        }

        return ans / classes.size();
    }
};
// @lc code=end

