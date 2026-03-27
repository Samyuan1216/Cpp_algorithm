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

    void up(int p)
    {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void lazy(int p, const Tag &t)
    {
        bool success = info[p].lazy(t);
        assert(success);
    }

    void down(int p)
    {
        if (info[p].has_lazy())
        {
            lazy(p << 1, info[p].get_lazy());
            lazy(p << 1 | 1, info[p].get_lazy());

            info[p].clear_lazy();
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
            if (info[p].lazy(t))
            {
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
    std::optional<int> find_kth(int p, int l, int r, i64 k, F get_cnt)
    {
        if (l == r)
        {
            return l;
        }

        int mid = std::midpoint(l, r);
        down(p);

        i64 left_cnt = get_cnt(info[p << 1]);
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
    Seg_Tree(int n) : n(n), info(4 * n + 1)
    {
        build(1, 1, n);
    }

    Seg_Tree(const std::vector<Info>& init_arr) : n(init_arr.size() - 1), info(4 * n + 1)
    {
        build(1, 1, n, init_arr);
    }
    
    void modify(int l, int r, const Tag &t)
    {
        modify(1, 1, n, l, r, t);
    }

    Info query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }

    template<class F> 
    std::optional<int> find_first(int l, int r, F check)
    {
        return find_first(1, 1, n, l, r, check);
    }

    template<class F> 
    std::optional<int> find_last(int l, int r, F check)
    {
        return find_last(1, 1, n, l, r, check);
    }

    template<class F>
    std::optional<int> find_kth(long long k, F get_cnt)
    {
        if (get_cnt(info[1]) < k)
        {
            return std::nullopt;
        }

        return find_kth(1, 1, n, k, get_cnt);
    }
};

void solve()
{
    int H, W, h, w, n;
    std::cin >> H >> W >> h >> w >> n;

    int max_x = W - w + 1, max_y = H - h + 1;
    if (n == 0)
    {
        std::cout << i64(max_x) * max_y << "\n";
        return;
    }

    auto p = std::vector<std::array<int, 4>>();
    p.reserve(2 * n);

    auto Y = std::vector<int>();
    Y.reserve(2 * n);

    for (int i = 0, r, c; i < n; ++i)
    {
        std::cin >> r >> c;

        int x1 = std::max(1, c + 1 - w);
        int x2 = std::min(max_x + 1, c + 1);
        int y1 = std::max(1, r + 1 - h);
        int y2 = std::min(max_y + 1, r + 1);
        if (x1 >= x2 ||  y1 >= y2)
        {
            continue;
        }

        p.push_back({x1, y1, y2, 1});
        p.push_back({x2, y1, y2, -1});
        Y.push_back(y1), Y.push_back(y2);
    }

    ranges::sort(p);
    ranges::sort(Y);

    if (p.empty())
    {
        std::cout << i64(max_x) * max_y << "\n";
        return;
    }

    Y.erase(ranges::unique(Y).begin(), Y.end());
    int m = std::ssize(Y) - 1;

    struct Tag
    {
        int add = 0;
    };

    struct Info
    {
        int all_len = 0;
        int min_cnt = 0;
        int min_uncover = 0;
        Tag tag;

        Info operator+(const Info &other) const
        {
            Info res;
            res.all_len = all_len + other.all_len;
            res.min_cnt = std::min(min_cnt, other.min_cnt);

            if (res.min_cnt == min_cnt)
            {
                res.min_uncover += min_uncover;
            }

            if (res.min_cnt == other.min_cnt)
            {
                res.min_uncover += other.min_uncover;
            }

            return res;
        }

        bool lazy(const Tag &t)
        {
            min_cnt += t.add;
            tag.add += t.add;

            return true;
        }

        bool has_lazy()
        {
            return tag.add != 0;
        }

        Tag get_lazy()
        {
            return tag;
        }

        void clear_lazy()
        {
            tag = Tag{};
        }
    };

    auto init_arr = std::vector<Info>(m + 1);
    for (int i = 1; i <= m; ++i)
    {
        init_arr[i] = {Y[i] - Y[i - 1], 0, Y[i] - Y[i - 1]};
    }

    Seg_Tree<Info, Tag> tr(init_arr);

    i64 num = 0;
    int pre_x = p[0][0];
    for (auto &[x, y1, y2, add]: p)
    {
        int dx = x - pre_x;
        if (dx > 0)
        {
            auto root = tr.query(1, m);

            int len = root.all_len;
            if (root.min_cnt == 0)
            {
                len -= root.min_uncover;
            }

            num += i64(len) * dx;
        }

        pre_x = x;

        int l = ranges::lower_bound(Y, y1) - Y.begin() + 1, r = ranges::lower_bound(Y, y2) - Y.begin();
        tr.modify(l, r, {add});
    }

    std::cout << i64(max_x) * max_y - num << "\n";
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
