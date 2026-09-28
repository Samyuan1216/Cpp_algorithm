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

    ranges::sort(arr);

    {
        int num = 0;
        for (int i = 0; i < n; ++i)
        {
            if (arr[i] >= 0)
            {
                break;
            }

            ++num;
        }

        if (num >= 3)
        {
            std::cout << "NO\n";
            return;
        }
    }

    {
        int num = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            if (arr[i] <= 0)
            {
                break;
            }

            ++num;
        }

        if (num >= 3)
        {
            std::cout << "NO\n";
            return;
        }
    }

    std::vector<int> a;
    std::set<int> s;

    for (int i = 0; i < n; ++i)
    {
        if (arr[i] >= 0)
        {
            break;
        }

        a.push_back(arr[i]);
        s.insert(arr[i]);
    }

    for (int i = n - 1; i >= 0; --i)
    {
        if (arr[i] <= 0)
        {
            break;
        }

        a.push_back(arr[i]);
        s.insert(arr[i]);
    }

    if (std::ssize(a) < std::ssize(arr))
    {
        a.push_back(0);
        s.insert(0);

        if (std::ssize(a) <= std::ssize(arr) - 2)
        {
            a.push_back(0);
        }
    }

    for (int i = 0; i < std::ssize(a); ++i)
    {
        for (int j = i + 1; j < std::ssize(a); ++j)
        {
            for (int k = j + 1; k < std::ssize(a); ++k)
            {
                if (!s.contains(a[i] + a[j] + a[k]))
                {
                    std::cout << "NO\n";
                    return;
                }
            }
        }
    }

    std::cout << "YES\n";
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
