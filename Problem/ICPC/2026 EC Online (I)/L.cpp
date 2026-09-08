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

template<typename T = std::string,
         typename F = decltype([](const std::string &word, int i)
         {
             return word[i] - 'a';
         }),
         int N = 26>
struct Trie
{
private:
    std::vector<std::array<int, N>> tree;
    std::vector<int> pass;
    std::vector<int> len;
    std::vector<int> max;
    int cnt;
    i64 sum = 0;
    F compute;

    void build()
    {
        cnt = 1;

        tree.assign(2, std::array<int, N>{});
        pass.assign(2, 0);
        len.assign(2, 0);
        max.push_back(0);
    }
public:
    Trie(F func = F()) : compute(func)
    {
        build();
    }

    i64 insert(const T &word, int n)
    {
        int cur = 1;
        sum += ++pass[cur];
        max.push_back(0);

        for (int i = 0, l = 0; i < n; ++i)
        {
            int path = compute(word, i);
            if (tree[cur][path] == 0)
            {
                if (++cnt >= int(tree.size()))
                {
                    tree.push_back(std::array<int, N>{});
                    pass.push_back(0);
                    len.push_back(0);
                }

                tree[cur][path] = cnt;
            }

            cur = tree[cur][path];
            pass[cur]++;
            len[cur] = ++l;
        }

        cur = 1;
        for (int i = 0; i < n; ++i)
        {
            int path = compute(word, i);
            cur = tree[cur][path];

            if (len[cur] > max[pass[cur]])
            {
                sum += (len[cur] ^ pass[cur]) - (max[pass[cur]] ^ pass[cur]);
                max[pass[cur]] = len[cur];
            }
        }

        return sum;
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
        std::cout << tr.insert(str, std::ssize(str)) << "\n";
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
