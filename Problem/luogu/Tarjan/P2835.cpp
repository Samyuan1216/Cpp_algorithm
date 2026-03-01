#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210, MAXM = 40010;
vector<int> head(MAXN), ne(MAXM), to(MAXM), head_s(MAXN), ne_s(MAXM), to_s(MAXM), dfn(MAXN), low(MAXN), st(MAXN), in_st(MAXN), indegree(MAXN), father(MAXN), which(MAXN);
set<pair<int, int>> s;
int cnt = 1, cnt_s = 1, d = 1, sc = 0, tp = 0, N = 0, x = 0, ans = 0;

int find(int i)
{
    if (i != father[i])
    {
        father[i] = find(father[i]);
    }

    return father[i];
}

void un(int a, int b)
{
    father[find(a)] = find(b);
}

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
        sc++;
        do
        {
            tp--;
            un(u, st[tp]);
            in_st[st[tp]] = 0;
        } while (st[tp] != u);
        
        which[find(u)] = sc;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        cin >> x;
        while (x != 0)
        {
            ne[cnt] = head[i];
            to[cnt] = x;
            head[i] = cnt++;

            cin >> x;
        }
    }

    for (int i = 1; i <= N; i++)
    {
        father[i] = i;
    }

    for (int i = 1; i <= N; i++)
    {
        if (dfn[i] == 0)
        {
            tarjan(i);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = head[i]; j > 0; j = ne[j])
        {
            if (find(i) != find(to[j]))
            {
                ne_s[cnt_s] = head_s[which[find(i)]];
                to_s[cnt_s] = which[find(to[j])];
                head_s[which[find(i)]] = cnt_s++;

                indegree[which[find(to[j])]]++;
            }
        }
    }

    for (int i = 1; i <= sc; i++)
    {
        if (indegree[i] == 0)
        {
            ans++;
        }
    }

    cout << ans << endl;
}