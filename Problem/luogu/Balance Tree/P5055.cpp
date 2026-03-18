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
        int num = 0;
        int left = 0;
        int right = 0;
        int size = 0;
        i64 sum = 0;
        double priority = 0;
        bool reverse = false;
    };

    std::vector<Node> tr;
    std::vector<int> head;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(int num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, num, dis(gen), false);

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
        tr[i].sum = tr[tr[i].left].sum + tr[tr[i].right].sum + tr[i].num;
    }

    void down(int i)
    {
        if (tr[i].reverse)
        {
            if (tr[i].left != 0)
            {
                tr[i].left = copy(tr[i].left);
                tr[tr[i].left].reverse = !tr[tr[i].left].reverse;
            }

            if (tr[i].right != 0)
            {
                tr[i].right = copy(tr[i].right);
                tr[tr[i].right].reverse = !tr[tr[i].right].reverse;
            }

            std::swap(tr[i].left, tr[i].right);
            tr[i].reverse = false;
        }
    }

    void split(int &l, int &r, int i, int rank)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        i = copy(i);
        down(i);

        if (tr[tr[i].left].size + 1 <= rank)
        {
            l = i;
            split(tr[i].right, r, tr[i].right, rank - tr[tr[i].left].size - 1);
        }
        else
        {
            r = i;
            split(l, tr[i].left, tr[i].left, rank);
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
            down(l);

            tr[l].right = merge(tr[l].right, r);

            up(l);
            return l;
        }
        else
        {
            r = copy(r);
            down(r);

            tr[r].left = merge(l, tr[r].left);

            up(r);
            return r;
        }
    }
public:
    FHQ_Treap(int n)
    {
        tr.reserve((n + 1) * 100);
        head.reserve(n + 1);

        tr.emplace_back();
        head.emplace_back();
    }

    void insert(int v, int x, int y)
    {
        int l, r;
        split(l, r, head[v], x);

        head.emplace_back(merge(merge(l, new_node(y)), r));
    }

    void remove(int v, int x)
    {
        int l, m, r;
        split(l, r, head[v], x);
        split(l, m, l, x - 1);

        head.emplace_back(merge(l, r));
    }

    void reverse(int v, int x, int y)
    {
        int l, m, r;
        split(l, r, head[v], y);
        split(l, m, l, x - 1);

        tr[m].reverse = !tr[m].reverse;
        head.emplace_back(merge(merge(l, m), r));
    }

    i64 query(int v, int x, int y)
    {
        int l, m, r;
        split(l, r, head[v], y);
        split(l, m, l, x - 1);

        i64 ans = tr[m].sum;
        head.emplace_back(merge(merge(l, m), r));

        return ans;
    }
};

void solve()
{
    int n;
    std::cin >> n;

    FHQ_Treap tree(n);

    i64 last_ans = 0;
    for (int i = 1, v, op; i <= n; ++i)
    {
        std::cin >> v >> op;

        if (op == 1)
        {
            i64 p, x;
            std::cin >> p >> x;

            p ^= last_ans, x ^= last_ans;
            tree.insert(v, p, x);
        }
        else if (op == 2)
        {
            i64 p;
            std::cin >> p;

            p ^= last_ans;
            tree.remove(v, p);
        }
        else if (op == 3)
        {
            i64 l, r;
            std::cin >> l >> r;

            l ^= last_ans, r ^= last_ans;
            tree.reverse(v, l, r);
        }
        else
        {
            i64 l, r;
            std::cin >> l >> r;

            l ^= last_ans, r ^= last_ans;
            last_ans = tree.query(v, l, r);

            std::cout << last_ans << "\n";
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
