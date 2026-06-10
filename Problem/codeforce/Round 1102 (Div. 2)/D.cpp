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
    std::cin >> n >> k;

    std::string s, z;
    std::cin >> s >> z;

    using u64 = unsigned long long;
    u64 cnta = 0, cntb = 0, cntc = 0;

    for (int i = 0; i < n; ++i)
    {
        if (s[i] == '1')
        {
            ++cnta;
        }

        if (z[i] == '1')
        {
            ++cntb;
        }

        if (s[i] != z[i])
        {
            ++cntc;
        }
    }

    u64 a = cnta * (n - cnta), b = cntb * (n - cntb), c = cntc * (n - cntc), cnt = 0;
    bool status = true;

    while (k--)
    {
        if (status)
        {
            cnt = 2 * cnt + 1;
        }
        else
        {
            cnt = 2 * cnt - 1;
        }

        status = !status;
    }

    u64 ans = 0;
    if (status)
    {
        ans = (cnt + 1) * a + (cnt + 1) * b + cnt * c;
    }
    else
    {
        ans = cnt * (a + b + c);
    }

    std::cout << ans << "\n";
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
