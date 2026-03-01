/*
 * @lc app=leetcode.cn id=857 lang=cpp
 *
 * [857] 雇佣 K 名工人的最低成本
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct Employee
    {
        double ratio;
        int quality;

        Employee () {}
        Employee (double r, int q): ratio(r), quality(q) {}

        bool operator<(const Employee &other) const
        {
            return this->ratio < other.ratio;
        }
    };
    
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k)
    {
        int n = quality.size();

        vector<Employee> employees(n);
        for (int i = 0; i < n; i++)
        {
            employees[i] = Employee(double(wage[i]) / quality[i], quality[i]);
        }

        sort(employees.begin(), employees.end());

        priority_queue<int> heap;
        int quality_sum = 0;
        double ans = DBL_MAX;

        for (int i = 0, cur_quality; i < n; i++)
        {
            cur_quality = employees[i].quality;
            if (heap.size() < k)
            {
                quality_sum += cur_quality;

                heap.push(cur_quality);
                if (heap.size() == k)
                {
                    ans = min(ans, quality_sum * employees[i].ratio);
                }
            }
            else
            {
                if (cur_quality < heap.top())
                {
                    quality_sum += cur_quality - heap.top();
                    heap.pop();

                    heap.push(cur_quality);
                    ans = min(ans, quality_sum * employees[i].ratio);
                }
            }
        }

        return ans;
    }
};
// @lc code=end

