#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace pbds = __gnu_pbds;

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

void solve()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::array<int, 3>> arr(m);
    for (auto &[c, a, b]: arr)
    {
        std::cin >> a >> b >> c;
        --a, --b;
    }

    ranges::sort(arr, std::greater());

    std::vector<int> father(n), enemy(n, -1);
    ranges::iota(father, 0);

    auto find = [&](this auto &&find, int i) -> int
    {
        father[i] = (father[i] == i? i: find(father[i]));
        return father[i];
    };

    int ans = 0;
    for (auto &[c, a, b]: arr)
    {
        if (find(a) == find(b))
        {
            ans = c;
            break;
        }

        if (enemy[a] == -1)
        {
            enemy[a] = b;
        }
        else
        {
            father[find(enemy[a])] = find(b);
        }

        if (enemy[b] == -1)
        {
            enemy[b] = a;
        }
        else
        {
            father[find(enemy[b])] = find(a);
        }
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
