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
    std::string str;
    std::cin >> str;

    std::array<int, 26> count{};
    for (auto &c: str)
    {
        ++count[c - 'a'];
    }

    std::priority_queue<std::array<int, 2>> heap;
    for (int i = 0; i < 26; ++i)
    {
        heap.push({count[i], i});
    }

    auto max = heap.top();
    heap.pop();

    std::vector<std::string> ans(max[0]);
    for (auto &s: ans)
    {
        s += max[1] + 'a';
    }

    int idx = 0;
    while (!heap.empty() && heap.top()[0] > 0)
    {
        auto res = heap.top();
        heap.pop();

        while (res[0]--)
        {
            ans[idx] += res[1] + 'a';
            idx = (idx + 1) % max[0];
        }
    }

    for (int cnt = 0; auto &s: ans)
    {
        if (std::ssize(s) == 1)
        {
            ++cnt;
        }

        if (cnt > 1)
        {
            std::cout << "No\n";
            return;
        }
    }

    std::cout << "Yes\n";
    for (auto &s: ans)
    {
        std::cout << s;
    }
    std::cout << "\n";
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
