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

    std::vector<std::priority_queue<int, std::vector<int>, std::greater<>>> hs(n);
    for (int i = 0, l, r; i < n; ++i)
    {
        std::cin >> l >> r;
        --l, --r;

        hs[l].push(r);
    }

    for (int i = 0; i < n; ++i)
    {
        if (hs[i].empty())
        {
            std::cout << 0 << "\n";
            return;
        }

        int r = hs[i].top();
        hs[i].pop();

        if (!hs[i].empty() && r == hs[i].top())
        {
            std::cout << 0 << "\n";
            return;
        }

        if (!hs[i].empty())
        {
            if (std::ssize(hs[r + 1]) < std::ssize(hs[i]))
            {
                std::swap(hs[r + 1], hs[i]);
            }

            while (!hs[i].empty())
            {
                hs[r + 1].push(hs[i].top());
                hs[i].pop();
            }
        }
    }

    std::cout << 1 << "\n";
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
