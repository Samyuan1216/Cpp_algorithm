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
    int n, cnt = 0;
    std::vector<Info> info;
    std::vector<Tag> tag;
    std::vector<bool> has_tag;
    std::vector<int> root, left, right;

    int new_node()
    {
        info.push_back({});
        tag.push_back({});
        has_tag.push_back({});
        left.push_back(-1);
        right.push_back(-1);

        return cnt++;
    }

    int clone(int o)
    {
        int rt = new_node();
        info[rt] = info[o];
        tag[rt] = tag[o];
        has_tag[rt] = has_tag[o];
        left[rt] = left[o];
        right[rt] = right[o];

        return rt;
    }

    void up(int i)
    {
        info[i] = info[left[i]] + info[right[i]];
    }

    void apply(int i, const Tag &t)
    {
        bool success = info[i].apply(t); 
        assert(success);

        if (has_tag[i])
        {
            tag[i].apply(t);
        }
        else
        {
            tag[i] = t;
            has_tag[i] = true;
        }
    }

    void down(int i)
    {
        if (has_tag[i])
        {
            left[i] = clone(left[i]), right[i] = clone(right[i]);

            apply(left[i], tag[i]);
            apply(right[i], tag[i]);
            has_tag[i] = false;
        }
    }

    int build(int l, int r)
    {
        int rt = new_node();
        if (l != r)
        {
            int mid = std::midpoint(l, r);
            left[rt] = build(l, mid);
            right[rt] = build(mid + 1, r);

            up(rt);
        }

        return rt;
    }

    int build(int l, int r, const std::vector<Info> &init_arr)
    {
        int rt = new_node();
        if (l == r)
        {
            info[rt] = init_arr[l];
        }
        else
        {
            int mid = std::midpoint(l, r);
            left[rt] = build(l, mid, init_arr);
            right[rt] = build(mid + 1, r, init_arr);

            up(rt);
        }

        return rt;
    }

    int modify(int i, int l, int r, int ql, int qr, const Tag &t)
    {
        int rt = clone(i);
        if (ql <= l && r <= qr)
        {
            if (info[rt].apply(t))
            {
                if (has_tag[rt])
                {
                    tag[rt].apply(t);
                }
                else
                {
                    tag[rt] = t;
                    has_tag[rt] = true;
                }

                return rt;
            }
        }

        int mid = std::midpoint(l, r);
        down(rt);

        if (ql <= mid)
        {
            left[rt] = modify(left[rt], l, mid, ql, qr, t);
        }

        if (qr > mid)
        {
            right[rt] = modify(right[rt], mid + 1, r, ql, qr, t);
        }

        up(rt);
        return rt;
    }

    Info query(int i, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
             return info[i];
        }

        int mid = std::midpoint(l, r);
        down(i);

        if (qr <= mid)
        {
            return query(left[i], l, mid, ql, qr);
        }

        if (ql > mid)
        {
            return query(right[i], mid + 1, r, ql, qr);
        }

        return query(left[i], l, mid, ql, qr) + query(right[i], mid + 1, r, ql, qr);
    }

    template<class F>
    std::optional<int> find_first(int u, int v, int l, int r, int ql, int qr, F check)
    {
        if (ql <= l && r <= qr)
        {
            if (!check(info[u], info[v]))
            {
                return std::nullopt;
            }

            if (l == r)
            {
                return l;
            }
        }

        int mid = std::midpoint(l, r);
        down(u), down(v);

        std::optional<int> res;
        if (ql <= mid)
        {
            res = find_first(left[u], left[v], l, mid, ql, qr, check);
        }

        if (!res && qr > mid)
        {
            res = find_first(right[u], right[v], mid + 1, r, ql, qr, check);
        }

        return res;
    }

    template<class F>
    std::optional<int> find_last(int u, int v, int l, int r, int ql, int qr, F check)
    {
        if (ql <= l && r <= qr)
        {
            if (!check(info[u], info[v]))
            {
                return std::nullopt;
            }

            if (l == r)
            {
                return l;
            }
        }

        int mid = std::midpoint(l, r);
        down(u), down(v);

        std::optional<int> res;
        if (qr > mid)
        {
            res = find_last(right[u], right[v], mid + 1, r, ql, qr, check);
        }

        if (!res && ql <= mid)
        {
            res = find_last(left[u], left[v], l, mid, ql, qr, check);
        }

        return res;
    }

    template<class F>
    std::optional<int> find_kth(int v1, int v2, int v3, int v4, int l, int r, long long k, F get_cnt)
    {
        if (l == r)
        {
            return l;
        }

        int mid = std::midpoint(l, r);
        down(v1), down(v2), down(v3), down(v4);

        long long left_cnt = get_cnt(info[left[v1]]) + get_cnt(info[left[v2]]) - get_cnt(info[left[v3]]) - get_cnt(info[left[v4]]);
        if (k <= left_cnt)
        {
            return find_kth(left[v1], left[v2], left[v3], left[v4], l, mid, k, get_cnt);
        }
        else
        {
            return find_kth(right[v1], right[v2], right[v3], right[v4], mid + 1, r, k - left_cnt, get_cnt);
        }
    }

