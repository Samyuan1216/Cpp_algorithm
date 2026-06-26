#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

template<typename T = int, typename F = std::less_equal<T>>
struct FHQ_Treap
{
    struct Node
    {
        T key = T{};
        int left = 0;
        int right = 0;
        int size = 0;
        unsigned long long priority = 0;
    };

    std::vector<Node> tr;
    int head = 0;

    inline static std::mt19937_64 gen{std::random_device{}()};

    F compute;

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.push_back({num, 0, 0, 1, gen()});

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

        if (compute(tr[i].key, num))
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

    FHQ_Treap()
    {
        tr.push_back({});
    }

    void insert(T x)
    {
        int l, r;
        split_key(l, r, head, x);
        head = merge(merge(l, new_node(x)), r);
    }

    int query(T x)
    {
        int l, m, r;
        split_key(l, r, head, x);
        split_key(l, m, l, x - 1);

        int res = tr[l].size;
        head = merge(merge(l, m), r);

        return res;
    }
};

void solve()
{
    int n;
    std::string str;
    std::cin >> n >> str;

    std::vector<int> sum(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        sum[i] = sum[i - 1] + (str[i - 1] == 'A'? 1: (str[i - 1] == 'B'? -1: 0));
    }

    FHQ_Treap tr;
    tr.insert(0);

    i64 ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        ans += tr.query(sum[i]);
        tr.insert(sum[i]);
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
