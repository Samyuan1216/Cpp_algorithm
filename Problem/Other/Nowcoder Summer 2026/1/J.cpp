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
    struct Q
    {
        int rank, suit; // 点数，花色

        auto operator<=>(const Q &other) const = default;
    };

    auto parse = [&](const std::string &str) -> Q
    {
        return Q{
            int(std::string("23456789TJQKA").find(str[0])),
            int(std::string("SHDC").find(str[1]))
        };
    };

    auto eval = [&](std::vector<Q> arr) -> std::vector<int>
    {
        std::vector<int> cnt(15);
        for (auto &[r, s]: arr)
        {
            ++cnt[r];
        }

        ranges::sort(arr);

        bool is_flush = true, is_str = false;
        for (int i = 1; i < 5; ++i)
        {
            is_flush &= (arr[i].suit == arr[0].suit);
        }

        is_str = (*ranges::max_element(cnt) == 1) && (arr[0].rank + 4 == arr[4].rank);

        std::vector<int> b(6);
        for (int i = 1; i < 6; ++i)
        {
            b[i] = arr[i - 1].rank;
        }

        ranges::sort(b.begin() + 1, b.end(), std::greater(), [&](int x) { return std::pair{cnt[x], x}; });

        if (b == std::vector{0, 12, 3, 2, 1, 0})
        {
            is_str = true;
            b[1] = 0;
        }

        if (is_flush && is_str) return b[0] = 9, b; // 同花顺
        if (cnt[b[1]] == 4) return b[0] = 8, b; // 四条
        if (cnt[b[1]] == 3 && cnt[b[4]] == 2) return b[0] = 7, b; // 葫芦
        if (is_flush) return b[0] = 6, b; // 同花
        if (is_str) return b[0] = 5, b; // 顺子
        if (cnt[b[1]] == 3) return b[0] = 4, b; // 三条
        if (cnt[b[1]] == 2 && cnt[b[3]] == 2) return b[0] = 3, b; // 两对
        if (cnt[b[1]] == 2) return b[0] = 2, b; // 一对
        return b; // 高牌
    };

    std::vector<bool> visited(52);

    std::vector<Q> a(4);
    for (auto &x: a)
    {
        std::string str;
        std::cin >> str;

        x = parse(str);
        visited[x.suit * 13 + x.rank] = true;
    }

    std::vector<Q> b(4);
    for (auto &x: b)
    {
        std::string str;
        std::cin >> str;

        x = parse(str);
        visited[x.suit * 13 + x.rank] = true;
    }

    std::vector<Q> rest;
    for (int s = 0; s < 4; ++s)
    {
        for (int r = 0; r < 13; ++r)
        {
            if (!visited[s * 13 + r])
            {
                rest.push_back({r, s});
            }
        }
    }

    int k = std::ssize(rest);
    std::vector<std::vector<int>> s1(k), s2(k);

    for (int i = 0; i < k; ++i)
    {
        auto ta = a;
        ta.push_back(rest[i]);
        s1[i] = eval(ta);

        auto tb = b;
        tb.push_back(rest[i]);
        s2[i] = eval(tb);
    }

    int c1 = 0, c2 = -1;
    for (int i = 1; i < k; ++i)
    {
        if (s1[i] > s1[c1])
        {
            c2 = c1;
            c1 = i;
        }
        else if (c2 == -1 || s1[i] > s1[c2])
        {
            c2 = i;
        }
    }

    bool win1 = true, win2 = false;
    for (int x = 0; x < k; ++x)
    {
        auto &my_ans = (x == c1? s1[c2]: s1[c1]);
        if (my_ans > s2[x]) {}
        else if (s2[x] > my_ans)
        {
            win1 = false, win2 = true;
        }
        else
        {
            win1 = false;
        }
    }

    if (win1)
    {
        std::cout << "WoYaoYanPai\n";
    }
    else if (win2)
    {
        std::cout << "GeiWoCaPiXie\n";
    }
    else
    {
        std::cout << "PaiMeiYouWenTi\n";
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
