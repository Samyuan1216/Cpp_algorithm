// @lc code=start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int electricCarPlan(vector<vector<int>>& paths, int cnt, int start, int end, vector<int>& charge)
    {
        int n = charge.size(), m = 2 * paths.size() + 1;

        vector<int> head(n), ne(m), to(m), weight(m);
        int cntm = 1;
        for (auto &node: paths)
        {
            ne[cntm] = head[node[0]];
            to[cntm] = node[1];
            weight[cntm] = node[2];
            head[node[0]] = cntm++;

            ne[cntm] = head[node[1]];
            to[cntm] = node[0];
            weight[cntm] = node[2];
            head[node[1]] = cntm++;
        }

        vector<vector<int>> distance(n, vector<int>(cnt + 1, INT_MAX));
        distance[start][0] = 0;

        priority_queue< vector<int>,
                        vector<vector<int>>,
                        decltype([](vector<int> &a, vector<int> &b)
                        {
                            return a[2] > b[2];
                        })> heap;
        heap.push(vector<int>{start, 0, 0});

        vector<vector<int>> visited(n, vector<int>(cnt + 1));
        while (heap.empty() == false)
        {
            int cur = heap.top()[0], power = heap.top()[1], cost = heap.top()[2];
            heap.pop();

            if (visited[cur][power] == 1)
            {
                continue;
            }

            if (cur == end)
            {
                return cost;
            }

            visited[cur][power] = 1;
            if (power < cnt)
            {
                if (visited[cur][power + 1] == 0 && cost + charge[cur] < distance[cur][power + 1])
                {
                    distance[cur][power + 1] = cost + charge[cur];
                    heap.push(vector<int>{cur, power + 1, distance[cur][power + 1]});
                }
            }

            for (int i = head[cur]; i > 0; i = ne[i])
            {
                int next_city = to[i], rest_power = power - weight[i], next_cost = cost + weight[i];
                if (rest_power >= 0 && visited[next_city][rest_power] == 0 && next_cost < distance[next_city][rest_power])
                {
                    distance[next_city][rest_power] = next_cost;
                    heap.push(vector<int>{next_city, rest_power, next_cost});
                }
            }
        }

        return -1;
    }
};
// @lc code=end