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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    int block = std::sqrt(n), bnum = (n + block - 1) / block;
    std::vector<int> sorted = arr, bi(n), bl(bnum), br(bnum), lazy(bnum);

    for (int i = 0; i < n; ++i)
    {
        bi[i] = i / block;
    }

    for (int i = 0; i < bnum; ++i)
    {
        bl[i] = i * block;
        br[i] = std::min((i + 1) * block, n);

        ranges::sort(sorted.begin() + bl[i], sorted.begin() + br[i]);
    }

    auto modify = [&](int l, int r, int v) -> void
    {
        auto add = [&](int l, int r, int v) -> void
        {
            for (int i = l; i <= r; ++i)
            {
                arr[i] += v;
            }

            for (int i = bl[bi[l]]; i < br[bi[l]]; ++i)
            {
                sorted[i] = arr[i];
            }

            ranges::sort(sorted.begin() + bl[bi[l]], sorted.begin() + br[bi[l]]);
        };

        if (bi[l] == bi[r])
        {
            add(l, r, v);
        }
        else
        {
            add(l, br[bi[l]] - 1, v);
            add(bl[bi[r]], r, v);

            for (int i = bi[l] + 1; i <= bi[r] - 1; ++i)
            {
                lazy[i] += v;
            }
        }
    };

    auto query = [&](int l, int r, int v) -> int
    {
        auto q = [&](int l, int r, int v) -> int
        {
            v -= lazy[bi[l]];

            int ans = 0;
            for (int i = l; i <= r; ++i)
            {
                if (arr[i] >= v)
                {
                    ++ans;
                }
            }

            return ans;
        };

        int ans = 0;
        if (bi[l] == bi[r])
        {
            ans += q(l, r, v);
        }
        else
        {
            ans += q(l, br[bi[l]] - 1, v) + q(bl[bi[r]], r, v);
            for (int i = bi[l] + 1; i <= bi[r] - 1; ++i)
            {
                ans += br[i] - std::distance(sorted.begin(), ranges::lower_bound(sorted.begin() + bl[i], sorted.begin() + br[i], v - lazy[i]));
            }
        }

        return ans;
    };

    while (q--)
    {
        char op;
        int l, r, v;
        std::cin >> op >> l >> r >> v;
        --l, --r;

        if (op == 'M')
        {
            modify(l, r, v);
        }
        else
        {
            std::cout << query(l, r, v) << "\n";
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
