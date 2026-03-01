/*
 * @lc app=leetcode.cn id=354 lang=cpp
 *
 * [354] 俄罗斯套娃信封问题
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxEnvelopes(vector<vector<int>>& envelopes)
    {
        sort(envelopes.begin(), envelopes.end(), [](vector<int> &a, vector<int> &b)
        {
            if (a[0] != b[0])
            {
                return a[0] < b[0];
            }

            return a[1] > b[1];
        });

        int n = envelopes.size();
        vector<int> ends(n);
        ends[0] = envelopes[0][1];
        int e = 1;

        for (int i = 1; i < n; i++)
        {
            if (envelopes[i][1] > ends[e - 1])
            {
                ends[e++] = envelopes[i][1];
            }
            else
            {
                int cur = 0;
                for (int l = 0, r = e - 1, m = 0; l <= r;)
                {
                    m = l + ((r - l) >> 1);
                    if (envelopes[i][1] <= ends[m])
                    {
                        cur = m;
                        r = m - 1;
                    }
                    else
                    {
                        l = m + 1;
                    }
                }

                ends[cur] = envelopes[i][1];
            }
        }

        return e;
    }
};
// @lc code=end

