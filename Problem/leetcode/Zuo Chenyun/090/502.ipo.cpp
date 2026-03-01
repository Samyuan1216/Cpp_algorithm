/*
 * @lc app=leetcode.cn id=502 lang=cpp
 *
 * [502] IPO
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    struct compare1
    {
        bool operator()(vector<int> &a, vector<int> &b)
        {
            return a[1] > b[1];
        }
    };

    struct compare2
    {
        bool operator()(vector<int> &a, vector<int> &b)
        {
            return a[0] < b[0];
        }
    };
    
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
    {
        priority_queue<vector<int>, vector<vector<int>>, compare1> heap1;
        priority_queue<vector<int>, vector<vector<int>>, compare2> heap2;

        int n = profits.size();
        for (int i = 0; i < n; i++)
        {
            heap1.push(vector<int>{profits[i], capital[i]});
        }

        while (k > 0)
        {
            while (!heap1.empty() && w >= heap1.top()[1])
            {
                heap2.push(heap1.top());
                heap1.pop();
            }

            if (heap2.empty())
            {
                break;
            }

            w += heap2.top()[0];
            heap2.pop();

            k--;
        }

        return w;
    }
};
// @lc code=end

