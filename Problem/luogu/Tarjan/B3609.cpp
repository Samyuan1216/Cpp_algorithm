#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010, MAXM = 100010;
vector<int> head(MAXN), ne(MAXM), to(MAXM), dfn(MAXN), low(MAXN), st(MAXN), in_st(MAXN);
vector<vector<int>> ans;
int cnt = 1, d = 1, tp = 0, sc = -1, n = 0, m = 0, u = 0, v = 0;

void tarjan(int u)
{
    dfn[u] = low[u] = d++;
    st[tp++] = u;
    in_st[u] = 1;

    for (int i = head[u]; i > 0; i = ne[i])
    {
        int v = to[i];
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_st[v] == 1)
        {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u])
    {
        ans.push_back(vector<int>());
        sc++;

        do
        {
            tp--;
            ans[sc].push_back(st[tp]);
            in_st[st[tp]] = 0;
        } while (st[tp] != u);

        sort(ans[sc].begin(), ans[sc].end());
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> u >> v;

        ne[cnt] = head[u];
        to[cnt] = v;
        head[u] = cnt++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);
        }
    }

    sort(ans.begin(), ans.end());
    
    cout << sc + 1 << endl;
    for (int i = 0; i <= sc; i++)
    {
        for (auto &x: ans[i])
        {
            cout << x << " ";
        }

        cout << endl;
    }
}