public:
    Seg_Tree(int n, int m, int r = 0) : n(n), root(m + 1)
    {
        if (n <= 0)
        {
            return;
        }

        info.reserve(4 * n + 80 * m);
        tag.reserve(4 * n + 80 * m);
        has_tag.reserve(4 * n + 80 * m);
        left.reserve(4 * n + 80 * m);
        right.reserve(4 * n + 80 * m);

        root[r] = build(0, n - 1);
    }

    Seg_Tree(const std::vector<Info>& init_arr, int m, int r = 0) : n(init_arr.size()), root(m + 1)
    {
        if (n <= 0)
        {
            return;
        }

        info.reserve(4 * n + 80 * m);
        tag.reserve(4 * n + 80 * m);
        has_tag.reserve(4 * n + 80 * m);
        left.reserve(4 * n + 80 * m);
        right.reserve(4 * n + 80 * m);

        root[r] = build(0, n - 1, init_arr);
    }
    
    void modify(int l, int r, int newv, int oldv, const Tag &t)
    {
        if (l > r || l < 0 || r >= n)
        {
            return;
        }

        root[newv] = modify(root[oldv], 0, n - 1, l, r, t);
    }

    Info query(int l, int r, int v)
    {
        if (l > r || l < 0 || r >= n)
        {
            return Info();
        }

        return query(root[v], 0, n - 1, l, r);
    }

    template<class F>
    std::optional<int> find_first(int l, int r, int newv, int oldv, F check)
    {
        if (l > r || l < 0 || r >= n)
        {
            return std::nullopt;
        }

        return find_first(root[newv], root[oldv], 0, n - 1, l, r, check);
    }

    template<class F>
    std::optional<int> find_last(int l, int r, int newv, int oldv, F check)
    {
        if (l > r || l < 0 || r >= n)
        {
            return std::nullopt;
        }

        return find_last(root[newv], root[oldv], 0, n - 1, l, r, check);
    }

    template<class F>
    std::optional<int> find_kth(long long k, int v1, int v2, int v3, int v4, F get_cnt)
    {
        if (n == 0 || k <= 0)
        {
            return std::nullopt;
        }

        long long total = get_cnt(info[root[v1]]) + get_cnt(info[root[v2]]) - get_cnt(info[root[v3]]) - get_cnt(info[root[v4]]);
        if (total < k)
        {
            return std::nullopt;
        }

        return find_kth(root[v1], root[v2], root[v3], root[v4], 0, n - 1, k, get_cnt);
    }

    void copy_ver(int newv, int oldv)
    {
        if (newv >= 0 && newv < std::ssize(root) && oldv >= 0 && oldv < std::ssize(root))
        {
            root[newv] = root[oldv];
        }
    }
};

struct HLD
{
    const std::vector<std::vector<int>> &g;
    std::vector<int> father, deep, size, son, top, dfn, seg;
    int cnt = 0, n;

