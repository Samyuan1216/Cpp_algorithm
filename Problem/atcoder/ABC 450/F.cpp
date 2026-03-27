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

template <int MOD_ID>
class ModInt
{
    int val;
    inline static int dynamic_mod = 998244353;
public:
    ModInt(i64 v = 0)
    {
        int mod = get_mod();
        v %= mod;

        if (v < 0)
        {
            v += mod;
        }

        val = static_cast<int>(v);
    }

    static int get_mod()
    {
        if constexpr (MOD_ID > 0)
        {
            return MOD_ID;
        }
        else
        {
            return dynamic_mod;
        }
    }

    static void set_mod(int m)
    {
        if constexpr (MOD_ID <= 0)
        {
            dynamic_mod = m;
        }
    }

    ModInt pow(i64 p) const
    {
        ModInt res = 1, a = *this;
        while (p > 0)
        {
            if (p & 1)
            {
                res *= a;
            }
            a *= a;
            p >>= 1;
        }

        return res;
    }

    ModInt inv() const
    {
        auto exgcd = [&](auto &&self, int a, int b) -> std::array<int, 3>
        {
            if (b == 0)
            {
                return {a, 1, 0};
            }
            
            auto [d, x, y] = self(self, b, a % b);
            return {d, y, x - y * (a / b)};
        };

        auto [d, x, y] = exgcd(exgcd, val, get_mod());
        
        return ModInt(x);
    }

    ModInt& operator+=(const ModInt& other)
    {
        val += other.val;
        if (val >= get_mod())
        {
            val -= get_mod();
        }

        return *this;
    }

    ModInt& operator-=(const ModInt& other)
    {
        val -= other.val;
        if (val < 0)
        {
            val += get_mod();
        }

        return *this;
    }

    ModInt& operator*=(const ModInt& other)
    {
        val = static_cast<int>(1LL * val * other.val % get_mod());
        return *this;
    }

    ModInt& operator/=(const ModInt& other)
    {
        return *this *= other.inv();
    }

    ModInt operator-() const
    {
        return ModInt(val == 0 ? 0 : get_mod() - val);
    }

    ModInt& operator++()
    {
        return *this += 1;
    }

    ModInt& operator--()
    {
        return *this -= 1;
    }

    ModInt operator++(int)
    {
        ModInt temp = *this;
        *this += 1;

        return temp;
    }

    ModInt operator--(int)
    {
        ModInt temp = *this; 
        *this -= 1; 

        return temp;
    }

    friend ModInt operator+(ModInt a, const ModInt& b)
    {
        return a += b;
    }

    friend ModInt operator-(ModInt a, const ModInt& b)
    {
        return a -= b;
    }

    friend ModInt operator*(ModInt a, const ModInt& b)
    {
        return a *= b;
    }

    friend ModInt operator/(ModInt a, const ModInt& b)
    {
        return a /= b;
    }

    auto operator<=>(const ModInt& other) const = default;

    friend std::istream& operator>>(std::istream& is, ModInt& m)
    {
        i64 v;
        is >> v;

        m = ModInt(v);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const ModInt& m)
    {
        return os << m.val;
    }
};

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
    Seg_Tree(int n) : n(n), info(4 * n + 1) {}

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
    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    int n, m;
    std::cin >> n >> m;

    auto edges = std::vector(m, std::array<int, 2>());
    for (auto &edge: edges)
    {
        std::cin >> edge[0] >> edge[1];
    }

    ranges::sort(edges);

    struct Tag
    {
        mint mul = 1;
        mint add = 0;
    };

    struct Info
    {
        mint sum = 0;
        int len = 1;
        Tag tag;

        Info operator+(const Info &other) const
        {
            Info res;
            res.sum = sum + other.sum;
            res.len = len + other.len;
            res.tag =  {1, 0};

            return res;
        }

        bool lazy(const Tag &t)
        {
            sum = sum * t.mul + len * t.add;
            tag.mul *= t.mul;
            tag.add = tag.add * t.mul + t.add;

            return true;
        }

        bool has_lazy() const
        {
            return tag.mul != 1 || tag.add != 0;
        }

        Tag get_lazy() const
        {
            return tag;
        }

        void clear_lazy()
        {
            tag = {1, 0};
        }
    };

    auto init_arr = std::vector<Info>(n + 1, {0, 1, {}});
    init_arr[1].sum = 1;

    Seg_Tree<Info, Tag> tr(init_arr);
    for (auto &[x, y]: edges)
    {
        if (x >= y)
        {
            continue;
        }

        tr.modify(y, y, {1, tr.query(x, y).sum});
        if (y + 1 <= n)
        {
            tr.modify(y + 1, n, {2, 0});
        }
    }

    std::cout << tr.query(n, n).sum << "\n";
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
