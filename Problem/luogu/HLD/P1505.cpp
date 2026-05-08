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
    int n;
    std::cin >> n;

    std::vector<std::vector<std::array<int, 3>>> g(n);
    for (int i = 1, u, v, w; i < n; ++i)
    {
        std::cin >> u >> v >> w;

        g[u].push_back({v, w, i});
        g[v].push_back({u, w, i});
    }

    std::vector<int> father(n, -1), deep(n), size(n), son(n, -1), edge(n), weight(n);
    [&](this auto &&dfs, int u, int f) -> void
    {
        father[u] = f;
        deep[u] = (f == -1? 0: deep[f]) + 1;
        size[u] = 1;

        for (auto &[v, w, i]: g[u])
        {
            if (v == f)
            {
                continue;
            }

            edge[i] = v;
            weight[v] = w;

            dfs(v, u);

            size[u] += size[v];
            if (son[u] == -1 || size[son[u]] < size[v])
            {
                son[u] = v;
            }
        }
    } (0, -1);

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
        for (auto &[v, w, i]: g[u])
        {
            if (v == father[u] || v == son[u])
            {
                continue;
            }

            dfs(v, v);
        }
    } (0, 0);

    struct Tag
    {
        int mul = 1, cover = 0;
        bool has_cover = false;

        void apply(const Tag &t)
        {
            if (t.has_cover)
            {
                mul = 1;
                cover = t.cover;
                has_cover = true;
            }
            else
            {
                if (has_cover)
                {
                    cover *= t.mul;
                }
                else
                {
                    mul *= t.mul;
                }
            }
        }
    };

    struct Info
    {
        int sum = 0, len = 1, max = -1e9, min = 1e9;

        Info operator+(const Info &other)
        {
            return {sum + other.sum, len + other.len, std::max(max, other.max), std::min(min, other.min)};
        }

        bool apply(const Tag &t)
        {
            if (t.has_cover)
            {
                sum = t.cover * len;
                min = max = t.cover;
            }
            else
            {
                sum *= t.mul;

                if (t.mul < 0)
                {
                    std::swap(min, max);
                }

                min *= t.mul;
                max *= t.mul;
            }

            return true;
        }
    };

    std::vector<Info> init(n);
    for (int i = 0; i < n; ++i)
    {
        init[i] = {weight[seg[i]], 1, weight[seg[i]], weight[seg[i]]};
    }

    Seg_Tree<Info, Tag> tr(init);

    int m;
    std::cin >> m;

    while (m--)
    {
        std::string op;
        std::cin >> op;

        if (op[0] == 'C')
        {
            int i, w;
            std::cin >> i >> w;

            tr.modify(dfn[edge[i]], dfn[edge[i]], {1, w, true});
        }
        else if (op[0] == 'N')
        {
            int u, v;
            std::cin >> u >> v;

            while (top[u] != top[v])
            {
                if (deep[top[u]] > deep[top[v]])
                {
                    tr.modify(dfn[top[u]], dfn[u], {-1, 0, false});
                    u = father[top[u]];
                }
                else
                {
                    tr.modify(dfn[top[v]], dfn[v], {-1, 0, false});
                    v = father[top[v]];
                }
            }

            tr.modify(std::min(dfn[u], dfn[v]) + 1, std::max(dfn[u], dfn[v]), {-1, 0, false});
        }
        else if (op[0] == 'S')
        {
            int u, v;
            std::cin >> u >> v;

            int ans = 0;
            while (top[u] != top[v])
            {
                if (deep[top[u]] > deep[top[v]])
                {
                    ans += tr.query(dfn[top[u]], dfn[u]).sum;
                    u = father[top[u]];
                }
                else
                {
                    ans += tr.query(dfn[top[v]], dfn[v]).sum;
                    v = father[top[v]];
                }
            }

            ans += tr.query(std::min(dfn[u], dfn[v]) + 1, std::max(dfn[u], dfn[v])).sum;
            std::cout << ans << "\n";
        }
        else if (op[1] == 'A')
        {
            int u, v;
            std::cin >> u >> v;

            int ans = -2e9;
            while (top[u] != top[v])
            {
                if (deep[top[u]] > deep[top[v]])
                {
                    ans = std::max(ans, tr.query(dfn[top[u]], dfn[u]).max);
                    u = father[top[u]];
                }
                else
                {
                    ans = std::max(ans, tr.query(dfn[top[v]], dfn[v]).max);
                    v = father[top[v]];
                }
            }

            ans = std::max(ans, tr.query(std::min(dfn[u], dfn[v]) + 1, std::max(dfn[u], dfn[v])).max);
            std::cout << ans << "\n";
        }
        else
        {
            int u, v;
            std::cin >> u >> v;

            int ans = 2e9;
            while (top[u] != top[v])
            {
                if (deep[top[u]] > deep[top[v]])
                {
                    ans = std::min(ans, tr.query(dfn[top[u]], dfn[u]).min);
                    u = father[top[u]];
                }
                else
                {
                    ans = std::min(ans, tr.query(dfn[top[v]], dfn[v]).min);
                    v = father[top[v]];
                }
            }

            ans = std::min(ans, tr.query(std::min(dfn[u], dfn[v]) + 1, std::max(dfn[u], dfn[v])).min);
            std::cout << ans << "\n";
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
