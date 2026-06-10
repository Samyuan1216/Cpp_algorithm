// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs)
    {
        std::vector<int> points;
        for (auto &pair: pairs)
        {
            points.push_back(pair[0]);
            points.push_back(pair[1]);
        }

        ranges::sort(points);

        auto [l, r] = ranges::unique(points);
        points.erase(l, r);

        int n = std::ssize(points), m = std::ssize(pairs), cnt = 0;
        std::vector<int> head(n, -1), next(m, -1), to(m, -1);

        auto add_edge = [&](int u, int v) -> void
        {
            next[cnt] = head[u];
            to[cnt] = v;
            head[u] = cnt++;
        };

        std::vector<int> out(n), in(n);
        for (auto &pair: pairs)
        {
            int u = std::distance(points.begin(), ranges::lower_bound(points, pair[0]));
            int v = std::distance(points.begin(), ranges::lower_bound(points, pair[1]));

            add_edge(u, v);
            ++out[u], ++in[v];
        }

        int start = [&]() -> int
        {
            int start = -1, end = -1;
            for (int i = 0, v; i < n; ++i)
            {
                v = out[i] - in[i];
                if (v == 1)
                {
                    start = i;
                }

                if (v == -1)
                {
                    end = i;
                }
            }

            if (start != -1)
            {
                return start;
            }

            for (int i = 0; i < n; ++i)
            {
                if (out[i] != 0)
                {
                    return i;
                }
            }

            return -1;
        } ();

        std::vector<int> path, cur = head;
        [&](this auto &&dfs, int u) -> void
        {
            for (int ei = cur[u]; ei != -1; ei = cur[u])
            {
                cur[u] = next[ei];
                dfs(to[ei]);
            }

            path.push_back(points[u]);
        } (start);

        ranges::reverse(path);

        std::vector<std::vector<int>> ans;
        for (int i = 0; i < m; ++i)
        {
            ans.push_back({path[i], path[i + 1]});
        }

        return ans;
    }
};
// @leet end
