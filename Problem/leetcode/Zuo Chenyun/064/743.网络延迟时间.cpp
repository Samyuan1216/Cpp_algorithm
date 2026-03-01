/*
 * @lc app=leetcode.cn id=743 lang=cpp
 *
 * [743] 网络延迟时间
 */

// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        int m = times.size();
        vector<int> head(n + 1), ne(m + 1), to(m + 1), weight(m + 1);
        int cnt = 1;
        for (auto &time: times)
        {
            ne[cnt] = head[time[0]];
            to[cnt] = time[1];
            weight[cnt] = time[2];
            head[time[0]] = cnt++;
        }

        vector<int> distance(n + 1, INT_MAX);
        distance[k] = 0;

        priority_queue< pair<int, int>,
                        vector<pair<int, int>>,
                        decltype([](pair<int, int> a, pair<int, int> b)
                        {
                            return a.second > b.second;
                        })> heap;
        heap.push(make_pair(k, 0));

        vector<int> visited(n + 1);
        while (heap.empty() == false)
        {
            int u = heap.top().first;
            heap.pop();

            if (visited[u] == 1)
            {
                continue;
            }

            visited[u] = 1;
            for (int i = head[u]; i > 0; i = ne[i])
            {
                int v = to[i], w = weight[i];
                if (visited[v] == false && (long long)distance[u] + w < distance[v])
                {
                    distance[v] = distance[u] + w;
                    heap.push(make_pair(v, distance[v]));
                }
            }
        }

        int ans = INT_MIN;
        for (int i = 1; i <= n; i++)
        {
            if (distance[i] == INT_MAX)
            {
                return -1;
            }

            ans = max(ans, distance[i]);
        }

        return ans;
    }
};
// @lc code=end

