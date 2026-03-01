#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010, MAXM = 500010, MOD = 80112002;
vector<int> mhead(MAXN), mnext(MAXM), mto(MAXM), mqueue(MAXN), mindegree(MAXN), mlines(MAXN);
int cnt = 1, n = 0, m = 0;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0, u = 0, v = 0; i < m; i++)
    {
        cin >> u >> v;

        mnext[cnt] = mhead[u];
        mto[cnt] = v;
        mhead[u] = cnt++;

        mindegree[v]++;
    }

    int l = 0, r = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mindegree[i] == 0)
        {
            mqueue[r++] = i;
            mlines[i] = 1;
        }
    }

    int ans = 0;
    while (l < r)
    {
        int u = mqueue[l++];
        if (mhead[u] == 0)
        {
            ans = (ans + mlines[u]) % MOD;
        }
        else
        {
            for (int i = mhead[u]; i > 0; i = mnext[i])
            {
                mlines[mto[i]] = (mlines[mto[i]] + mlines[u]) % MOD;

                mindegree[mto[i]]--;
                if (mindegree[mto[i]] == 0)
                {
                    mqueue[r++] = mto[i];
                }
            }
        }
    }

    cout << ans << endl;
}