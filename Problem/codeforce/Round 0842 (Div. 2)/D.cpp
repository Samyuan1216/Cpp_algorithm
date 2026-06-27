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
        --x;
    }

    int cnt = 0;
    std::vector<int> index(n, -1);

    for (int i = 0; i < n; ++i)
    {
        if (index[i] >= 0)
        {
            continue;
        }

        for (int j = i; index[j] == -1; j = arr[j])
        {
            index[j] = cnt;
        }

        ++cnt;
    }

    int k = n - cnt + 1;
    for (int i = 1; i < n; ++i)
    {
        if (index[i] == index[i - 1])
        {
            k -= 2;
            break;
        }
    }

    std::cout << k << "\n";
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
