#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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

class FHQ_Treap
{
    struct Node
    {
        int key = 0;
        int left = 0;
        int right = 0;
        int size = 0;
        double priority = 0;
    };

    std::vector<Node> tr;
    std::vector<int> head;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(int num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1,dis(gen));

        return i;
    }

    int copy(int idx)
    {
        int i = tr.size();
        tr.emplace_back(tr[idx]);

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
    }

    void split(int &l, int &r, int i, int num)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        i = copy(i);
        if (tr[i].key <= num)
        {
            l = i;
            split(tr[i].right, r, tr[i].right, num);
        }
        else
        {
            r = i;
            split(l, tr[i].left, tr[i].left, num);
        }

        up(i);
    }

    int merge(int l, int r)
    {
        if (l == 0 || r == 0)
        {
            return l + r;
        }

        if (tr[l].priority >= tr[r].priority)
        {
            l = copy(l);
            tr[l].right = merge(tr[l].right, r);

            up(l);
            return l;
        }
        else
        {
            r = copy(r);
            tr[r].left = merge(l, tr[r].left);

            up(r);
            return r;
        }
    }

    int small(int i, int num)
    {
        if (i == 0)
        {
            return 0;
        }

        if (tr[i].key >= num)
        {
            return small(tr[i].left, num);
        }

        return tr[tr[i].left].size + 1 + small(tr[i].right, num);
    }

    std::optional<int> index_impl(int i, int x)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[tr[i].left].size >= x)
        {
            return index_impl(tr[i].left, x);
        }

        if (tr[tr[i].left].size + 1 < x)
        {
            return index_impl(tr[i].right, x - tr[tr[i].left].size - 1);
        }

        return tr[i].key;
    }

    std::optional<int> pre_impl(int i, int num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key >= num)
        {
            return pre_impl(tr[i].left, num);
        }

        auto right_res = pre_impl(tr[i].right, num);
        return (right_res? right_res: tr[i].key);
    }

    std::optional<int> post_impl(int i, int num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key <= num)
        {
            return post_impl(tr[i].right, num);
        }

        auto left_res = post_impl(tr[i].left, num);
        return (left_res? left_res: tr[i].key);
    }
public:
    FHQ_Treap()
    {
        tr.reserve(500001 * 50);
        head.reserve(500001);
        tr.emplace_back();
        head.emplace_back();
    }

    void add(int v, int num)
    {
        int l, r;
        split(l, r, head[v], num);

        head.emplace_back(merge(merge(l, new_node(num)), r));
    }

    void remove(int v, int num)
    {
        int l, m, r;
        split(l, r, head[v], num);
        split(l, m, l, num - 1);

        head.emplace_back(merge(merge(l, merge(tr[m].left, tr[m].right)), r));
    }

    int rank(int v, int num)
    {
        head.emplace_back(head[v]);

        return small(head.back(), num) + 1;
    }

    std::optional<int> index(int v, int x)
    {
        head.emplace_back(head[v]);

        return index_impl(head.back(), x);
    }

    std::optional<int> pre(int v, int num)
    {
        head.emplace_back(head[v]);

        return pre_impl(head.back(), num);
    }

    std::optional<int> post(int v, int num)
    {
        head.emplace_back(head[v]);

        return post_impl(head.back(), num);
    }
};

void solve()
{
    int n;
    std::cin >> n;

    FHQ_Treap tree;
    for (int i = 1, v, op, x; i <= n; ++i)
    {
        std::cin >> v >> op >> x;

        if (op == 1)
        {
            tree.add(v, x);
        }
        else if (op == 2)
        {
            tree.remove(v, x);
        }
        else if (op == 3)
        {
            std::cout << tree.rank(v, x) << "\n";
        }
        else if (op == 4)
        {
            std::cout << *tree.index(v, x) << "\n";
        }
        else if (op == 5)
        {
            if (auto ans = tree.pre(v, x); ans)
            {
                std::cout << *ans << "\n";
            }
            else
            {
                std::cout << lim<int>::min() + 1 << "\n";
            }
        }
        else
        {
            if (auto ans = tree.post(v, x); ans)
            {
                std::cout << *ans << "\n";
            }
            else
            {
                std::cout << lim<int>::max() << "\n";
            }
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
