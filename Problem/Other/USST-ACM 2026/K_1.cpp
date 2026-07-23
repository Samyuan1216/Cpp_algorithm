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

    std::vector<int> pos;
    for (int i = 0; i < n; ++i)
    {
        if (str[i] == '1')
        {
            pos.push_back(i);
        }
    }

    int m = std::ssize(pos);
    auto check = [&](int mid) -> int
    {
        int ans = 0;
        for (int i = 0, u = 0, us = 0, uss = 0; i < n; ++i)
        {
            char c = str[i];
            if (c == '1')
            {
                if (mid > 0 && i <= pos[mid - 1])
                {
                    c = 'u';
                }
                else
                {
                    c = 't';
                }
            }

            if (c == 'u')
            {
                ++u;
            }
            else if (c == 's')
            {
                if (us > 0)
                {
                    --us;
                    ++uss;
                }
                else if (u > 0)
                {
                    --u;
                    ++us;
                }
            }
            else if (uss > 0)
            {
                --uss;
                ++ans;
            }
        }

        return ans;
    };

    auto find = [&](auto l, auto r, bool find_min = true) -> decltype(l)
    {
        while (r - l >= 3)
        {
            auto m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            if (find_min? check(m1) < check(m2): check(m1) > check(m2))
            {
                r = m2;
            }
            else
            {
                l = m1;
            }
        }
    
        auto ans = l;
        auto val = check(l);
    
        for (auto i = l + 1; i <= r; ++i)
        {
            auto cur = check(i);
            if (find_min? cur < val: cur > val)
            {
                ans = i;
                val = cur;
            }
        }
    
        return ans;
    };

    std::cout << check(find(0, m, false)) << "\n";
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
