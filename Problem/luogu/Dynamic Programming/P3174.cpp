#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 300010;
vi head(MAXN), ne(2 * MAXN), to(2 * MAXN);
int n, m, cnt = 1;

void add_edge(int u, int v)
{
    ne[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

struct tepo
{
    int maxp;
    int maxc;

    tepo(int a, int b): maxp(a), maxc(b) {}
};

tepo dfs(int u, int p)
{
    int maxp = 0, sub_maxp = 0, maxc = 0, num = 0;
    for (int ei = head[u], v; ei > 0; ei = ne[ei])
    {
        v = to[ei];
        if (v != p)
        {
            tepo tmp = dfs(v, u);
            maxc = max(maxc, tmp.maxc);
            
            if (tmp.maxp >= maxp)
            {
                sub_maxp = maxp;
                maxp = tmp.maxp;
            }
            else if (tmp.maxp > sub_maxp)
            {
                sub_maxp = tmp.maxp;
            }

            num++;
        }
    }

    if (maxc <= maxp + sub_maxp + num + 1)
    {
        maxc = maxp + sub_maxp + num + 1;
        if (p != 0)
        {
            maxc++;
        }
    }
    
    tepo res(maxp + num, maxc);
    return res;
}

int main()
{
    cin >> n >> m;
    for (int i = 0, a, b; i < m; i++)
    {
        cin >> a >> b;

        add_edge(a, b);
        add_edge(b, a);
    }

    tepo res = dfs(1, 0);
    cout << res.maxc << endl;
}