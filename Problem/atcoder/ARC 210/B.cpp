#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

#ifndef YUAN_DEBUG
struct __X
{
    __X& operator<<(const auto& str) {return *this;}
    void sp([[maybe_unused]] const std::string& str = "") {}
} dout;
#define debug(x)
#endif

template<typename T = int, typename F = std::less<T>>
struct FHQ_Treap
{
private:
    struct Node
    {
        T key = T{};
        i64 sum = 0;
        int size = 0;
        uint64_t priority = 0;
        bool reverse = false;
    };

    std::vector<Node> tr;
    std::vector<int> left, right;
    int head = 0;

    inline static std::mt19937_64 gen{std::random_device{}()};

    F compute;

    int new_node(const T &num = T{})
    {
        int i = tr.size();
        tr.push_back({num, num, 1, gen(), false});
        left.push_back({});
        right.push_back({});

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[left[i]].size + tr[right[i]].size + 1;
        tr[i].sum = tr[left[i]].sum + tr[right[i]].sum + tr[i].key;
    }

    void down(int i)
    {
        if (tr[i].reverse)
        {
            if (left[i] != 0)
            {
                tr[left[i]].reverse = !tr[left[i]].reverse;
            }

            if (right[i] != 0)
            {
                tr[right[i]].reverse = !tr[right[i]].reverse;
            }

            std::swap(left[i], right[i]);
            tr[i].reverse = false;
        }
    }

    void split_key(int &l, int &r, int i, const T &num)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        down(i);
        if (!compute(num, tr[i].key))
        {
            l = i;
            split_key(right[i], r, right[i], num);
        }
        else
        {
            r = i;
            split_key(l, left[i], left[i], num);
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

        down(i);
        if (tr[left[i]].size + 1 <= rank)
        {
            l = i;
            split_rank(right[i], r, right[i], rank - tr[left[i]].size - 1);
        }
        else
        {
            r = i;
            split_rank(l, left[i], left[i], rank);
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
            down(l);

            right[l] = merge(right[l], r);

            up(l);
            return l;
        }
        else
        {
            down(r);

            left[r] = merge(l, left[r]);

            up(r);
            return r;
        }
    }
public:
    FHQ_Treap()
    {
        tr.push_back({});
        left.push_back({});
        right.push_back({});
    }

    void insert_key(const T &num)
    {
        int l, r;
        split_key(l, r, head, num);

        head = merge(merge(l, new_node(num)), r);
    }

    i64 query(int n, int m)
    {
        int l, r;
        split_rank(l, r, head, n / 2);

        i64 res = tr[l].sum;
        head = merge(l, r);

        split_rank(l, r, head, n + m - n / 2);

        res += tr[r].sum;
        head = merge(l, r);

        return res;
    }

    void insert_rank(const T &num)
    {
        insert_rank(num, tr[head].size);
    }

    void insert_rank(const T &num, int rank)
    {
        assert(rank >= 0 && rank <= tr[head].size);

        int l, r;
        split_rank(l, r, head, rank);

        head = merge(merge(l, new_node(num)), r);
    }

    void erase_key(const T &num)
    {
        int l, m, r;
        split_key(l, r, head, num);
        split_key(l, m, l, num - 1);

        m = merge(left[m], right[m]);
        head = merge(merge(l, m), r);
    }

    void erase_rank(int rank)
    {
        assert(rank >= 0 && rank < tr[head].size);

        int l, m, r;
        split_rank(l, r, head, rank + 1);
        split_rank(l, m, l, rank);

        head = merge(l, r);
    }

    std::optional<T> kth(int rank)
    {
        if (rank < 0 || rank >= tr[head].size)
        {
            return std::nullopt;
        }

        int l, m, r;
        split_rank(l, r, head, rank + 1);
        split_rank(l, m, l, rank);

        T res = tr[m].key;
        head = merge(merge(l, m), r);

        return res;
    }

    int rank(const T &num)
    {
        int l, r;
        split_key(l, r, head, num - 1);

        int res = tr[l].size;
        head = merge(l, r);

        return res;
    }

    void reverse(int left, int right)
    {
        assert(left >= 0 && left <= right && right < tr[head].size);

        int l, m, r;
        split_rank(l, r, head, right + 1);
        split_rank(l, m, l, left);

        tr[m].reverse = !tr[m].reverse;
        head = merge(merge(l, m), r);
    }

    std::optional<T> prev(const T &num)
    {
        int l, m, r;
        split_key(l, r, head, num - 1);

        if (l == 0)
        {
            head = merge(l, r);
            return std::nullopt;
        }

        split_rank(l, m, l, tr[l].size - 1);

        T res = tr[m].key;
        head = merge(merge(l, m), r);

        return res;
    }

    std::optional<T> next(const T &num)
    {
        int l, m, r;
        split_key(l, r, head, num);

        if (r == 0)
        {
            head = merge(l, r);
            return std::nullopt;
        }

        split_rank(m, r, r, 1);

        T res = tr[m].key;
        head = merge(merge(l, m), r);

        return res;
    }
};

void solve()
{
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> a(n);
    for (auto &x: a)
    {
        std::cin >> x;
    }

    std::vector<int> b(m);
    for (auto &x: b)
    {
        std::cin >> x;
    }

    FHQ_Treap tr;
    for (auto &x: a)
    {
        tr.insert_key(x);
    }

    for (auto &x: b)
    {
        tr.insert_key(x);
    }

    while (q--)
    {
        int t, i, x;
        std::cin >> t >> i >> x;
        --i;

        tr.erase_key((t == 1? a: b)[i]);
        (t == 1? a: b)[i] = x;

        tr.insert_key(x);

        std::cout << tr.query(n, m) << "\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    // std::cin >> t;
    while (t--)
    {
        solve();
    }
}