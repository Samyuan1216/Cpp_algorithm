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
    int n;
    std::cin >> n;

    std::vector<std::array<i64, 2>> arr(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> arr[i][0];

        arr[i][1] = i;
    }

    ranges::sort(arr);

    struct Tag
    {
        i64 val = 0;

        void apply(const Tag &t)
        {
            val = t.val;
        }
    };

    struct Info
    {
        i64 sum = 0, pre = 0, suf = 0;

        Info operator+(const Info &other) const
        {
            return {sum + other.sum, std::max(pre, sum + other.pre), std::max(other.suf, other.sum + suf)};
        }

        bool apply(const Tag &t)
        {
            sum = pre = suf = t.val;
            return true;
        }
    };

    std::vector<Info> init(n, {1, 1, 1});
    Seg_Tree<Info, Tag> tr(init, n);

    for (int i = 1; i < n; ++i)
    {
        tr.modify(arr[i - 1][1], arr[i - 1][1], i, i - 1, {-1});
    }

    int q;
    std::cin >> q;

    i64 last = 0;
    while (q--)
    {
        std::array<i64, 4> t;
        std::cin >> t[0] >> t[1] >> t[2] >> t[3];

        for (auto &x: t)
        {
            x = (x + last) % n;
        }

        ranges::sort(t);

        auto check = [&](i64 mid) -> bool
        {
            int res = tr.query(t[0], t[1], mid).suf + tr.query(t[2], t[3], mid).pre;
            if (t[1] + 1 <= t[2] - 1)
            {
                res += tr.query(t[1] + 1, t[2] - 1, mid).sum;
            }

            return res >= 0;
        };

        auto find = [&](auto l, auto r, bool find_first = true) -> std::optional<decltype(l)>
        {
            std::optional<decltype(l)> ans;
            while (l <= r)
            {
                auto mid = std::midpoint(l, r);
                if (check(mid))
                {
                    ans = mid;
                    find_first? (r = mid - 1): (l = mid + 1);
                }
                else
                {
                    find_first? (l = mid + 1): (r = mid - 1);
                }
            }
        
            return ans;
        };

        last = arr[*find(0, n - 1, false)][0];
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
