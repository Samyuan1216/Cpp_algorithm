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

template<class Info, class Tag>
class Seg_Tree
{
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    std::vector<bool> has_tag;

    void up(int p)
    {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void apply(int p, const Tag &t)
    {
        bool success = info[p].apply(t); 
        assert(success);

        if (has_tag[p])
        {
            tag[p].apply(t);
        }
        else
        {
            tag[p] = t;
            has_tag[p] = true;
        }
    }

    void down(int p)
    {
        if (has_tag[p])
        {
            apply(p << 1, tag[p]);
            apply(p << 1 | 1, tag[p]);
            has_tag[p] = false;
        }
    }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            return;
        }

        int mid = std::midpoint(l, r);
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);

        up(p);
    }

    void build(int p, int l, int r, const std::vector<Info> &init_arr)
    {
        if (l == r)
        {
            info[p] = init_arr[l];
            return;
        }

        int mid = std::midpoint(l, r);
        build(p << 1, l, mid, init_arr);
        build(p << 1 | 1, mid + 1, r, init_arr);

        up(p);
    }

    void modify(int p, int l, int r, int ql, int qr, const Tag &t)
    {
        if (ql <= l && r <= qr)
        {
            if (info[p].apply(t))
            {
                if (has_tag[p])
                {
                    tag[p].apply(t);
                }
                else
                {
                    tag[p] = t;
                    has_tag[p] = true;
                }
                return;
            }
        }

        int mid = std::midpoint(l, r);
        down(p);

        if (ql <= mid)
        {
            modify(p << 1, l, mid, ql, qr, t);
        }

        if (qr > mid)
        {
            modify(p << 1 | 1, mid + 1, r, ql, qr, t);
        }

        up(p);
    }

    Info query(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
             return info[p];
        }

        int mid = std::midpoint(l, r);
        down(p);

        if (qr <= mid)
        {
            return query(p << 1, l, mid, ql, qr);
        }

        if (ql > mid)
        {
            return query(p << 1 | 1, mid + 1, r, ql, qr);
        }

        return query(p << 1, l, mid, ql, qr) + query(p << 1 | 1, mid + 1, r, ql, qr);
    }

    template<class F>
    std::optional<int> find_first(int p, int l, int r, int ql, int qr, F check)
    {
        if (ql <= l && r <= qr)
        {
            if (!check(info[p]))
            {
                return std::nullopt;
            }

            if (l == r)
            {
                return l;
            }
        }

        int mid = std::midpoint(l, r);
        down(p);

        std::optional<int> res;
        if (ql <= mid)
        {
            res = find_first(p << 1, l, mid, ql, qr, check);
        }

        if (!res && qr > mid)
        {
            res = find_first(p << 1 | 1, mid + 1, r, ql, qr, check);
        }

        return res;
    }

    template<class F>
    std::optional<int> find_last(int p, int l, int r, int ql, int qr, F check)
    {
        if (ql <= l && r <= qr)
        {
            if (!check(info[p]))
            {
                return std::nullopt;
            }

            if (l == r)
            {
                return l;
            }
        }

        int mid = std::midpoint(l, r);
        down(p);

        std::optional<int> res;
        if (qr > mid)
        {
            res = find_last(p << 1 | 1, mid + 1, r, ql, qr, check);
        }

        if (!res && ql <= mid)
        {
            res = find_last(p << 1, l, mid, ql, qr, check);
        }

        return res;
    }

    template<class F>
    std::optional<int> find_kth(int p, int l, int r, long long k, F get_cnt)
    {
        if (l == r)
        {
            return l;
        }

        int mid = std::midpoint(l, r);
        down(p);

        long long left_cnt = get_cnt(info[p << 1]);
        if (k <= left_cnt)
        {
            return find_kth(p << 1, l, mid, k, get_cnt);
        }
        else
        {
            return find_kth(p << 1 | 1, mid + 1, r, k - left_cnt, get_cnt);
        }
    }

