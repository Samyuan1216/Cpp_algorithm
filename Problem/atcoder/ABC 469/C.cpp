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

    std::vector<int> idx;
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == 'x')
        {
            idx.push_back(i);
        }
    }

    int cnt = 0;
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == 'o')
        {
            ++cnt;
        }

        if (cnt == 0)
        {
            std::cout << i + 1 << "\n";
        }
        else
        {
            if (std::ssize(idx) >= i + 1)
            {
                std::cout << idx[i] + 1 << "\n";
            }
            else
            {
                std::cout << n << "\n";
            }
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
