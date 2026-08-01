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
    int max = 0;

    for (auto &x: arr)
    {
        std::cin >> x;

        max = std::max(max, x);
    }

    std::vector<std::vector<int>> num(max + 1);
    for (int i = 0; i < n; ++i)
    {
        for (int d = 1; d * d <= arr[i]; ++d)
        {
            if (arr[i] % d == 0)
            {
                num[d].push_back(i);
                if (d * d != arr[i])
                {
                    num[arr[i] / d].push_back(i);
                }
            }
        }
    }

    std::vector<int> father(n), size(n, 1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        return (father[i] = (father[i] == i? i: find(father[i])));
    };

    auto merge = [&](int x, int y) -> bool
    {
        int fx = find(x), fy = find(y);
        if (fx == fy)
        {
            return false;
        }

        if (size[fx] < size[fy])
        {
            std::swap(fx, fy);
        }

        father[fy] = fx;
        size[fx] += size[fy];

        return true;
    };

    i64 ans = 0;
    for (int x = max, cnt = 0; x >= 1; --x)
    {
        if (std::ssize(num[x]) < 2)
        {
            continue;
        }

        for (int i = 1; i < std::ssize(num[x]); ++i)
        {
            if (merge(num[x][0], num[x][i]))
            {
                ans += x;
                if (++cnt == n - 1)
                {
                    std::cout << ans << "\n";
                    return;
                }
            }
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
