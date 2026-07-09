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
    }

    int i = 0, cnt = 0;
    while (i < n)
    {
        if (arr[i] > 1)
        {
            ++cnt;
        }
        else
        {
            --cnt;
        }

        ++i;

        if (cnt <= 0)
        {
            break;
        }
    }

    if (i == n)
    {
        std::cout << "NO\n";
        return;
    }

    if (cnt == -1 && arr[i] == 3)
    {
        ++i;
    }

    cnt = 0;
    while (i < n)
    {
        if (arr[i] > 2)
        {
            ++cnt;
        }
        else
        {
            --cnt;
        }

        ++i;

        if (cnt <= 0)
        {
            break;
        }
    }

    std::cout << (i < n? "YES\n": "NO\n");
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
