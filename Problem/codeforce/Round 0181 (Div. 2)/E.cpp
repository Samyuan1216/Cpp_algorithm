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
    i64 k;
    std::cin >> k;

    std::vector<i64> arr(k);
    for (auto &x: arr)
    {
        std::cin >> x;
    }

    auto euler = [&](i64 n) -> std::array<std::vector<i64>, 3>
    {
        std::vector<bool> visited(n + 1);
        std::vector<i64> idx(n + 1);
        std::vector<i64> prime(n + 1);

        std::vector<i64> min_prime(n + 1);
        min_prime[1] = 1;

        int cnt = 0;
        for (int i = 2; i <= n; ++i)
        {
            if (!visited[i])
            {
                idx[i] = cnt;
                prime[cnt++] = i;
                min_prime[i] = i;
            }

            for (int j = 0; j < cnt; ++j)
            {
                if (i * prime[j] > n)
                {
                    break;
                }

                visited[i * prime[j]] = true;
                min_prime[i * prime[j]] = prime[j];

                if (i % prime[j] == 0)
                {
                    break;
                }
            }
        }

        prime.resize(cnt);
        return {prime, min_prime, idx};
    };

    i64 max = *ranges::max_element(arr);
    auto [prime, min_prime, idx] = euler(max);

    std::vector<i64> diff(max + 10);
    for (auto &x: arr)
    {
        ++diff[1];
        --diff[x + 1];
    }

    for (int i = 1; i <= max; ++i)
    {
        diff[i] += diff[i - 1];
    }

    std::vector<i64> cntp(std::ssize(prime));
    for (int i = 2; i <= max; ++i)
    {
        if (diff[i] == 0)
        {
            continue;
        }

        int tmp = i;
        while (tmp > 1)
        {
            i64 cnt = 0, tp = min_prime[tmp];
            while (tmp % tp == 0)
            {
                tmp /= tp;
                ++cnt;
            }

            cntp[idx[tp]] += diff[i] * cnt;
        }
    }

    auto check = [&](i64 mid) -> bool
    {
        for (int i = 0; i < std::ssize(prime); ++i)
        {
            i64 need = cntp[i], x = mid;
            while (need > 0 && x > 0)
            {
                x /= prime[i];
                need -= x;
            }

            if (need > 0)
            {
                return false;
            }
        }

        return true;
    };

    auto find = [&](auto l, auto r, bool find_first = true) -> std::optional<decltype(l)>
    {
        std::optional<decltype(l)> ans;
        while (l <= r)
        {
            auto mid = std::midpoint(l, r);
            if (check(mid))
            {
                ans = mid;
                find_first? (r = mid - 1): (l = mid + 1);
            }
            else
            {
                find_first? (l = mid + 1): (r = mid - 1);
            }
        }
    
        return ans;
    };

    std::cout << *find(1ll, i64(1e18)) << "\n";
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
