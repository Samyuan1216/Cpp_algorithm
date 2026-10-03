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

constexpr i64 MAXN = 1e5, MAXP = 3.2e8;
i64 prime[MAXP + 10], phi[MAXN + 10], rem[MAXN + 10];
bool vis[MAXP + 10];
i64 cnt = 0;

void sieve()
{
    vis[0] = vis[1] = true;
    for (i64 i = 2; i <= MAXP; ++i)
    {
        if (!vis[i])
        {
            prime[cnt++] = i;
        }

        for (i64 j = 0; j < cnt && i * prime[j] <= MAXP; ++j)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
}

void segment_phi(i64 l, i64 r)
{
    for (i64 i = l; i <= r; ++i)
    {
        rem[i - l] = phi[i - l] = i;
    }

    for (i64 i = 0; i < cnt; ++i)
    {
        for (i64 j = std::max(prime[i] * prime[i], (l + prime[i] - 1) / prime[i] * prime[i]); j <= r; j += prime[i])
        {
            phi[j - l] -= phi[j - l] / prime[i];
            while (rem[j - l] % prime[i] == 0)
            {
                rem[j - l] /= prime[i];
            }
        }
    }

    for (i64 i = 0; i < r - l + 1; ++i)
    {
        if (rem[i] > 1)
        {
            phi[i] -= phi[i] / rem[i];
        }
    }
}

void solve()
{
    i64 l, r;
    std::cin >> l >> r;

    {
        i64 L = l, R = std::min(r, l + MAXN);
        segment_phi(L, R);

        std::map<i64, i64> mp;
        for (i64 i = L; i <= R; ++i)
        {
            i64 tmp = phi[i - L];
            if (mp.contains(tmp))
            {
                std::cout << mp[tmp] << " " << i << "\n";
                return;
            }

            mp[tmp] = i;
        }
    }

    {
        i64 L = std::max(l, r - MAXN), R = r;
        segment_phi(L, R);

        std::map<i64, i64> mp;
        for (i64 i = R; i >= L; --i)
        {
            i64 tmp = phi[i - L];
            if (mp.contains(tmp))
            {
                std::cout << i << " " << mp[tmp] << "\n";
                return;
            }

            mp[tmp] = i;
        }
    }

    std::cout << "-1 -1\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    sieve();

    int t = 1;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
}
