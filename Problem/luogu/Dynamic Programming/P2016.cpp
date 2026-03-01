#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 1510, MAXM = 2 * MAXN;
vi head(MAXN), ne(MAXM), to(MAXM);
int n, ans, cnt = 1;

int dfs(int u, int p)
{
    int status = 0;
    for (int i = head[u], temp; i > 0; i = ne[i])
    {
        if (to[i] != p)
        {
            temp = dfs(to[i], u);
            if (temp == 0 && status == 0)
            {
                status = 1;
                ans++;
            }
        }
    }

    return status;
}

int main()
{
    cin >> n;
    for (int i = 0, a, k, b; i < n; i++)
    {
        cin >> a >> k;
        while (k--)
        {
            cin >> b;

            ne[cnt] = head[a];
            to[cnt] = b;
            head[a] = cnt++;

            ne[cnt] = head[b];
            to[cnt] = a;
            head[b] = cnt++;
        }
    }

    dfs(0, -1);

    cout << ans << endl;
}