#include <bits/stdc++.h>
#include <bits/extc++.h>
namespace ranges = std::ranges;
namespace views = std::views;

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

template<typename T = std::string,
         typename F = decltype([](const std::string &word, int i)
         {
             return word[i] - 'a';
         }),
         int N = 26>
class AC
{
    std::vector<std::array<int, N>> tree;
    std::vector<int> end;
    std::vector<int> fail;
    std::vector<bool> alert;
    std::vector<int> len;
    int cnt;
    F compute;

    void build()
    {
        cnt = 0;

        tree.assign(1, std::array<int, N>{});
        fail.assign(1, 0);
        alert.assign(1, false);
        len.assign(1, 0);
    }
public:
    AC(F func = F{}): compute(func)
    {
        build();
    }

    void insert(const T &word)
    {
        int u = 0;
        for (int i = 0, c; i < std::ssize(word); ++i)
        {
        c = compute(word, i);
            if (tree[u][c] == 0)
            {
                if (++cnt >= std::ssize(tree))
                {
                    tree.push_back(std::array<int, N>{});
                    fail.push_back(0);
                    alert.push_back(false);
                    len.push_back(0);
                }

                tree[u][c] = cnt;
            }

            u = tree[u][c];
        }

        end.push_back(u);
        alert[u] = true;
        len[u] |= 1 << std::ssize(word);
    }

    void set_fail()
    {
        std::queue<int> q;
        for (int i = 0; i < N; ++i)
        {
            if (tree[0][i] > 0)
            {
                q.push(tree[0][i]);
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < N; ++i)
            {
                if (tree[u][i] == 0)
                {
                    tree[u][i] = tree[fail[u]][i];
                }
                else
                {
                    fail[tree[u][i]] = tree[fail[u]][i];
                    len[tree[u][i]] |= len[fail[tree[u][i]]];
                    q.push(tree[u][i]);
                }
            }

            alert[u] = alert[u] || alert[fail[u]];
        }
    }

    std::vector<int> query(std::string &&str)
    {
        std::vector<int> times(cnt);
        for (int i = 0, u = 0; i < std::ssize(str); ++i)
        {
            u = tree[u][str[i] - 'a'];
            ++times[u];
        }

        std::vector<std::vector<int>> g(cnt);
        for (int i = 0; i < cnt; ++i)
        {
            g[fail[i]].push_back(i);
        }

        auto dfs = [&](auto &&self, int u)
        {
            for (auto &v: g[u])
            {
                self(self, v);
                times[u] += times[v];
            }
        };

        dfs(dfs, 0);

        return times;
    }

    bool is_alert(int i)
    {
        return alert[i];
    }

    int get(int u, int c)
    {
        return tree[u][c];
    }

    int length(int u)
    {
        return len[u];
    }
};

void solve()
{
    int n, m;
    std::cin >> n >> m;

    AC ac;
    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;

        ac.insert(str);
    }

    ac.set_fail();

    while (m--)
    {
        std::string str;
        std::cin >> str;

        int status = 1, ans = 0;
        for (int i = 0, u = 0; i < std::ssize(str); ++i)
        {
            u = ac.get(u, str[i] - 'a');
            status <<= 1;

            if (ac.length(u) & status)
            {
                status |= 1;
                ans = i + 1;
            }
        }

        std::cout << ans << "\n";
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
