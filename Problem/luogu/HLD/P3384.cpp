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
    static i64 p;
    i64 n, m, r;
    std::cin >> n >> m >> r >> p;
    --r;

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> father(n, -1), deep(n), size(n), son(n, -1);
    [&](this auto &&dfs, int u, int f) -> void
    {
        father[u] = f;
        deep[u] = (f == -1? 0: deep[f]) + 1;
        size[u] = 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (r, -1);

    std::vector<int> top(n), dfn(n), seg(n);
    int cnt = 0;

    [&](this auto &&dfs, int u, int t) -> void
    {
        top[u] = t;
        dfn[u] = cnt;
        seg[cnt++] = u;

        if (son[u] == -1)
        {
            return;
        }

        dfs(son[u], t);
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, v);
        }
    } (r, r);

    struct Tag
    {
        i64 add = 0;

        void apply(const Tag &t)
        {
            add += t.add;
        }
    };

    struct Info
    {
        i64 sum = 0;
        int len = 1;

        Info operator+(const Info &other) const
        {
            return {(sum + other.sum) % p, len + other.len};
        }

        bool apply(const Tag &t)
        {
            sum = (sum + (t.add * len) % p) % p;

            return true;
        }
    };

    std::vector<Info> init(n);
    for (int i = 0; i < n; ++i)
    {
        init[i].sum = arr[seg[i]] % p;
    }

    Seg_Tree<Info, Tag> tr(init);
    while (m--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x, y;
            i64 z;
            std::cin >> x >> y >> z;

            z %= p;
            --x, --y;

            while (top[x] != top[y])
            {
                if (deep[top[x]] <= deep[top[y]])
                {
                    tr.modify(dfn[top[y]], dfn[y], {z});
                    y = father[top[y]];
                }
                else
                {
                    tr.modify(dfn[top[x]], dfn[x], {z});
                    x = father[top[x]];
                }
            }

            tr.modify(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y]), {z});
        }
        else if (op == 2)
        {
            int x, y;
            std::cin >> x >> y;
            --x, --y;

            i64 ans = 0;
            while (top[x] != top[y])
            {
                if (deep[top[x]] <= deep[top[y]])
                {
                    ans = (ans + tr.query(dfn[top[y]], dfn[y]).sum) % p;
                    y = father[top[y]];
                }
                else
                {
                    ans = (ans + tr.query(dfn[top[x]], dfn[x]).sum) % p;
                    x = father[top[x]];
                }
            }

            ans = (ans + tr.query(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y])).sum) % p;
            std::cout << ans << "\n";
        }
        else if (op == 3)
        {
            int x;
            i64 z;
            std::cin >> x >> z;
            --x;

            tr.modify(dfn[x], dfn[x] + size[x] - 1, {z});
        }
        else
        {
            int x;
            std::cin >> x;
            --x;

            std::cout << tr.query(dfn[x], dfn[x] + size[x] - 1).sum << "\n";
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
