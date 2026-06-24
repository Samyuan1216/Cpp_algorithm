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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n), suf(2 * q + 10);
    suf[0] = n;

    int offset = 0;
    while (q--)
    {
        int op, x;
        std::cin >> op >> x;

        if (op == 1)
        {
            ++suf[++arr[x - 1]];
            if (suf[1 + offset] == n)
            {
                ++offset;
            }
        }
        else
        {
            if (x + offset >= std::ssize(suf))
            {
                std::cout << 0 << "\n";
                continue;
            }

            std::cout << suf[x + offset] << "\n";
        }
    }
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
