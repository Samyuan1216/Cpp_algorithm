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

    std::deque<char> dq;
    int cnt0 = 0, cnt1 = 0;

    for (int i = 0; i < n; ++i)
    {
        if (dq.empty() || dq.back() != str[i])
        {
            dq.push_back(str[i]);
        }
        else
        {
            if (str[i] == '0')
            {
                ++cnt0;
            }
            else
            {
                ++cnt1;
            }
        }
    }

    if (cnt0 == 0 && cnt1 == 0)
    {
        std::cout << 0 << "\n";
        return;
    }

    int ans = 1e9;
    auto compute = [&](char c) -> bool
    {
        bool status = (c == '1'? true: false);

        int cnt = 0, tc1 = cnt1, tc0 = cnt0;
        auto tdq = dq;

        while (true)
        {
            if (status)
            {
                if (tc1 > 0)
                {
                    --tc1;
                    ++cnt;
                }
                else if (tdq.front() == '1')
                {
                    tdq.pop_front();
                    ++cnt;
                }
                else if (tdq.back() == '1')
                {
                    tdq.pop_back();
                    ++cnt;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (tc0 > 0)
                {
                    --tc0;
                    ++cnt;
                }
                else if (tdq.front() == '0')
                {
                    tdq.pop_front();
                    ++cnt;
                }
                else if (tdq.back() == '0')
                {
                    tdq.pop_back();
                    ++cnt;
                }
                else
                {
                    return false;
                }
            }

            if (tc0 == 0 && tc1 == 0)
            {
                ans = std::min(ans, cnt);
                return true;
            }

            status = !status;
        }
    };

    if (bool s1 = compute('1'), s2 = compute('0'); !s1 && !s2)
    {
        std::cout << -1 << "\n";
    }
    else
    {
        std::cout << ans << "\n";
    }
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
