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

    std::vector<int> pre(n * 10, -1);
    std::queue<int> q;

    auto flat_index = [](auto ...D)
    {
        return [=](auto ...i)
        {
            int idx = 0;
            ((idx = idx * D + i), ...);
    
            return idx;
        };
    };
    auto idx = flat_index(n, 10);

    int status = -1;
    for (int i = 1, r; i <= 9; ++i)
    {
        r = i % n;
        if (pre[idx(r, i)] == -1)
        {
            pre[idx(r, i)] = -2;
            q.push(idx(r, i));

            if (r == 0)
            {
                status = idx(r, i);
                break;
            }
        }
    }

    while (!q.empty() && status == -1)
    {
        int cur = q.front();
        q.pop();

        int r = cur / 10, d = cur % 10;
        for (int ni = d, nr; ni <= 9; ++ni)
        {
            nr = (r * 10 + ni) % n;
            if (pre[idx(nr, ni)] == -1)
            {
                pre[idx(nr, ni)] = cur;
                q.push(idx(nr, ni));

                if (nr == 0)
                {
                    status = idx(nr, ni);
                    break;
                }
            }
        }
    }

    if (status == -1)
    {
        std::cout << -1 << "\n";
        return;
    }

    std::string ans;
    while (status != -2)
    {
        ans += std::to_string(status % 10);
        status = pre[status];
    }

    ranges::reverse(ans);
    std::cout << ans << "\n";
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
