/*
 * @lc app=leetcode.cn id=928 lang=cpp
 *
 * [928] 尽量减少恶意软件的传播 II
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial)
    {
        int n = graph.size();

        vector<int> virus(n), cnts(n), infect(n, -1), size(n, 1), father(n);
        for (int i = 0; i < n; i++)
        {
            father[i] = i;
        }

        for (int &x: initial)
        {
            virus[x] = 1;
        }

        function<int (int)> find = [&](int i) -> int
        {
            if (i != father[i])
            {
                father[i] = find(father[i]);
            }

            return father[i];
        };

        auto un = [&](int a, int b) -> void
        {
            int ua = find(a), ub = find(b);
            if (ua != ub)
            {
                father[ua] = ub;
                size[ub] += size[ua];
            }
        };

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (graph[i][j] == 1 && virus[i] == 0 && virus[j] == 0)
                {
                    un(i, j);
                }
            }
        }

        for (int &sick: initial)
        {
            for (int neibour = 0; neibour < n; neibour++)
            {
                if (sick != neibour && virus[neibour] == 0 && graph[sick][neibour] == 1)
                {
                    int fn = find(neibour);
                    if (infect[fn] == -1)
                    {
                        infect[fn] = sick;
                    }
                    else if (infect[fn] != -2 && infect[fn] != sick)
                    {
                        infect[fn] = -2;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (i == find(i) && infect[i] >= 0)
            {
                cnts[infect[i]] += size[i];
            }
        }

        sort(initial.begin(), initial.end());

        int ans = initial[0];
        int maxn = cnts[ans];
        for (int &x: initial)
        {
            if (cnts[x] > maxn)
            {
                ans = x;
                maxn = cnts[x];
            }
        }

        return ans;
    }
};
// @lc code=end

