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

template<typename T = int>
class FHQ_Treap
{
    struct Node
    {
        T key = T{};
        int left = 0;
        int right = 0;
        int size = 0;
        double priority = 0;
    };

    std::vector<Node> tr;
    int head = 0;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, dis(gen));

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
    }

    void split_key(int &l, int &r, int i, const T &num)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        if (tr[i].key <= num)
        {
            l = i;
            split_key(tr[i].right, r, tr[i].right, num);
        }
        else
        {
            r = i;
            split_key(l, tr[i].left, tr[i].left, num);
        }

        up(i);
    }

    void split_rank(int &l, int &r, int i, int rank)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        if (tr[tr[i].left].size + 1 <= rank)
        {
            l = i;
            split_rank(tr[i].right, r, tr[i].right, rank - tr[tr[i].left].size - 1);
        }
        else
        {
            r = i;
            split_rank(l, tr[i].left, tr[i].left, rank);
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
public:
    FHQ_Treap()
    {
        tr.emplace_back();
    }

    void insert(const T &num, int x)
    {
        int l, r;
        split_rank(l, r, head, x);
        head = merge(merge(l, new_node(num)), r);
    }

    void query(int x)
    {
        int l, m, r;
        split_rank(l, r, head, x + 1);
        split_rank(l, m, l, x);

        std::cout << tr[m].key << "\n";
        head = merge(merge(l, m), r);
    }
};

void solve()
{
    auto tr = FHQ_Treap<std::string>();

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        auto str = std::string();
        std::cin >> str;

        tr.insert(str, i);
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i)
    {
        auto str = std::string();
        int x;
        std::cin >> str >> x;

        tr.insert(str, x);
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int x;
        std::cin >> x;

        tr.query(x);
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
