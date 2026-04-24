#include <bits/extc++.h>
namespace ranges = std::ranges;

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

    std::vector<int> arr(n);
    int max_len = 1;

    for (int i = 0, len = 1; i < n; ++i)
    {
        std::cin >> arr[i];

        if (i == 0)
        {
            continue;
        }

        if (arr[i] == arr[i - 1])
        {
            ++len;
        }
        else
        {
            len = 1;
        }

        max_len = std::max(max_len, len);
    }

    std::cout << (max_len < m? "YES\n": "NO\n");
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
