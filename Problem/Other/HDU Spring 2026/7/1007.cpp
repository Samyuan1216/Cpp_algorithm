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

    std::vector<i64> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    std::vector<std::array<i64, 3>> edges;
    for (int i = 0; i < n; ++i)
    {
        edges.push_back({2 * arr[i], i, i});
        if (i + 1 < n)
        {
            edges.push_back({arr[i] + arr[i + 1], i, i + 1});
        }
    }

    ranges::sort(edges);

    std::vector<int> father(n);
    std::iota(father.begin(), father.end(), 0);

    auto find = [&](auto &&self, int i) -> int
    {
        father[i] = (father[i] == i? i: self(self, father[i]));
        return father[i];
    };

    auto merge = [&](int a, int b)
    {
        father[find(find, a)] = find(find, b);
    };

    i64 ans = 0, cnt = 0;
    for (auto &[w, u, v]: edges)
    {
        int l = u, r = v;
        while (l >= 0 && r < n)
        {
            if (find(find, l) != find(find, r))
            {
                merge(l, r);

                ans += w;
                ++cnt;

                if (cnt == n - 1)
                {
                    std::cout << ans << "\n";
                    return;
                }
            }

            --l, ++r;
        }
    }

    std::cout << ans << "\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
