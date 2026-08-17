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
    int n, m;
    std::cin >> n >> m;

    std::set<char> s;
    while (n--)
    {
        std::string str;
        std::cin >> str;

        s.insert(str[0]);
    }

    bool status = true;
    while (m--)
    {
        std::string str;
        std::cin >> str;

        for (auto &c: str)
        {
            if (!s.contains(c - 'A' + 'a'))
            {
                status = false;
            }
        }
    }

    std::cout << (status? "YES\n": "NO\n");
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