    HLD(const std::vector<std::vector<int>> &adj, int root = 0): g(adj), father(std::ssize(adj), -1), deep(std::ssize(adj)), size(std::ssize(adj), 1), son(std::ssize(adj), -1), top(std::ssize(adj)), dfn(std::ssize(adj)), seg(std::ssize(adj)), n(std::ssize(adj))
    {
        dfs1(root, root);
        dfs2(root, root);
    }

    void dfs1(int u, int f)
    {
        father[u] = f;
        deep[u] = deep[f] + 1;

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            dfs1(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    }

    void dfs2(int u, int t)
    {
        top[u] = t;
        dfn[u] = cnt;
        seg[cnt++] = u;

        if (son[u] == -1)
        {
            return;
        }

        dfs2(son[u], t);
        for (auto &v: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs2(v, v);
        }
    }

    int lca(int a, int b)
    {
        while (top[a] != top[b])
        {
            if (deep[top[a]] > deep[top[b]])
            {
                a = father[top[a]];
            }
            else
            {
                b = father[top[b]];
            }
        }

        return (deep[a] <= deep[b]? a: b);
    }

    int dist(int x, int y)
    {
        return deep[x] + deep[y] - 2 * deep[lca(x, y)];
    }

    int intersection(int x1, int y1, int x2, int y2)
    {
        std::vector<int> t = {lca(x1, x2), lca(x1, y2), lca(y1, x2), lca(y1, y2)};
        ranges::sort(t, {}, [&](int x) { return deep[x]; });

        int r1 = lca(x1, y1), r2 = lca(x2, y2);
        if (deep[t[0]] < std::min(deep[r1], deep[r2]) || deep[t[2]] < std::max(deep[r1], deep[r2]))
        {
            return 0;
        }

        return dist(t[2], t[3]) + 1;
    }

    void modify(auto &tr, int x, int y, auto &z)
    {
        while (top[x] != top[y])
        {
            if (deep[top[x]] > deep[top[y]])
            {
                tr.modify(dfn[top[x]], dfn[x], z);
                x = father[top[x]];
            }
            else
            {
                tr.modify(dfn[top[y]], dfn[y], z);
                y = father[top[y]];
            }
        }

        tr.modify(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y]), z);
    }

    auto query(auto &tr, int x, int y)
    {
        i64 ans = -1e18;
        while (top[x] != top[y])
        {
            if (deep[top[x]] > deep[top[y]])
            {
                ans = std::max(ans, tr.query(dfn[top[x]], dfn[x]).max);
                x = father[top[x]];
            }
            else
            {
                ans = std::max(ans, tr.query(dfn[top[y]], dfn[y]).max);
                y = father[top[y]];
            }
        }

        return std::max(ans, tr.query(std::min(dfn[x], dfn[y]), std::max(dfn[x], dfn[y])).max);
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<i64> w(n);
    for (auto &x: w)
    {
        std::cin >> x;
    }

    auto sorted = w;
    {
        ranges::sort(sorted);
        auto [l, r] = ranges::unique(sorted);
        sorted.erase(l, r);
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    struct Tag
    {
        i64 val = 0;

        void apply(const Tag &t)
        {
            val += t.val;
        }
    };

    struct Info
    {
        i64 sum = 0;

        Info operator+(const Info &other) const
        {
            return {sum + other.sum};
        }

        bool apply(const Tag &t)
        {
            sum += t.val;
            return true;
        }
    };

    Seg_Tree<Info, Tag> tr(std::ssize(sorted), n, n);
    [&](this auto &&self, int u, int f) -> void
    {
        int p = std::distance(sorted.begin(), ranges::lower_bound(sorted, w[u]));
        tr.modify(p, p, u, f, {1});

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u);
        }
    } (0, n);

    HLD hld(g);
    int last = 0;

    while (m--)
    {
        int u, v, k;
        std::cin >> u >> v >> k;

        u ^= last;
        --u, --v;

        int l = hld.lca(u, v);
        int lf = (l == 0? n: hld.father[l]);

        auto ans = tr.find_kth(k, u, v, l, lf, [](const Info &info) -> i64
        {
            return info.sum;
        });

        last = sorted[*ans];
        std::cout << last << "\n";
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
