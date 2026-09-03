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
    static auto p = []() -> std::map<i64, std::array<i64, 2>>
    {
        std::array<i64, 61> arr{};
        arr[0] = 1;

        for (int i = 1; i <= 60; ++i)
        {
            arr[i] = arr[i - 1] * 2;
        }

        std::map<i64, std::array<i64, 2>> mp;
        for (int i = 0; i < 60; ++i)
        {
            for (int j = i + 1; j <= 60; ++j)
            {
                mp[arr[j] - arr[i]] = {arr[i], arr[j]};
            }
        }

        return mp;
    } ();

    int n;
    std::cin >> n;

    std::vector<i64> arr(n);
    i64 aim = 0;

    for (auto &x: arr)
    {
        std::cin >> x;

        aim += x;
    }

    if (aim % n != 0)
    {
        std::cout << "No\n";
        return;
    }

    aim /= n;

    std::map<i64, int> in, out;
    for (auto &x: arr)
    {
        if (x == aim)
        {
            continue;
        }

        if (!p.contains(std::abs(x - aim)))
        {
            std::cout << "No\n";
            return;
        }

        if (x > aim)
        {
            auto tp = p[x - aim];
            ++in[std::min(tp[0], tp[1])];
            ++out[std::max(tp[0], tp[1])];
        }
        else if (x < aim)
        {
            auto tp = p[aim - x];
            ++in[std::max(tp[0], tp[1])];
            ++out[std::min(tp[0], tp[1])];
        }
    }

    if (in != out)
    {
        std::cout << "No\n";
        return;
    }

    std::cout << "Yes\n";
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
