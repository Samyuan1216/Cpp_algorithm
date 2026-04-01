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
    int n, q;
    std::cin >> n >> q;

    auto arr = std::vector<int>(n + 1), pre = std::vector<int>(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];

        pre[i] = pre[i - 1] + arr[i];
    }

    while (q--)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x;
            std::cin >> x;

            pre[x] -= arr[x] - arr[x + 1];
            std::swap(arr[x], arr[x + 1]);
        }
        else
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << pre[r] - pre[l - 1] << "\n";
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
