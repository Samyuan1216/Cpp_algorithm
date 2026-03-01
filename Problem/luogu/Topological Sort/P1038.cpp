#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110, MAXM = 10010;
vector<int> head(MAXN), ne(MAXM), to(MAXM), weight(MAXM), indegree(MAXN), q(MAXN), C(MAXN);
int cnt = 1, l = 0, r = 0, n = 0, m = 0, len = 0, s = 0, e = 0;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 1, c = 0, u = 0; i <= n; i++)
    {
        cin >> c >> u;

        if (c <= 0)
        {
            C[i] = c - u;
        }
        else
        {
            C[i] = c;
        }
    }

    for (int i = 0, a = 0, b = 0, w = 0; i < m; i++)
    {
        cin >> a >> b >> w;

        ne[cnt] = head[a];
        to[cnt] = b;
        weight[cnt] = w;
        head[a] = cnt++;

        indegree[b]++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q[r++] = i;
        }
    }

    while (l < r)
    {
        len = r - l;
        s = l;
        e = r;

        for (int i = 0; i < len; i++)
        {
            int cur = q[l++];
            for (int j = head[cur]; j > 0; j = ne[j])
            {
                if (C[cur] > 0)
                {
                    C[to[j]] += C[cur] * weight[j];
                }

                indegree[to[j]]--;
                if (indegree[to[j]] == 0)
                {
                    q[r++] = to[j];
                }
            }
        }
    }

    sort(q.begin() + s, q.begin() + e);

    int count = 0;
    for (int i = s; i < e; i++)
    {
        if (C[q[i]] > 0)
        {
            cout << q[i] << " " << C[q[i]] << endl;
            count++;
        }
    }

    if (count == 0)
    {
        cout << "NULL" << endl;
    }
}