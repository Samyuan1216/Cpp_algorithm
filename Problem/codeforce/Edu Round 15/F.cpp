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

struct Data
{
    int val, cnt, idx;

    auto operator<=>(const Data &other) const = default;
    auto operator<=>(int other) const
    {
        return val <=> other;
    }

    auto operator==(int other) const
    {
        return val == other;
    }
};

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
        int lazy_val = 0;
        int lazy_cnt = 0;
    };

    std::vector<Node> tr;
    int head = 0;

    std::mt19937 gen{std::random_device{}()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    int new_node(const T &num)
    {
        int i = tr.size();
        tr.emplace_back(num, 0, 0, 1, dis(gen), 0, 0);

        return i;
    }

    void up(int i)
    {
        tr[i].size = tr[tr[i].left].size + tr[tr[i].right].size + 1;
    }

    void down(int i)
    {
        if (i == 0 || (tr[i].lazy_val == 0 && tr[i].lazy_cnt == 0))
        {
            return;
        }

        int l = tr[i].left, r = tr[i].right;
        if (l != 0)
        {
            tr[l].key.val -= tr[i].lazy_val;
            tr[l].key.cnt += tr[i].lazy_cnt;

            tr[l].lazy_val += tr[i].lazy_val;
            tr[l].lazy_cnt += tr[i].lazy_cnt;
        }

        if (r != 0)
        {
            tr[r].key.val -= tr[i].lazy_val;
            tr[r].key.cnt += tr[i].lazy_cnt;

            tr[r].lazy_val += tr[i].lazy_val;
            tr[r].lazy_cnt += tr[i].lazy_cnt;
        }

        tr[i].lazy_val = tr[i].lazy_cnt = 0;
    }

    void split_key(int &l, int &r, int i, int num)
    {
        if (i == 0)
        {
            l = r = 0;
            return;
        }

        down(i);
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
            down(l);
            tr[l].right = merge(tr[l].right, r);

            up(l);
            return l;
        }
        else
        {
            down(r);
            tr[r].left = merge(l, tr[r].left);

            up(r);
            return r;
        }
    }

    int insert_to(int root, int u)
    {
        tr[u].left = tr[u].right = 0;
        tr[u].size = 1;

        int l, r;
        split_key(l, r, root, tr[u].key.val);

        return merge(merge(l, u), r);
    }
public:
    FHQ_Treap()
    {
        tr.emplace_back();
    }

    void insert(const T &num)
    {
        int l, r;
        split_key(l, r, head, num.val);

        head = merge(merge(l, new_node(num)), r);
    }

    void cost(int c)
    {
        int l, m, r;
        split_key(l, r, head, 2 * c - 1);
        split_key(l, m, l, c - 1);

        if (r != 0)
        {
            tr[r].key.val -= c;
            tr[r].key.cnt += 1;

            tr[r].lazy_val += c;
            tr[r].lazy_cnt += 1;
        }

        auto dfs = [&](auto &&self, int u) -> void
        {
            if (u == 0)
            {
                return;
            }

            down(u);

            self(self, tr[u].left);
            self(self, tr[u].right);

            tr[u].key.val -= c;
            tr[u].key.cnt += 1;

            l = insert_to(l, u);
        };

        dfs(dfs, m);
        head = merge(l, r);
    }

    void print(int k)
    {
        auto ans = std::vector<int>(k);
        auto dfs = [&](auto &&self, int u) -> void
        {
            if (u == 0)
            {
                return;
            }

            down(u);

            self(self, tr[u].left);
            self(self, tr[u].right);

            ans[tr[u].key.idx] = tr[u].key.cnt;
        };

        dfs(dfs, head);

        for (int i = 0; i < k; ++i)
        {
            std::cout << ans[i] << " \n"[i == k - 1];
        }
    }
};

void solve()
{
    int n;
    std::cin >> n;

    auto arr = std::vector(n, std::array<int, 2>());
    for (auto &[c, q]: arr)
    {
        std::cin >> c >> q;
    }

    ranges::sort(arr, [](auto &a, auto &b)
    {
        if (a[1] != b[1])
        {
            return a[1] > b[1];
        }

        return a[0] < b[0];
    });

    int k;
    std::cin >> k;

    FHQ_Treap<Data> tr;
    for (int i = 0, x; i < k; ++i)
    {
        std::cin >> x;

        tr.insert({x, 0, i});
    }

    for (auto &[c, _]: arr)
    {
        tr.cost(c);
    }

    tr.print(k);
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
