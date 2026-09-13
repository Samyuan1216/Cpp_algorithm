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

    std::vector<int> a1, a2;
    int mex = 0;

    for (auto &x: arr)
    {
        if (x == mex)
        {
            a1.push_back(x);
            ++mex;
        }
        else
        {
            a2.push_back(x);
        }
    }

    std::map<int, int> mp;
    for (int i = 0; i < std::ssize(a2); ++i)
    {
        std::vector<bool> visited(std::ssize(a2));
        visited[i] = true;

        int k = mex + a2[i], t = mex + 1, l = i - 1, r = 0;
        while (true)
        {
            while (r < std::ssize(a2) && (visited[r] || a2[r] < t))
            {
                ++r;
            }

            while (l >= 0 && (visited[l] || k - a2[l] < t))
            {
                --l;
            }

            if (r < std::ssize(a2) && a2[r] == t)
            {
                visited[r] = true;
                ++r, ++t;
            }
            else if (l >= 0 && k - a2[l] == t)
            {
                visited[l] = true;
                --l, ++t;
            }
            else
            {
                break;
            }
        }

        mp[k] = std::max(mp[k], t);
    }

    int q;
    std::cin >> q;

    int ans = 0;
    while (q--)
    {
        int k;
        std::cin >> k;

        ans ^= (mp.contains(k)? mp[k]: mex);
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
