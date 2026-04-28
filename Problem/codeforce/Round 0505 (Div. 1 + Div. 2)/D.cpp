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
    int n;
    std::cin >> n;

    std::vector<int> arr(n + 2);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> arr[i];
    }

    auto can = std::vector(n + 2, std::vector<bool>(n + 2));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            can[i][j] = (std::gcd(arr[i], arr[j]) > 1);
        }
    }

    auto left = std::vector(n + 2, std::vector<bool>(n + 2));
    auto right = std::vector(n + 2, std::vector<bool>(n + 2));

    for (int i = 1; i <= n; ++i)
    {
        left[i][i] = can[i][i + 1];
        right[i][i] = can[i][i - 1];
    }

    for (int len = 2; len <= n; ++len)
    {
        for (int l = 1, r = l + len - 1; r <= n; ++l, ++r)
        {
            for (int k = l; k <= r; ++k)
            {
                bool ls = (k == l || left[l][k - 1]), rs = (k == r || right[k + 1][r]);
                if (ls && rs)
                {
                    if (can[k][r + 1])
                    {
                        left[l][r] = true;
                    }

                    if (can[k][l - 1])
                    {
                        right[l][r] = true;
                    }
                }

                if (left[l][r] && right[l][r])
                {
                    break;
                }
            }
        }
    }

    bool status = false;
    for (int k = 1; k <= n; ++k)
    {
        bool ls = (k == 1 || left[1][k - 1]), rs = (k == n || right[k + 1][n]);
        if (ls && rs)
        {
            status = true;
            break;
        }
    }

    std::cout << (status? "Yes\n": "No\n");
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
