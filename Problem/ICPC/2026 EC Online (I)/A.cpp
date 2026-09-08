#include <bits/extc++.h>
namespace ranges = std::ranges;

using i64 = long long;

void solve()
{
    int n;
    std::cin >> n;

    std::map<int, std::vector<std::pair<char, int>>> adj;
    std::map<int, int> idx;
    std::vector<std::pair<char, int>> ope(n);

    for (int i = 0; i < n; ++i)
    {
        char op;
        int num;
        std::cin >> op >> num;

        ope[i] = {op, num};

        if (!adj.contains(num))
        {
            if (op == '+')
            {
                adj[num].push_back({op, i});
                idx[num] = 0;
            }

            continue;
        }

        auto &cur = adj[num];
        if (cur.back().first != op)
        {
            cur.push_back({op, i});
        }
        else if (op == '+')
        {
            cur.push_back({op, i});
        }
        else if (op == 'T')
        {
            cur.back().second = i;
        }
    }

    std::stack<int> sta;
    std::map<int, int> time;
    std::string ans;

    for (int i = 0; i < n; ++i)
    {
        if (ope[i].first == 'T' || ope[i].first == 'F')
        {
            ans += '?';
        }

        while (!sta.empty() && time[sta.top()] <= i)
        {
            sta.pop();
            ans += '-';
        }

        if (ope[i].first == '+')
        {
            time[ope[i].second] = i;

            auto &cur1 = idx[ope[i].second];
            ++cur1;

            auto &cur2 = adj[ope[i].second];

            int size = cur2.size();
            while (cur1 < size)
            {
                if (cur2[cur1].first == 'T')
                {
                    time[ope[i].second] = cur2[cur1].second;
                }

                if (cur2[cur1].first == '+')
                {
                    break;
                }

                ++cur1;
            }

            ans += '+';
            sta.push(ope[i].second);
        }

        while (!sta.empty() && time[sta.top()] <= i)
        {
            sta.pop();
            ans += '-';
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