public:
    Seg_Tree(int n) : n(n), info(4 * n), tag(4 * n), has_tag(4 * n, false)
    {
        if (n > 0)
        {
            build(1, 0, n - 1);
        }
    }

    Seg_Tree(const std::vector<Info>& init_arr) : n(init_arr.size()), info(4 * n), tag(4 * n), has_tag(4 * n, false)
    {
        if (n > 0)
        {
            build(1, 0, n - 1, init_arr);
        }
    }
    
    void modify(int l, int r, const Tag &t)
    {
        if (l <= r && l >= 0 && r < n)
        {
            modify(1, 0, n - 1, l, r, t);
        }
    }

    Info query(int l, int r)
    {
        if (l > r || l < 0 || r >= n)
        {
            return Info();
        }

        return query(1, 0, n - 1, l, r);
    }

    template<class F> 
    std::optional<int> find_first(int l, int r, F check)
    {
        if (l > r || l < 0 || r >= n)
        {
            return std::nullopt;
        }

        return find_first(1, 0, n - 1, l, r, check);
    }

    template<class F> 
    std::optional<int> find_last(int l, int r, F check)
    {
        if (l > r || l < 0 || r >= n)
        {
            return std::nullopt;
        }

        return find_last(1, 0, n - 1, l, r, check);
    }

    template<class F>
    std::optional<int> find_kth(long long k, F get_cnt)
    {
        if (n == 0 || get_cnt(info[1]) < k)
        {
            return std::nullopt;
        }

        return find_kth(1, 0, n - 1, k, get_cnt);
    }
};

void solve()
{
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    int m;
    std::cin >> m;

    std::vector<std::tuple<std::string, int, int>> query(m);
    std::vector<std::array<int, 2>> u;

    for (auto &[op, x, y]: query)
    {
        std::cin >> op;
        if (op == "F3")
        {
            continue;
        }

        std::cin >> x;
        if (op == "A3")
        {
            continue;
        }

        --x;
        if (op == "F1" || op == "F2")
        {
            continue;
        }

        std::cin >> y;
        if (op == "U")
        {
            --y;
            u.push_back({x, y});
        }
    }

    std::vector<int> father(2 * n);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    };

    std::vector<std::vector<int>> g(2 * n);
    int unused = n;

    for (auto &[x, y]: u)
    {
        x = find(x), y = find(y);
        if (x == y)
        {
            continue;
        }

        g[x].push_back(unused);
        g[unused].push_back(x);

        g[y].push_back(unused);
        g[unused].push_back(y);

        father[x] = father[y] = unused++;
    }

    std::vector<int> ord(n);
    int index = 0;

    for (int i = 0; i < unused; ++i)
    {
        if (i != father[i])
        {
            continue;
        }

        [&](this auto &&dfs, int u, int f) -> void
        {
            bool status = true;
            for (auto &v: g[u])
            {
                if (v == f)
                {
                    continue;
                }

                status = false;
                dfs(v, u);
            }

            if (status)
            {
                ord[u] = index++;
            }
        } (i, -1);
    }

    struct Tag
    {
        int add = 0;

        void apply(const Tag &t)
        {
            add += t.add;
        }
    };

    struct Info
    {
        int max = lim<int>::min();

        Info operator+(const Info &other)
        {
            return {std::max(max, other.max)};
        }

        bool apply(const Tag &t)
        {
            max += t.add;
            return true;
        }
    };

    std::vector<Info> num(n);
    for (int i = 0; i < n; ++i)
    {
        num[ord[i]].max = arr[i];
    }

    Seg_Tree<Info, Tag> tr(num);

    ranges::iota(father, 0);
    unused = n;

    std::vector<std::array<int, 2>> range(2 * n);
    for (int i = 0; i < 2 * n; ++i)
    {
        range[i] = {i, i};
    }

    for (auto &[op, x, y]: query)
    {
        if (op == "U")
        {
            x = find(ord[x]), y = find(ord[y]);
            range[unused] = {std::min(range[x][0], range[y][0]), std::max(range[x][1], range[y][1])};
            father[x] = father[y] = unused++;
        }
        else if (op == "A1")
        {
            tr.modify(ord[x], ord[x], {y});
        }
        else if (op == "A2")
        {
            tr.modify(range[find(ord[x])][0], range[find(ord[x])][1], {y});
        }
        else if (op == "A3")
        {
            tr.modify(0, n - 1, {x});
        }
        else if (op == "F1")
        {
            std::cout << tr.query(ord[x], ord[x]).max << "\n";
        }
        else if (op == "F2")
        {
            std::cout << tr.query(range[find(ord[x])][0], range[find(ord[x])][1]).max << "\n";
        }
        else
        {
            std::cout << tr.query(0, n - 1).max << "\n";
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
