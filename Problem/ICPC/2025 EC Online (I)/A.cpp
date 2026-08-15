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
    int s;
    std::cin >> s;

    std::vector<std::tuple<std::string, int, int, std::string>> query(s);
    for (auto &[team, p, time, res]: query)
    {
        std::string problem, t;
        std::cin >> team >> problem >> t >> res;

        p = problem[0] - 'A', time = std::stoi(t);
    }

    ranges::sort(query, {}, [&](const auto &a) { return std::get<2>(a); });

    std::set<std::string> names;
    std::map<std::string, std::array<int, 2>> ac, un;
    std::map<std::string, std::array<int, 26>> rej;
    std::map<std::string, std::array<bool, 26>> visited;

    for (auto &[team, problem, time, result]: query)
    {
        names.insert(team);

        if (result == "Rejected")
        {
            if (visited[team][problem])
            {
                continue;
            }

            rej[team][problem] += 20;
        }
        else if (result == "Accepted")
        {
            if (visited[team][problem])
            {
                continue;
            }

            visited[team][problem] = true;

            ++ac[team][0];
            ac[team][1] += time + rej[team][problem];
        }
        else
        {
            if (visited[team][problem])
            {
                continue;
            }

            visited[team][problem] = true;

            ++un[team][0];
            un[team][1] += time + rej[team][problem];
        }
    }

    std::array<int, 2> max{};
    for (auto &[key, p]: ac)
    {
        if (max[0] < p[0])
        {
            max = p;
        }
        else if (max[0] == p[0] && max[1] > p[1])
        {
            max = p;
        }
    }

    std::vector<std::string> ans;
    for (auto &name: names)
    {
        std::array<int, 2> cur{};
        cur[0] = ac[name][0] + un[name][0];
        cur[1] = ac[name][1] + un[name][1];

        if (cur[0] > max[0] || (cur[0] == max[0] && cur[1] <= max[1]))
        {
            ans.push_back(name);
        }
    }

    ranges::sort(ans);

    for (int i = 0; i < std::ssize(ans); ++i)
    {
        std::cout << ans[i] << " \n"[i == std::ssize(ans) - 1];
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
