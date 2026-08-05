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

    std::vector<std::array<int, 2>> arr(m);
    for (auto &[a, b]: arr)
    {
        std::cin >> a >> b;
    }

    auto check = [&](int x)
    {
        for (auto &[a, b]: arr)
        {
            if (a != x && b != x)
            {
                return false;
            }
        }

        return true;
    };

    if (bool s1 = check(arr[0][0]), s2 = check(arr[0][1]); s1 || s2)
    {
        if (s1 && s2)
        {
            std::cout << 2 * n - 3 << "\n";
        }
        else
        {
            std::cout << n - 1 << "\n";
        }

        return;
    }

    std::set<std::array<int, 2>> ans;
    auto compute = [&](int x) -> void
    {
        constexpr int MAXN = 2e5 + 10;
        std::bitset<MAXN> num, tmp;

        bool status = true;
        for (auto &[a, b]: arr)
        {
            if (a == x || b == x)
            {
                continue;
            }

            if (num.none() && status)
            {
                num[a] = num[b] = 1;
                status = false;
            }
            else
            {
                tmp.reset();
                tmp[a] = tmp[b] = 1;
                num &= tmp;
            }
        }

        for (int pos = num._Find_first(); pos < std::ssize(num); pos = num._Find_next(pos))
        {
            ans.insert({std::min(x, pos), std::max(x, pos)});
        }
    };

    compute(arr[0][0]), compute(arr[0][1]);
    std::cout << std::ssize(ans) << "\n";
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
