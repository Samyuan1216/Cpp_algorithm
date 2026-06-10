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
    std::cin >> n;

    std::vector<int> arr(n);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    int t = arr[0];
    std::set<int, std::greater<>> s{1};

    do
    {
        s.insert(t);
        if (t & 1)
        {
            t += 1;
        }
        else
        {
            t >>= 1;
        }
    } while (t > 1);

    for (int i = 1; i < n; ++i)
    {
        t = arr[i];
        std::set<int, std::greater<>> tmp{1};

        do
        {
            if (s.contains(t))
            {
                tmp.insert(t);
            }

            if (t & 1)
            {
                t += 1;
            }
            else
            {
                t >>= 1;
            }
        } while (t > 1);

        s = tmp;
    }

    auto compute = [&](int x) -> int
    {
        int cnt = 0;
        for (int i = 0, t = arr[0]; i < n; ++i, t = arr[i])
        {
            while (t != x)
            {
                ++cnt;
                if (t & 1)
                {
                    t += 1;
                }
                else
                {
                    t >>= 1;
                }
            }
        }

        return cnt;
    };

    std::cout << std::min(compute(*s.begin()), (std::ssize(s) > 1? compute(*std::next(s.begin())): std::numeric_limits<int>::max())) << "\n";
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
