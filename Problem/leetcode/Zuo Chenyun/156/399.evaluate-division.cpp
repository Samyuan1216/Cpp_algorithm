// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)
    {
        unordered_map<string, int> ord;
        int idx = 0;

        for (auto &s: equations)
        {
            if (!ord.contains(s[0]))
            {
                ord[s[0]] = idx++;
            }

            if (!ord.contains(s[1]))
            {
                ord[s[1]] = idx++;
            }
        }

        vector<int> father(idx);
        ranges::iota(father, 0);

        vector<double> dist(idx, 1);
        auto find = [&](this auto &&find, int i) -> int
        {
            if (father[i] != i)
            {
                int old = father[i];
                father[i] = find(old);
                dist[i] *= dist[old];
            }

            return father[i];
        };

        auto merge = [&](int l, int r, double v) -> void
        {
            if (int lf = find(l), rf = find(r); lf != rf)
            {
                father[lf] = rf;
                dist[lf] = dist[r] / dist[l] * v;
            }
        };

        for (int i = 0; i < std::ssize(equations); ++i)
        {
            merge(ord[equations[i][0]], ord[equations[i][1]], values[i]);
        };

        auto query = [&](int l, int r) -> double
        {
            if (find(l) != find(r))
            {
                return -1;
            }

            return dist[l] / dist[r];
        };

        vector<double> ans;
        for (auto &q: queries)
        {
            if (!ord.contains(q[0]) || !ord.contains(q[1]))
            {
                ans.push_back(-1);
            }
            else
            {
                ans.push_back(query(ord[q[0]], ord[q[1]]));
            }
        };

        return ans;
    }
};
// @leet end
