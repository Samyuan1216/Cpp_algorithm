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

    Info query(int newv, int oldv, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            Info res;
            res.sum = info[newv].sum - info[oldv].sum;

            return res;
        }

        int mid = std::midpoint(l, r);
        down(newv), down(oldv);

        if (qr <= mid)
        {
            return query(left[newv], left[oldv], l, mid, ql, qr);
        }

        if (ql > mid)
        {
            return query(right[newv], right[oldv], mid + 1, r, ql, qr);
        }

        return query(left[newv], left[oldv], l, mid, ql, qr) + query(right[newv], right[oldv], mid + 1, r, ql, qr);
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
    std::optional<int> find_kth(int u, int v, int l, int r, long long k, F get_cnt)
    {
        if (l == r)
        {
            return l;
        }

        int mid = std::midpoint(l, r);
        down(u), down(v);

        long long left_cnt = get_cnt(info[left[u]]) - get_cnt(info[left[v]]);
        if (k <= left_cnt)
        {
            return find_kth(left[u], left[v], l, mid, k, get_cnt);
        }
        else
        {
            return find_kth(right[u], right[v], mid + 1, r, k - left_cnt, get_cnt);
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

    Info query(int l, int r, int newv, int oldv)
    {
        if (l > r || l < 0 || r >= n)
        {
            return Info();
        }

        return query(root[newv], root[oldv], 0, n - 1, l, r);
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
    std::optional<int> find_kth(long long k, int newv, int oldv, F get_cnt)
    {
        if (n == 0 || k <= 0)
        {
            return std::nullopt;
        }

        long long total = get_cnt(info[root[newv]]) - get_cnt(info[root[oldv]]);
        if (total < k)
        {
            return std::nullopt;
        }

        return find_kth(root[newv], root[oldv], 0, n - 1, k, get_cnt);
    }

    void copy_ver(int newv, int oldv)
    {
        if (newv >= 0 && newv < std::ssize(root) && oldv >= 0 && oldv < std::ssize(root))
        {
            root[newv] = root[oldv];
        }
    }
};

void solve()
{
    int n, q;
    std::cin >> n >> q;

    std::vector<std::vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i)
    {
        std::cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> dfn(n), size(n + 1, 1), deep(n + 1);
    int cnt = 0, maxd = 0;

    [&](this auto &&self, int u, int f) -> void
    {
        dfn[u] = ++cnt;
        deep[dfn[u]] = deep[dfn[f]] + 1;
        maxd = std::max(maxd, deep[dfn[u]]);

        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u);

            size[dfn[u]] += size[dfn[v]];
        }
    } (0, 0);

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

        Info operator+(const Info &other) const
        {
            return {sum + other.sum};
        }

        bool apply(const Tag &t)
        {
            sum += t.add;
            return true;
        }
    };

    Seg_Tree<Info, Tag> tr(maxd + 1, n + 1);
    [&](this auto &&self, int u, int f) -> void
    {
        tr.modify(deep[dfn[u]], deep[dfn[u]], dfn[u], dfn[u] - 1, {size[dfn[u]] - 1});
        for (auto &v: g[u])
        {
            if (v == f)
            {
                continue;
            }

            self(v, u);
        }
    } (0, 0);

    while (q--)
    {
        int a, k;
        std::cin >> a >> k;
        --a;

        i64 ans = std::min(k, deep[dfn[a]] - 1) * i64(size[dfn[a]] - 1);
        ans += tr.query(deep[dfn[a]] + 1, std::min(maxd, deep[dfn[a]] + k), dfn[a] + size[dfn[a]] - 1, dfn[a] - 1).sum;

        std::cout << ans << "\n";
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
