#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

template<typename T>
using lim = std::numeric_limits<T>;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

struct Leftist_Tree
{
    std::vector<int> num;
    std::vector<int> rt, left, right, dist, size;

    Leftist_Tree()
    {
        new_node(0);
        dist[0] = -1;
        rt.push_back(0);
    }

    int new_node(int v)
    {
        int i = std::ssize(num);
        num.push_back(v);
        left.push_back(0);
        right.push_back(0);
        dist.push_back(0);
        size.push_back(0);

        return i;
    }

    int clone(int idx)
    {
        int i = new_node(0);
        num[i] = num[idx];
        left[i] = left[idx];
        right[i] = right[idx];
        dist[i] = dist[idx];

        return i;
    }

    int merge(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (num[i] > num[j])
        {
            std::swap(i, j);
        }

        int h = clone(i);
        right[h] = merge(right[h], j);

        if (dist[left[h]] < dist[right[h]])
        {
            std::swap(left[h], right[h]);
        }

        dist[h] = dist[right[h]] + 1;
        return h;
    }

    int pop(int i)
    {
        if (left[i] == 0 && right[i] == 0)
        {
            return 0;
        }

        if (left[i] == 0 || right[i] == 0)
        {
            return clone(left[i] + right[i]);
        }

        return merge(left[i], right[i]);
    }

    void tree_add(int x, int y, int i)
    {
        rt.push_back(merge(rt[x], new_node(y)));
        size[rt[i]] = size[rt[x]] + 1;
    }

    void tree_merge(int x, int y, int i)
    {
        if (rt[x] == 0 && rt[y] == 0)
        {
            rt.push_back(0);
        }
        else if (rt[x] == 0 || rt[y] == 0)
        {
            rt.push_back(clone(rt[x] + rt[y]));
        }
        else
        {
            rt.push_back(merge(rt[x], rt[y]));
        }

        size[rt[i]] = size[rt[x]] + size[rt[y]];
    }

    void tree_pop(int x, int i)
    {
        if (size[rt[x]] == 0)
        {
            rt.push_back(0);
        }
        else
        {
            rt.push_back(pop(rt[x]));
            size[rt[i]] = size[rt[x]] - 1;
        }
    }
};

void solve()
{
    int m;
    std::cin >> m;

    Leftist_Tree tr;
    for (int i = 1; i <= m; ++i)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int v, x;
            std::cin >> v >> x;

            tr.tree_add(v, x, i);
        }
        else if (op == 2)
        {
            int u, v;
            std::cin >> u >> v;

            tr.tree_merge(u, v, i);
        }
        else
        {
            int v;
            std::cin >> v;

            tr.tree_pop(v, i);
        }

        std::cout << (tr.size[tr.rt[i]] > 0? tr.num[tr.rt[i]]: -1) << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
