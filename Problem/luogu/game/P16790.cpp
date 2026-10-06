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

template<typename T = std::string,
         typename F = decltype([](const std::string &word, int i)
         {
             return word[i] - 'a';
         }),
         int N = 26>
struct Trie
{
    std::vector<std::array<int, N>> tree;
    std::vector<int> pass;
    std::vector<int> end;
    int cnt;
    F compute;

    void build()
    {
        cnt = 1;

        tree.assign(2, std::array<int, N>{});
        pass.assign(2, 0);
        end.assign(2, 0);
    }

    Trie(F func = F{}) : compute(func)
    {
        build();
    }

    void insert(const T &word, int n)
    {
        int cur = 1;
        pass[cur]++;

        for (int i = 0; i < n; ++i)
        {
            int path = compute(word, i);
            if (tree[cur][path] == 0)
            {
                if (++cnt >= int(tree.size()))
                {
                    tree.push_back(std::array<int, N>{});
                    pass.push_back(0);
                    end.push_back(0);
                }

                tree[cur][path] = cnt;
            }

            cur = tree[cur][path];
            pass[cur]++;
        }

        end[cur]++;
    }

    int search(const T &word, int n)
    {
        int cur = 1;
        for (int i = 0; i < n; ++i)
        {
            int path = compute(word, i);

            if (tree[cur][path] == 0)
            {
                return 0;
            }

            cur = tree[cur][path];
        }

        return end[cur];
    }

    int prefix_number(const T &prefix, int n)
    {
        int cur = 1;
        for (int i = 0; i < n; ++i)
        {
            int path = compute(prefix, i);
            if (tree[cur][path] == 0)
            {
                return 0;
            }

            cur = tree[cur][path];
        }

        return pass[cur];
    }

    void delete_word(const T &word, int n)
    {
        if (search(word, n) > 0)
        {
            int cur = 1;
            pass[cur]--;

            for (int i = 0; i < n; ++i)
            {
                int path = compute(word, i);
                pass[tree[cur][path]]--;

                if (pass[tree[cur][path]] == 0)
                {
                    tree[cur][path] = 0;
                    return;
                }

                cur = tree[cur][path];
            }

            end[cur]--;
        }
    }

    void clear()
    {
        build();
    }
};

void solve()
{
    int n;
    std::cin >> n;

    Trie tr;
    for (int i = 0; i < n; ++i)
    {
        std::string str;
        std::cin >> str;

        tr.insert(str, std::ssize(str));
    }

    std::vector<int> sg(tr.cnt + 1);
    [&](this auto &&self, int cur) -> void
    {
        for (int path = 0; path < 26; ++path)
        {
            if (tr.tree[cur][path] == 0)
            {
                continue;
            }

            self(tr.tree[cur][path]);

            sg[cur] ^= sg[tr.tree[cur][path]] + 1;
        }
    } (1);

    std::cout << (sg[1] != 0? "XiaoLan\n": "XiaoQiao\n");
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
