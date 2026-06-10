// @leet start
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string crackSafe(int n, int k)
    {
        int m = std::pow(k, n - 1);
        std::vector<int> cur(m + 1);

        std::string path;
        [&](this auto &&dfs, int u, int ei) -> void
        {
            while (cur[u] < k)
            {
                int ne = cur[u]++;
                dfs((u * k + ne) % m, ne);
            }

            path.append((ei == -1? std::string(n - 1, '0'): to_string(ei)));
        } (0, -1);

        ranges::reverse(path);
        return path;
    }
};
// @leet end
