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

    int s1 = 0, s2 = 0;
    for (int i = 0; i < 2 * n; ++i)
    {
        if (str[i] == '1')
        {
            if (str[(i + 1) % (2 * n)] == '0')
            {
                (i & 1? ++s1: ++s2);
            }
            else
            {
                (i & 1? ++s2: ++s1);
            }
        }
    }

    std::cout << s2 << " " << s1 << "\n";
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
