// https://pintia.cn/problem-sets/994805046380707840/exam/problems/type/7?problemSetProblemId=1781658570803388420&page=1
#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = int64_t;

template<typename T>
using lim = std::numeric_limits<T>;

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

    auto strs = std::vector<std::string>(n);
    for (auto &str: strs)
    {
        std::cin >> str;
    }

    int k;
    std::cin >> k;
    std::cin.ignore();

    std::string str;
    std::getline(std::cin, str);

    int count = 0;
    const std::string placeholder = "*-*-*-*-*-*";
    const std::string censored = "<censored>";

    for (const auto& word : strs)
    {
        std::string::size_type pos = 0;
        while ((pos = str.find(word, pos)) != std::string::npos)
        {
            ++count;
            str.replace(pos, word.length(), placeholder);
            pos += placeholder.length();
        }
    }

    if (count >= k)
    {
        std::cout << count << "\nHe Xie Ni Quan Jia!\n";
        return;
    }

    std::string::size_type pos = 0;
    while ((pos = str.find(placeholder, pos)) != std::string::npos)
    {
        str.replace(pos, placeholder.length(), censored);
        pos += censored.length();
    }

    std::cout << str << "\n";
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
