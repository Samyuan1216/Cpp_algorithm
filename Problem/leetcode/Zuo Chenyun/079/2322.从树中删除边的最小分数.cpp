/*
 * @lc app=leetcode.cn id=2322 lang=cpp
 *
 * [2322] 从树中删除边的最小分数
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;
vector<int> dfn(MAXN), xr(MAXN), siz(MAXN);
int dfn_cnt = 0;

class Solution
{
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges)
    {
        int n = nums.size();
        vector<vector<int>> graph(n, vector<int>());

        for (auto &edge: edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        fill(dfn.begin(), dfn.begin() + n, 0);
        dfn_cnt = 0;

        f(nums, graph, 0);

        int m = edges.size();
        int ans = INT32_MAX;

        for (int i = 0, a, b, pre, pos, sum1, sum2, sum3; i < m; i++)
        {
            a = max(dfn[edges[i][0]], dfn[edges[i][1]]);
            for (int j = i + 1; j < m; j++)
            {
                b = max(dfn[edges[j][0]], dfn[edges[j][1]]);
                if (a < b)
                {
                    pre = a;
                    pos = b;
                }
                else
                {
                    pre = b;
                    pos = a;
                }

                sum1 = xr[pos];
                if (pos < pre + siz[pre])
                {
                    sum2 = xr[pre] ^ xr[pos];
                    sum3 = xr[1] ^ xr[pre];
                }
                else
                {
                    sum2 = xr[pre];
                    sum3 = xr[1] ^ sum1 ^ sum2;
                }

                ans = min(ans, max(sum1, max(sum2, sum3)) - min(sum1, min(sum2, sum3)));
            }
        }

        return ans;
    }

    void f(vector<int> &nums, vector<vector<int>> &graph, int u)
    {
        int i = ++dfn_cnt;
        dfn[u] = i;
        xr[i] = nums[u];
        siz[i] = 1;

        for (auto &v: graph[u])
        {
            if (dfn[v] == 0)
            {
                f(nums, graph, v);

                xr[i] ^= xr[dfn[v]];
                siz[i] += siz[dfn[v]];
            }
        }
    }
};
// @lc code=end

