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

template<class Info, class Tag>
struct Seg_Tree
{
private:
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

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    constexpr int limit = 20;
    int cnt = 0;
    std::vector<std::array<int, limit>> rmq(n);
    std::vector<int> dfn(n), depth(n);

    [&](this auto &&dfs, int u, int f) -> void
    {
        dfn[u] = cnt++;
        depth[u] = depth[f] + 1;
        rmq[dfn[u]][0] = f;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);
        }
    } (0, 0);

    auto up = [&](int x, int y) -> int
    {
        return (dfn[x] < dfn[y]? x: y);
    };

    for (int pre = 0, cur = 1; cur < limit; ++pre, ++cur)
    {
        for (int i = 0; i + (1 << cur) - 1 < n; ++i)
        {
            rmq[i][cur] = up(rmq[i][pre], rmq[i + (1 << pre)][pre]);
        }
    }

    auto lca = [&](int x, int y) -> int
    {
        if (x == y)
        {
            return x;
        }

        x = dfn[x], y = dfn[y];
        if (x > y)
        {
            std::swap(x, y);
        }
        ++x;

        int k = std::bit_width(unsigned(y - x + 1)) - 1;
        return up(rmq[x][k], rmq[y - (1 << k) + 1][k]);
    };

    static auto dist = [&](int u, int v) -> int
    {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    };

    struct Tag
    {
        int id = -1;
        bool black = false;

        void apply(const Tag &t)
        {
            id = t.id;
            black = t.black;
        }
    };

    struct Info
    {
        int u = -1, v = -1;

        Info operator+(const Info &other) const
        {
            if (u == -1)
            {
                return other;
            }

            if (other.u == -1)
            {
                return *this;
            }

            auto pts = std::array{u, v, other.u, other.v};
            Info res;

            int max_dist = -1;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = i; j < 4; ++j)
                {
                    int d = dist(pts[i], pts[j]);
                    if (d > max_dist)
                    {
                        res = {pts[i], pts[j]};
                        max_dist = d;
                    }
                }
            }

            return res;
        }

        bool apply(const Tag &t)
        {
            if (t.black)
            {
                u = v = t.id;
            }
            else
            {
                u = v = -1;
            }

            return true;
        }
    };

    std::vector<Info> init_arr(n);
    for (int i = 0; i < n; ++i)
    {
        init_arr[i] = {i, i};
    }

    Seg_Tree<Info, Tag> tr(init_arr);
    std::vector<bool> black(n, true);

    int q;
    std::cin >> q;

    while (q--)
    {
        int x;
        std::cin >> x;
        --x;

        black[x] = !black[x];
        tr.modify(x, x, {x, black[x]});

        Info ans = tr.query(0, n - 1);
        std::cout << dist(ans.u, ans.v) << "\n";
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
