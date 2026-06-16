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
    int n;
    std::cin >> n;

    struct Node
    {
        int l, r = -1;
        mutable int val = 0;

        bool operator<(const Node &other) const
        {
            return l < other.l;
        }
    };

    std::set<Node> cht{{0, n - 1, 1}};
    auto split = [&](int pos) -> std::set<Node>::iterator
    {
        auto iter = cht.lower_bound({pos});
        if (iter != cht.end() && iter->l == pos)
        {
            return iter;
        }

        --iter;

        int l = iter->l, r = iter->r, val = iter->val;
        cht.erase(iter);
        cht.insert({l, pos - 1, val});
        return cht.insert({pos, r, val}).first;
    };

    int sum = n;
    auto assign = [&](int l, int r, int val) -> void
    {
        auto itr = split(r + 1), itl = split(l);
        for (auto iter = itl; iter != itr; ++iter)
        {
            sum -= iter->val * (iter->r - iter->l + 1);
        }

        cht.erase(itl, itr);
        cht.insert({l, r, val});

        sum += val * (r - l + 1);
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        int l, r, k;
        std::cin >> l >> r >> k;
        --l, --r;

        assign(l, r, (k == 1? 0: 1));
        std::cout << sum << "\n";
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
