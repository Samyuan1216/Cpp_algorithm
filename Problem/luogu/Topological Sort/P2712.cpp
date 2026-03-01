#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);

    int n = 0;
    cin >> n;

    static vector<int> head(510), next(10010), to(10010), indegree(510, -1), camera(510);
    int cnt = 1, maxn = 0;
    for (int i = 0; i < n; i++)
    {
        int x = 0, m = 0;
        cin >> x >> m;

        maxn = max(maxn, x);
        indegree[x] = max(0, indegree[x]);
        camera[x] = 1;

        while (m--)
        {
            int y = 0;
            cin >> y;

            next[cnt] = head[x];
            to[cnt] = y;
            head[x] = cnt++;

            indegree[y] = max(0, indegree[y]);
            indegree[y]++;
        }
    }

    vector<int> q(510);
    int l = 0, r = 0;
    for (int i = 1; i <= maxn; i++)
    {
        if (indegree[i] == 0 && camera[i] == 1)
        {
            q[r++] = i;
        }
    }

    int cnt_2 = 0;
    while (l < r)
    {
        int cur = q[l++];
        cnt_2++;

        for (int i = head[cur]; i > 0; i = next[i])
        {
            indegree[to[i]]--;
            if (indegree[to[i]] == 0 && camera[to[i]] == 1)
            {
                q[r++] = to[i];
            }
        }
    }

    if (cnt_2 == n)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << n - cnt_2 << endl;
    }
}