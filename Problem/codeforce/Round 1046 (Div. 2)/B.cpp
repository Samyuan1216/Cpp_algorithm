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
    std::string str;
    std::cin >> n >> k >> str;

    for (int i = 0, cnt = 0; i < n; ++i)
    {
        if (str[i] == '0')
        {
            cnt = 0;
        }
        else
        {
            ++cnt;
        }

        if (cnt == k)
        {
            std::cout << "NO\n";
            return;
        }
    }

    int num = 1;
    std::vector<int> ans(n);

    for (int i = 0; i < n; ++i)
    {
        if (str[i] == '1')
        {
            ans[i] = num++;
        }
    }

    for (int i = 0; i < n; ++i)
    {
        if (str[i] == '0')
        {
            ans[i] = num++;
        }
    }

    std::cout << "YES\n";
    for (int i = 0; i < n; ++i)
    {
        std::cout << ans[i] << " \n"[i == n - 1];
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
