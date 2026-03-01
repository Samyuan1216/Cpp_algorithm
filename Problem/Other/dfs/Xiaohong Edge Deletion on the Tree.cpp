// https://www.nowcoder.com/share/jump/1961392931766809796959

#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXN = 100010;
vi head(MAXN), next(MAXN << 1), to(MAXN << 1);
int n, ans, cnt = 1;

void add_edge(int u, int v)
{
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int dfs(int u, int f)
{
    int cnt = 1;
    for (int ei = head[u], v, num; ei > 0; ei = next[ei])
    {
        v = to[ei];
        if (v != f)
        {
            num = dfs(v, u);
            if (num & 1)
            {
                cnt += num;
            }
            else
            {
                ans++;
            }
        }
    }

    return cnt;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    if (n & 1)
    {
        std::cout << -1 << "\n";
        return 0;
    }

    for (int i = 1, u, v; i < n; i++)
    {
        std::cin >> u >> v;

        add_edge(u, v);
        add_edge(v, u);
    }

    dfs(1, 0);
    std::cout << ans << "\n";
}