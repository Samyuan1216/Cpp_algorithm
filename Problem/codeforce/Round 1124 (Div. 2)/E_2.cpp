
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

    std::vector<int> pre(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] ^ arr[i - 1];
    }

    std::vector<int> cnt((1 << 18) + 10), lg(n + 1), lb(n + 1), rg(n + 1), rb(n + 1);
    int state = 0;

    auto check = [&](int m) -> bool
    {
        std::vector<int> s(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            s[i] = pre[i] & m;
        }

        return [&](this auto &&self, int l, int r) -> bool
        {
            if (l == r)
            {
                return false;
            }

            int mid = std::midpoint(l, r);
            if (self(l, mid) || self(mid + 1, r))
            {
                return true;
            }

            int gmax = -1, bmax = -1;
            for (int i = mid; i >= l; --i)
            {
                if ((arr[i] & m) == m)
                {
                    gmax = std::max(gmax, arr[i]);
                }
                else
                {
                    bmax = std::max(bmax, arr[i]);
                }

                lg[i] = gmax, lb[i] = bmax;
            }

            gmax = bmax = -1;
            for (int i = mid + 1; i <= r; ++i)
            {
                if ((arr[i] & m) == m)
                {
                    gmax = std::max(gmax, arr[i]);
                }
                else
                {
                    bmax = std::max(bmax, arr[i]);
                }

                rg[i] = gmax, rb[i] = bmax;
            }

            ++state;
            int idx = mid + 1;

            for (int i = mid; i >= l; --i)
            {
                while (idx <= r && rb[idx] < lg[i])
                {
                    cnt[s[idx + 1]] = state;
                    ++idx;
                }

                if (lg[i] > lb[i] && cnt[s[i] ^ m] == state)
                {
                    return true;
                }
            }

            ++state;
            idx = mid;

            for (int i = mid + 1; i <= r; ++i)
            {
                while (idx >= l && lb[idx] < rg[i])
                {
                    cnt[s[idx]] = state;
                    --idx;
                }

                if (rg[i] > rb[i] && cnt[s[i + 1] ^ m] == state)
                {
                    return true;
                }
            }

            return false;
        } (0, n - 1);
    };

    int ans = 0;
    for (int p = 17; p >= 0; --p)
    {
        int mask = ans | (1 << p);
        if (check(mask))
        {
            ans = mask;
        }
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
