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

void solve()
{
    i64 n, m, seed, vmax;
    std::cin >> n >> m >> seed >> vmax;

    auto rnd = [&]() -> i64
    {
        i64 ret = seed;
        seed = (seed * 7 + 13) % 1000000007;

        return ret;
    };

    struct Node
    {
        int l, r = -1;
        mutable i64 val = 0;

        bool operator<(const Node &other) const
        {
            return l < other.l;
        }
    };

    std::set<Node> cht;
    for (int i = 1; i <= n; ++i)
    {
        cht.insert({i, i, (rnd() % vmax) + 1});
    }

    auto split = [&](int pos) -> std::set<Node>::iterator
    {
        auto iter = cht.lower_bound({pos});
        if (iter != cht.end() && iter->l == pos)
        {
            return iter;
        }

        --iter;

        int l = iter->l, r = iter->r;
        i64 val = iter->val;

        cht.erase(iter);
        cht.insert({l, pos - 1, val});
        return cht.insert({pos, r, val}).first;
    };

    auto assign = [&](int l, int r, i64 val) -> void
    {
        auto itr = split(r + 1), itl = split(l);
        cht.erase(itl, itr);
        cht.insert({l, r, val});
    };

    auto add = [&](int l, int r, i64 val) -> void
    {
        auto itr = split(r + 1), itl = split(l);
        for (auto iter = itl; iter != itr; ++iter)
        {
            iter->val += val;
        }
    };

    auto index = [&](int l, int r, int x) -> i64
    {
        std::vector<std::pair<i64, int>> sorted;

        auto itr = split(r + 1), itl = split(l);
        for (auto iter = itl; iter != itr; ++iter)
        {
            sorted.push_back({iter->val, iter->r - iter->l + 1});
        }

        ranges::sort(sorted);

        for (auto &[val, cnt]: sorted)
        {
            x -= cnt;
            if (x <= 0)
            {
                return val;
            }
        }

        return -1;
    };

    auto power = [&](i64 x, i64 n, i64 mod)
    {
        i64 ans = 1;
        x %= mod;

        while (n > 0)
        {
            if (n & 1)
            {
                ans = (ans * x) % mod;
            }
    
            x = (x * x) % mod;
            n >>= 1;
        }
    
        return ans;
    };

    auto psum = [&](int l, int r, i64 x, i64 y) -> i64
    {
        auto itr = split(r + 1), itl = split(l);

        i64 ans = 0;
        for (auto iter = itl; iter != itr; ++iter)
        {
            ans = (ans + ((iter->r - iter->l + 1 + y) % y) * power(iter->val, x, y) % y) % y;
        }

        return ans;
    };

    while (m--)
    {
        int op = (rnd() % 4) + 1, l = (rnd() % n) + 1, r = (rnd() % n) + 1;
        if (l > r)
        {
            std::swap(l, r);
        }

        i64 x, y;
        if (op == 3)
        {
            x = (rnd() % (r - l + 1)) + 1;
        }
        else
        {
            x = (rnd() % vmax) + 1;
        }

        if (op == 4)
        {
            y = (rnd() % vmax) + 1;
        }

        if (op == 1)
        {
            add(l, r, x);
        }
        else if (op == 2)
        {
            assign(l, r, x);
        }
        else if (op == 3)
        {
            std::cout << index(l, r, x) << "\n";
        }
        else
        {
            std::cout << psum(l, r, x, y) << "\n";
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
