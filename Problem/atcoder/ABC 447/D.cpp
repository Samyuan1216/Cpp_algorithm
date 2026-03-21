#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

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
    std::string str;
    std::cin >> str;

    int a_cnt = 0, b_cnt = 0, c_cnt = 0;
    for (auto &c: str)
    {
        if (c == 'A')
        {
            ++a_cnt;
        }
        else if (b_cnt < a_cnt && c == 'B')
        {
            ++b_cnt;
        }
        else if (c_cnt < b_cnt && c == 'C')
        {
            ++c_cnt;
        }
    }

    std::cout << c_cnt << "\n";
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
