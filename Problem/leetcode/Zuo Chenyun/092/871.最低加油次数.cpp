/*
 * @lc app=leetcode.cn id=871 lang=cpp
 *
 * [871] 最低加油次数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations)
    {
        if (startFuel >= target)
        {
            return 0;
        }

        priority_queue<int> heap;
        int to = startFuel, cnt = 0;
        for (auto &station: stations)
        {
            int position = station[0], fuel = station[1];
            if (to < position)
            {
                while (!heap.empty() && to < position)
                {
                    to += heap.top();
                    heap.pop();

                    cnt++;
                    if (to >= target)
                    {
                        return cnt;
                    }
                }

                if (to < position)
                {
                    return -1;
                }
            }

            heap.push(fuel);
        }

        while (!heap.empty())
        {
            to += heap.top();
            heap.pop();

            cnt++;
            if (to >= target)
            {
                return cnt;
            }
        }

        return -1;
    }
};
// @lc code=end

