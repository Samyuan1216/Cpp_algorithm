/*
 * @lc app=leetcode.cn id=2092 lang=cpp
 *
 * [2092] 找出知晓秘密的所有专家
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson)
    {
        int m = meetings.size();

        sort(meetings.begin(), meetings.end(), [](vector<int> a, vector<int> b) -> bool
        {
            return a[2] < b[2];
        });

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

        auto un = [&](int a, int b)
        {
            father[max(find(a), find(b))] = min(find(a), find(b));
        };

        un(0, firstPerson);

        for (int l = 0, r = 0; l < m;)
        {
            r = l;

            while (r + 1 < m && meetings[l][2] == meetings[r + 1][2])
            {
                r++;
            }

            for (int i = l; i <= r; i++)
            {
                un(meetings[i][0], meetings[i][1]);
            }

            for (int i = l, a = 0, b = 0; i <= r; i++)
            {
                a = meetings[i][0];
                b = meetings[i][1];

                if (find(a) != 0)
                {
                    father[a] = a;
                }

                if (find(b) != 0)
                {
                    father[b] = b;
                }
            }

            l = r + 1;
        }

        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (find(i) == 0)
            {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
// @lc code=end

