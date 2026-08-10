// https://www.spoj.com/problems/GIVEAWAY/

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

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    int block = std::sqrt(n), bnum = (n + block - 1) / block;
    std::vector<int> sorted = arr, bi(n), bl(bnum), br(bnum);

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

    auto modify = [&](int i, int v)
    {
        int l = bl[bi[i]], r = br[bi[i]];
        arr[i] = v;

        for (int j = l; j < r; ++j)
        {
            sorted[j] = arr[j];
        }

        ranges::sort(sorted.begin() + l, sorted.begin() + r);
    };

    auto query = [&](int l, int r, int v) -> int
    {
        int ans = 0;
        if (bi[l] == bi[r])
        {
            for (int i = l; i <= r; ++i)
            {
                if (arr[i] >= v)
                {
                    ++ans;
                }
            }
        }
        else
        {
            for (int i = l; i < br[bi[l]]; ++i)
            {
                if (arr[i] >= v)
                {
                    ++ans;
                }
            }

            for (int i = br[bi[r]]; i < r; ++i)
            {
                if (arr[i] >= v)
                {
                    ++ans;
                }
            }

            for (int i = bi[l] + 1; i <= bi[r] - 1; ++i)
            {
                ans += br[i] - std::distance(sorted.begin(), ranges::lower_bound(sorted.begin() + bl[i], sorted.begin() + br[i], v));
            }
        }

        return ans;
    };

    int q;
    std::cin >> q;

    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 0)
        {
            int a, b, c;
            std::cin >> a >> b >> c;
            --a, --b;

            std::cout << query(a, b, c) << "\n";
        }
        else
        {
            int a, b;
            std::cin >> a >> b;
            --a;

            modify(a, b);
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
