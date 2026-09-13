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

template <int MOD>
struct ModInt
{
    int val;

    ModInt(i64 v = 0)
    {
        v %= MOD;
        if (v < 0)
        {
            v += MOD;
        }
        val = static_cast<int>(v);
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
        return pow(MOD - 2);
    }

    ModInt& operator+=(const ModInt& other)
    {
        val += other.val;
        if (val >= MOD)
        {
            val -= MOD;
        }
        return *this;
    }

    ModInt& operator-=(const ModInt& other)
    {
        val -= other.val;
        if (val < 0)
        {
            val += MOD;
        }
        return *this;
    }

    ModInt& operator*=(const ModInt& other)
    {
        val = static_cast<int>(1LL * val * other.val % MOD);
        return *this;
    }

    ModInt& operator/=(const ModInt& other)
    {
        return *this *= other.inv();
    }

    ModInt operator-() const
    {
        return ModInt(val == 0 ? 0 : MOD - val);
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
    constexpr int mod = 998244353;
    using mint = ModInt<mod>;

    int n, q;
    std::cin >> n >> q;

    std::vector<std::array<int, 3>> tree(1 << (n + 1));
    [&](this auto &&self, int i, int l, int r) -> void
    {
        tree[i] = {l, r, -1};
        if (l == r)
        {
            return;
        }

        int mid = std::midpoint(l, r);
        self(2 * i, l, mid);
        self(2 * i + 1, mid + 1, r);
    } (1, 1, 1 << n);

    std::vector<std::array<int, 2>> query(q);
    bool status = true;

    for (auto &[u, x]: query)
    {
        std::cin >> u >> x;

        if (tree[u][2] != -1 && tree[u][2] != x)
        {
            status = false;
        }

        tree[u][2] = x;
    }

    if (!status)
    {
        std::cout << 0 << "\n";
        return;
    }

    ranges::sort(query, {}, [](const auto &a) { return std::pair{a[1], -a[0]}; });
    {
        auto [l, r] = ranges::unique(query);
        query.erase(l, r);
    }

    [&](this auto &&self, int i) -> int
    {
        if (tree[i][0] == tree[i][1])
        {
            return tree[i][2];
        }

        int max = std::max(self(2 * i), self(2 * i + 1));
        if (tree[i][2] >= 0 && tree[i][2] < max)
        {
            status = false;
            return -1;
        }

        return std::max(max, tree[i][2]);
    } (1);

    if (!status)
    {
        std::cout << 0 << "\n";
        return;
    }

    auto fac = [&](int n) -> std::vector<mint>
    {
        std::vector<mint> fac(n + 1);
    
        fac[0] = fac[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            fac[i] = i * fac[i - 1];
        }
    
        return fac;
    } ((1 << n) + 1);

    auto A = [&](int a, int b) -> mint
    {
        if (a < 0 || b < 0 || b > a)
        {
            return 0;
        }

        return fac[a] / fac[a - b];
    };

    struct Tag
    {
        int val = 0;

        void apply(const Tag &t)
        {
            val = t.val;
        }
    };

    struct Info
    {
        int sum = 0, len = 1;

        Info operator+(const Info &other) const
        {
            return {sum + other.sum, len + other.len};
        }

        bool apply(const Tag &t)
        {
            sum = t.val * len;
            return true;
        }
    };

    std::vector<Info> init((1 << n) + 1);
    for (int i = 1; i <= (1 << n); ++i)
    {
        init[i].sum = 1;
    }

    Seg_Tree<Info, Tag> tr1((1 << n) + 1), tr2(init);
    std::vector<int> owner((1 << n) + 1, -1);

    mint ans = 1;
    for (auto &[u, x]: query)
    {
        int l = tree[u][0], r = tree[u][1];
        bool fresh = (owner[x] == -1? 1: 0);

        if (!fresh && (tree[owner[x]][0] < l || tree[owner[x]][1] > r))
        {
            std::cout << 0 << "\n";
            return;
        }

        int empty = r - l + 1 - tr1.query(l, r).sum;
        int len = empty - (fresh? 1: 0);
        int cnt = tr2.query(1, x - 1).sum;

        if (len < 0 || cnt < len)
        {
            std::cout << 0 << "\n";
            return;
        }

        ans *= A(cnt, len);
        if (fresh)
        {
            ans *= empty;
            owner[x] = u;
        }

        tr1.modify(l, r, {1});
        if (len > 0)
        {
            auto k = tr2.find_kth(len, [](const Info &info)
            {
                return info.sum;
            });

            tr2.modify(1, *k, {0});
        }

        if (fresh)
        {
            tr2.modify(x, x, {0});
        }
    }

    {
        int len = tree[1][1] - tree[1][0] + 1 - tr1.query(tree[1][0], tree[1][1]).sum;
        int cnt = tr2.query(0, 1 << n).sum;

        ans *= A(cnt, len);
    }

    std::cout << ans << "\n";
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
