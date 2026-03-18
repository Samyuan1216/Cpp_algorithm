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

template<typename T = int>
class FHQ_Treap
{
    struct Node
    {
        T key = T{};
        int left = 0;
        int right = 0;
        int size = 0;
        int count = 0;
        double priority = 0;
    };

    std::vector<Node> tr;
    int head = 0;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, 1, dis(gen));

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + tr[i].count;
    }

    void split(int &l, int &r, int i, const T &num)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

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

        if (tr[l].priority > tr[r].priority)
        {
            tr[l].right = merge(tr[l].right, r);

            up(l);
            return l;
        }
        else
        {
            tr[r].left = merge(l, tr[r].left);

            up(r);
            return r;
        }
    }

    std::optional<T> find(int i, const T &num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key == num)
        {
            return i;
        }
        else if (tr[i].key > num)
        {
            return find(tr[i].left, num);
        }
        else
        {
            return find(tr[i].right, num);
        }
    }

    void change_count(int i, const T &num, int change)
    {
        if (tr[i].key == num)
        {
            tr[i].count += change;
        }
        else if (tr[i].key > num)
        {
            change_count(tr[i].left, num, change);
        }
        else
        {
            change_count(tr[i].right, num, change);
        }

        up(i);
    }

    int small(int i, const T &num)
    {
        if (i == 0)
        {
            return 0;
        }

        if (tr[i].key >= num)
        {
            return small(tr[i].left, num);
        }

        return tr[tr[i].left].size + tr[i].count + small(tr[i].right, num);
    }

    std::optional<T> index(int i, int x)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[tr[i].left].size >= x)
        {
            return index(tr[i].left, x);
        }

        if (tr[tr[i].left].size + tr[i].count < x)
        {
            return index(tr[i].right, x - tr[tr[i].left].size - tr[i].count);
        }

        return tr[i].key;
    }

    std::optional<T> pre(int i, const T &num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key >= num)
        {
            return pre(tr[i].left, num);
        }

        auto right_res = pre(tr[i].right, num);
        return (right_res? right_res: tr[i].key);
    }

    std::optional<T> post(int i, const T &num)
    {
        if (i == 0)
        {
            return std::nullopt;
        }

        if (tr[i].key <= num)
        {
            return post(tr[i].right, num);
        }

        auto left_res = post(tr[i].left, num);
        return (left_res? left_res: tr[i].key);
    }
public:
    FHQ_Treap()
    {
        tr.emplace_back();
    }

    void add(const T &num)
    {
        if (find(head, num))
        {
            change_count(head, num, 1);
        }
        else
        {
            int l, r;
            split(l, r, head, num);
            head = merge(merge(l, new_node(num)), r);
        }
    }

    void remove(const T &num)
    {
        auto p = find(head, num);
        if (p)
        {
            int i = *p;
            if (tr[i].count > 1)
            {
                change_count(head, num, -1);
            }
            else
            {
                int l, m, r;
                split(l, r, head, num);
                split(l, m, l, num - 1);

                head = merge(l, r);
            }
        }
    }

    int rank(const T &num)
    {
        return small(head, num) + 1;
    }
    
    std::optional<T> index(int x)
    {
        return index(head, x);
    }
    
    std::optional<T> pre(const T &num)
    {
        return pre(head, num);
    }
    
    std::optional<T> post(const T &num)
    {
        return post(head, num);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    FHQ_Treap tree;
    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        tree.add(x);
    }

    int ans = 0;
    for (int i = 0, last = 0, op, x; i < m; ++i)
    {
        std::cin >> op >> x;

        x ^= last;
        if (op == 1)
        {
            tree.add(x);
        }
        else if (op == 2)
        {
            tree.remove(x);
        }
        else if (op == 3)
        {
            last = tree.rank(x);
            ans ^= last;
        }
        else if (op == 4)
        {
            last = *tree.index(x);
            ans ^= last;
        }
        else if (op == 5)
        {
            last = *tree.pre(x);
            ans ^= last;
        }
        else
        {
            last = *tree.post(x);
            ans ^= last;
        }
    }

    std::cout << ans << "\n";
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
