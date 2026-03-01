#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010, MAXM = 100010;
int head[MAXN], ne[MAXM], to[MAXM], indegree[MAXN], q[MAXN];
int cnt = 1, l = 0, r = 0, N = 0, M = 0, x = 0, y = 0, status = 0, num = 0;

int main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M;

    for (int i = 0; i < M; i++)
    {
        cin >> x >> y;

        ne[cnt] = head[x];
        to[cnt] = y;
        head[x] = cnt++;

        indegree[y]++;
    }

    for (int i = 1; i <= N; i++)
    {
        if (indegree[i] == 0)
        {
            q[r++] = i;
        }
    }

    while (l < r)
    {
        int cur = q[l++];
        num = 0;

        for (int i = head[cur]; i > 0; i = ne[i])
        {
            indegree[to[i]]--;
            if (indegree[to[i]] == 0)
            {
                num++;
                q[r++] = to[i];
            }
        }

        if (num >= 2)
        {
            status = 1;
        }
    }

    for (int i = 0; i < N; i++)
    {
        cout << q[i] << endl;
    }

    cout << status << endl;
}