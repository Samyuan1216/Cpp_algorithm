// @leet start
#include <bits/extc++.h>
using namespace std;

template<typename T1, typename T2 = __gnu_pbds::null_type, typename F1 = std::less<T1>>
using rb_tree = __gnu_pbds::tree<T1, T2, F1, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

class Solution
{
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people)
    {
        int n = people.size();
        auto tree = rb_tree<int>();

        sort(people.begin(), people.end(), [](auto &a, auto &b)
        {
            return (a[0] != b[0]? a[0] < b[0]: a[1] > b[1]);
        });

        for (int i = 0; i < n; ++i)
        {
            tree.insert(i);
        }

        auto ans = vector(n, vector<int>(2));
        for (auto &p: people)
        {
            auto it = tree.find_by_order(p[1]);
            ans[*it] = p;

            tree.erase(it);
        }

        return ans;
    }
};
// @leet end
