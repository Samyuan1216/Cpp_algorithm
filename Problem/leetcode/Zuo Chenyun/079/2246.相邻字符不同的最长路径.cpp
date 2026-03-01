/*
 * @lc app=leetcode.cn id=2246 lang=cpp
 *
 * [2246] 相邻字符不同的最长路径
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longestPath(vector<int>& parent, string s)
    {
        int n = parent.size();
        vector<vector<int>> graph(n, vector<int>());

        for (int i = 1; i < n; i++)
        {
            graph[parent[i]].push_back(i);
        }

        return f(s, graph, 0).max_path;
    }

    struct Info
    {
        int max_path_from_head;
        int max_path;

        Info(int a, int b): max_path_from_head(a), max_path(b) {}
    };

    Info f(string &s, vector<vector<int>> &graph, int u)
    {
        if (graph[u].empty())
        {
            Info res(1, 1);
            return res;
        }

        int max1 = 0, max2 = 0, max_path = 1;
        for (auto &v: graph[u])
        {
            Info infon = f(s, graph, v);
            max_path = max(max_path, infon.max_path);

            if (s[u] != s[v])
            {
                if (infon.max_path_from_head > max1)
                {
                    max2 = max1;
                    max1 = infon.max_path_from_head;
                }
                else if (infon.max_path_from_head > max2)
                {
                    max2 = infon.max_path_from_head;
                }
            }
        }

        int max_path_from_head = max1 + 1;
        max_path = max(max_path, max1 + max2 + 1);

        Info res(max_path_from_head, max_path);
        return res;
    }
};
// @lc code=end

