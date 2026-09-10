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
    int n, l, r;
    std::cin >> n >> l >> r;

    std::queue<int> q;
    i64 sum = 0, ans = 0;

    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;

        while (!q.empty() && sum + x > r)
        {
            sum -= q.front();
            q.pop();
        }

        if (x > r)
        {
            continue;
        }

        sum += x;
        q.push(x);

        if (sum >= l)
        {
            ++ans;
            while (!q.empty())
            {
                q.pop();
            }

            sum = 0;
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
