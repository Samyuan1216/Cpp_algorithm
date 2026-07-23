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
    int n, k;
    std::cin >> n >> k;

    std::vector<i64> c(n);
    i64 sum = 0;

    for (auto &x: c)
    {
        std::cin >> x;

        sum += x;
    }

    bool status[n] = {};
    for (int i = 0, x; i < k; ++i)
    {
        std::cin >> x;
        --x;

        status[x] = true;
    }

    i64 ans = 0, cap = 0;
    bool visited[n] = {};

    for (int i = 0; i < n; ++i)
    {
        ans += c[i] * c[(i + 1) % n];
        if (status[i])
        {
            i64 cur = sum - cap - c[i];
            int prev = (i - 1 + n) % n,  next = (i + 1) % n;

            if (!visited[prev])
            {
                cur -= c[prev];
            }

            if (!visited[next])
            {
                cur -= c[next];
            }

            ans += c[i] * cur;
            cap += c[i];
            visited[i] = true;
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
