#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

using i64 = int64_t;
using i128 = __int128;
using u64 = uint64_t;
using u128 = unsigned __int128;
using f64 = double;
using f128 = long double;

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
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto prime_base = [](int x)
    {
        std::set<int> s;
        for (int i = 2; i * i <= x; ++i)
        {
            while (x % i == 0)
            {
                s.insert(i);
                x /= i;
            }
        }

        if (x > 1)
        {
            s.insert(x);
        }

        if (s.size() > 1)
        {
            return -1;
        }

        if (s.size() == 0)
        {
            return 1;
        }

        return *s.begin();
    };

    std::vector<int> b(n);
    for (int i = 0; i < n; ++i)
    {
        b[i] = prime_base(arr[i]);
    }

    if (ranges::is_sorted(arr) || (*ranges::min_element(b) != -1 && ranges::is_sorted(b)))
    {
        std::cout << "Bob\n";
    }
    else
    {
        std::cout << "Alice\n";
    }
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
