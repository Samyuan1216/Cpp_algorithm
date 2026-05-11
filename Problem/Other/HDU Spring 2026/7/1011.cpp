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

    std::string s;
    std::cin >> s;

    int m = std::gcd(n, k);
    std::vector<std::array<int, 2>> cnt(m);

    for (int mod = 0; mod < m; ++mod)
    {
        for (int i = mod; i < n; i += m)
        {
            ++(s[i] == '0'? cnt[mod][0]: cnt[mod][1]);
        }
    }

    for (int l = 0, r = m - 1; l < r; ++l, --r)
    {
        if (cnt[l][1] % 2 != cnt[r][1] % 2)
        {
            std::cout << "NO\n";
            return;
        }
    }

    if (m & 1)
    {
        int num = m / 2;
        if ((cnt[num][0] + cnt[num][1]) % 2 == 0 && cnt[num][1] % 2 == 1)
        {
            std::cout << "NO\n";
            return;
        }
    }

    std::cout << "YES\n";
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
