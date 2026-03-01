#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2010, MAXM = 6010, MAXQ = 4000010;
vector<int> head(MAXN), ne(MAXM), to(MAXM), weight(MAXM), dis(MAXN), update_cnt(MAXN), q(MAXQ), enter(MAXN);
int n = 0, m = 0, cnt = 1, l = 0, r = 0, T = 0;

void build()
{
    cnt = 1;
    l = r = 0;

    fill(head.begin() + 1, head.begin() + n + 1, 0);
    fill(enter.begin() + 1, enter.begin() + n + 1, 0);
    fill(dis.begin() + 1, dis.begin() + n + 1, INT_MAX);
    fill(update_cnt.begin() + 1, update_cnt.begin() + n + 1, 0);
}

void add_edge(int u, int v, int w)
{
    ne[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

bool spfa()
{
    dis[1] = 0;
    update_cnt[1]++;

    q[r++] = 1;
    enter[1] = 1;

    while (l < r)
    {
        int u = q[l++];
        enter[u] = 0;

        for (int i = head[u]; i > 0; i = ne[i])
        {
            int v = to[i], w = weight[i];
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                if (enter[v] == 0)
                {
                    update_cnt[v]++;
                    if (update_cnt[v] > n - 1)
                    {
                        return true;
                    }

                    q[r++] = v;
                    enter[v] = 1;
                }
            }
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> T;

    while (T--)
    {
        cin >> n >> m;
        build();

        for (int i = 0, u = 0, v = 0, w = 0; i < m; i++)
        {
            cin >> u >> v >> w;

            if (w >= 0)
            {
                add_edge(u, v, w);
                add_edge(v, u, w);
            }
            else
            {
                add_edge(u, v, w);
            }
        }

        if (spfa() == true)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}