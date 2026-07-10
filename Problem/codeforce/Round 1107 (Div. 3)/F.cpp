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
    std::string str;
    std::cin >> n >> str;

    std::vector<int> pre(n);
    pre[0] = (str[0] == '1'? 1: 0);

    for (int i = 1; i < n; ++i)
    {
        pre[i] = pre[i - 1] + (str[i] == '1'? 1: 0);
    }

    std::vector<int> suf(n);
    suf[n - 1] = (str[n - 1] == '0'? 1: 0);

    for (int i = n - 2; i >= 0; --i)
    {
        suf[i] = suf[i + 1] + (str[i] == '0'? 1: 0);
    }

    for (int i = 0; i < n; ++i)
    {
        if ((str[i] == '0' && (pre[i] & 1)) || (str[i] == '1' && (suf[i] & 1)))
        {
            std::cout << "Alice\n";
            return;
        }
    }

    std::cout << "Bob\n";
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
