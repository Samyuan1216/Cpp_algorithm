/*
 * @lc app=leetcode.cn id=646 lang=cpp
 *
 * [646] 最长数对链
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findLongestChain(vector<vector<int>>& pairs)
    {
        sort(pairs.begin(), pairs.end(), [](vector<int> &a, vector<int> &b)
        {
            return a[0] < b[0];
        });

        int n = pairs.size();
        vector<int> ends(n);
        ends[0] = pairs[0][1];
        int e = 1;

        for (int i = 1; i < n; i++)
        {
            if (pairs[i][0] > ends[e - 1])
            {
                ends[e++] = pairs[i][1];
            }
            else
            {
                int cur = 0;
                for (int l = 0, r = e - 1, m = 0; l <= r;)
                {
                    m = l + ((r - l) >> 1);
                    if (pairs[i][0] <= ends[m])
                    {
                        cur = m;
                        r = m - 1;
                    }
                    else
                    {
                        l = m + 1;
                    }
                }

                ends[cur] = min(ends[cur], pairs[i][1]);
            }
        }

        return e;
    }
};
// @lc code=end

