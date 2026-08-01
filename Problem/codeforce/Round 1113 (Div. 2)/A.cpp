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
    std::string str;
    std::cin >> str;

    int n = std::ssize(str);
    std::string ans;

    for (int i = 0; i < n; ++i)
    {
        if (str[i] != '0')
        {
            continue;
        }

        std::string alice = str.substr(0, i) + str.substr(i + 1), best;
        int m = std::ssize(alice);

        for (int j = 0; j < m; ++j)
        {
            if (alice[j] != '1')
            {
                continue;
            }

            std::string bob = alice.substr(0, j) + alice.substr(j + 1);
            if (best.empty() || bob < best)
            {
                best = bob;
            }
        }

        if (ans.empty() || best > ans)
        {
            ans = best;
        }
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
