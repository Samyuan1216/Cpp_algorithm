#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;

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

    std::array<int, 10> cnt{};
    for (auto &c: str)
    {
        ++cnt[c - '0'];
    }

    std::priority_queue<int, std::vector<int>, std::greater<>> heap;

    std::string ans(10, '0');
    for (int i = 0; i < 10; ++i)
    {
        while (cnt[9 - i]-- > 0)
        {
            heap.push(9 - i);
        }

        ans[i] = heap.top() + '0';
        heap.pop();
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
