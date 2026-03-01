#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010, MAXM = 200010;
vector<int> head(MAXN), ne(MAXM), to(MAXM), indegree(MAXN), q(MAXN), dp(MAXN, 1);
int cnt = 1, l = 0, r = 0, N = 0, M = 0, x = 0, y = 0;

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
        for (int i = head[cur]; i > 0; i = ne[i])
        {
            indegree[to[i]]--;
            if (indegree[to[i]] == 0)
            {
                q[r++] = to[i];
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = head[q[i]]; j > 0; j = ne[j])
        {
            dp[to[j]] = max(dp[to[j]], dp[q[i]] + 1);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << dp[i] << endl;
    }
}