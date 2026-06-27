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
    int n, q;
    std::cin >> n >> q;

    struct Tag
    {
        i64 dc1 = 0, dc2 = 0, dsum = 0;

        void apply(const Tag &t)
        {
            dc1 += t.dc1;
            dc2 += t.dc2;
            dsum += t.dsum;
        }
    };

    struct Info
    {
        i64 c1 = 0, c2 = 0, sum = 0;

        Info operator+(const Info &other) const
        {
            return {c1 + other.c1, c2 + other.c2, sum + other.sum};
        }

        bool apply(const Tag &t)
        {
            c1 += t.dc1;
            c2 += t.dc2;
            sum += t.dsum;

            return true;
        }
    };

    constexpr int MAXA = 1e6;
    Seg_Tree<Info, Tag> tr(MAXA + 1);

    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i] >> b[i];

        if (b[i] == 1)
        {
            tr.modify(a[i], a[i], {1, 0, a[i]});
        }
        else
        {
            tr.modify(a[i], a[i], {0, 1, a[i]});
        }
    }

    while (q--)
    {
        int w, x, y;
        std::cin >> w >> x >> y;
        --w;

        if (b[w] == 1)
        {
            tr.modify(a[w], a[w], {-1, 0, -a[w]});
        }
        else
        {
            tr.modify(a[w], a[w], {0, -1, -a[w]});
        }

        a[w] = x, b[w] = y;

        if (b[w] == 1)
        {
            tr.modify(a[w], a[w], {1, 0, a[w]});
        }
        else
        {
            tr.modify(a[w], a[w], {0, 1, a[w]});
        }

        Info total = tr.query(0, MAXA);
        if (total.c1 == 0)
        {
            int min = *tr.find_first(0, MAXA, [](const Info &info)
            {
                return info.c1 + info.c2 > 0;
            });

            std::cout << 2 * total.sum - min << "\n";
            continue;
        }
        else if (total.c1 == n)
        {
            std::cout << total.sum << "\n";
            continue;
        }

        int r = *tr.find_kth(total.c1, [](const Info &info)
        {
            return info.c1 + info.c2;
        });

        Info left = tr.query(0, r - 1);
        i64 rem = total.c1 - (left.c1 + left.c2);
        Info infor = tr.query(r, r);

        if (left.c2 > 0 || infor.c2 > 0)
        {
            i64 sum = left.sum + rem * r;
            std::cout <<  2 * total.sum - sum << "\n";
        }
        else
        {
            i64 sum = left.sum + rem * r;
            int min = *tr.find_first(0, MAXA, [](const Info &info)
            {
                return info.c2 > 0;
            });

            sum += -r + min;
            std::cout << 2 * total.sum - sum << "\n";
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
