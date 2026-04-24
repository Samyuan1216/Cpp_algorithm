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
    std::vector<int> num, up, left, right, dist, size, father, add;

    Leftist_Tree(int n, const auto &arr): num(arr), up(n + 1), left(n + 1), right(n + 1), dist(n + 1), size(n + 1, 1), father(n + 1), add(n + 1)
    {
        dist[0] = -1;
        ranges::iota(father, 0);
    }

    int find(int i)
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    }

    int merge(int i, int j)
    {
        if (i == 0 || j == 0)
        {
            return i + j;
        }

        if (num[i] < num[j])
        {
            std::swap(i, j);
        }

        right[i] = merge(right[i], j);
        up[right[i]] = i;

        if (dist[left[i]] < dist[right[i]])
        {
            std::swap(left[i], right[i]);
        }

        dist[i] = dist[right[i]] + 1;
        father[left[i]] = father[right[i]] = i;

        return i;
    }

    int remove(int i)
    {
        int h = find(i);
        father[left[i]] = left[i], father[right[i]] = right[i];

        int s = merge(left[i], right[i]), f = up[i];
        father[i] = s, up[s] = f;

        if (h != i)
        {
            father[s] = h;
            (left[f] == i? left[f]: right[f]) = s;

            for (int d = dist[s]; dist[f] > d + 1; f = up[f], ++d)
            {
                dist[f] = d + 1;
                if (dist[left[f]] < dist[right[f]])
                {
                    std::swap(left[f], right[f]);
                }
            }
        }

        up[i] = left[i] = right[i] = dist[i] = 0;
        return father[s];
    }

    void down(int i, int v)
    {
        if (i == 0)
        {
            return;
        }

        add[i] = 0, num[i] += v;
        down(left[i], v);
        down(right[i], v);
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    Leftist_Tree tr(n, arr);
    std::multiset<int> heads;

    auto minus_head = [&](int h) -> void
    {
        if (h == 0)
        {
            return;
        }

        heads.erase(heads.find(tr.num[h] + tr.add[h]));
    };

    auto add_head = [&](int h) -> void
    {
        if (h == 0)
        {
            return;
        }

        heads.insert(tr.num[h] + tr.add[h]);
    };

    for (int i = 1; i <= n; ++i)
    {
        add_head(i);
    }

    int m;
    std::cin >> m;

    int add_all = 0;
    auto u = [&](int x, int y) -> void
    {
        x = tr.find(x), y = tr.find(y);
        if (x == y)
        {
            return;
        }

        int xsize = tr.size[x], ysize = tr.size[y];
        minus_head(x), minus_head(y);

        int add_tag;
        if (xsize <= ysize)
        {
            tr.down(x, tr.add[x] - tr.add[y]);
            add_tag = tr.add[y];
        }
        else
        {
            tr.down(y, tr.add[y] - tr.add[x]);
            add_tag = tr.add[x];
        }

        int h = tr.merge(x, y);
        tr.size[h] = xsize + ysize;
        tr.add[h] = add_tag;

        add_head(h);
    };

    auto a1 = [&](int x, int v) -> void
    {
        int h = tr.find(x);
        minus_head(h);

        int l = tr.remove(x);
        if (l != 0)
        {
            tr.size[l] = tr.size[h] - 1;
            tr.add[l] = tr.add[h];

            add_head(l);
        }

        tr.num[x] += tr.add[h] + v;
        tr.father[x] = x;
        tr.size[x] = 1;
        tr.add[x] = 0;

        add_head(x);
        u(l, x);
    };

    auto a2 = [&](int x, int v) -> void
    {
        int h = tr.find(x);
        minus_head(h);

        tr.add[h] += v;
        add_head(h);
    };

    auto a3 = [&](int v) -> void
    {
        add_all += v;
    };

    auto f1 = [&](int x) -> int
    {
        return tr.num[x] + tr.add[tr.find(x)] + add_all;
    };

    auto f2 = [&](int x) -> int
    {
        return tr.num[tr.find(x)] + tr.add[tr.find(x)] + add_all;
    };

    auto f3 = [&]() -> int
    {
        return *heads.rbegin() + add_all;
    };

    for (int i = 1; i <= m; ++i)
    {
        std::string op;
        std::cin >> op;

        if (op == "U")
        {
            int x, y;
            std::cin >> x >> y;

            u(x, y);
        }
        else if (op == "A1")
        {
            int x, v;
            std::cin >> x >> v;

            a1(x, v);
        }
        else if (op == "A2")
        {
            int x, v;
            std::cin >> x >> v;

            a2(x, v);
        }
        else if (op == "A3")
        {
            int v;
            std::cin >> v;

            a3(v);
        }
        else if (op == "F1")
        {
            int x;
            std::cin >> x;
            std::cout << f1(x) << "\n";
        }
        else if (op == "F2")
        {
            int x;
            std::cin >> x;
            std::cout << f2(x) << "\n";
        }
        else
        {
            std::cout << f3() << "\n";
        }
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
