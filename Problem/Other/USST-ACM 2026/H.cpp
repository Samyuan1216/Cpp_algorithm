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
    int n, m;
    std::cin >> n >> m;

    std::multiset<i64> ms;
    std::multiset<i64>::iterator mid;

    auto insert = [&](i64 x) -> void
    {
        if (ms.empty())
        {
            ms.insert(x);
            mid = ms.begin();

            return;
        }

        int n = std::ssize(ms);
        ms.insert(x);

        if (x < *mid)
        {
            if (n & 1)
            {
                --mid;
            }
        }
        else
        {
            if (n % 2 == 0)
            {
                ++mid;
            }
        }
    };

    for (int i = 0; i < n; ++i)
    {
        i64 x;
        std::cin >> x;

        insert(x);
    }

    i64 s = 1, b = 0;
    auto print = [&]() -> void
    {
        double ans;
        int n = std::ssize(ms);

        if (n % 2 != 0)
        {
            ans = double(s * (*mid) + b);
        }
        else
        {
            auto next = std::next(mid);
            double r1 = double(s * (*mid) + b), r2 = double(s * (*next) + b);

            ans = (r1 + r2) / 2;
        }

        std::cout << std::format("{}\n", ans);
    };

    print();

    while (m--)
    {
        int op;
        i64 k;
        std::cin >> op >> k;

        if (op == 1)
        {
            insert(s * (k - b));
        }
        else if (op == 2)
        {
            b += k;
        }
        else
        {
            s = -s;
            b = 2 * k - b;
        }

        print();
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
