#include <bits/stdc++.h>
using namespace std;

const int MAXN = 6010;
vector<int> head(MAXN), ne(MAXN), to(MAXN), val(MAXN), boss(MAXN, 1), no(MAXN), yes(MAXN);
int cnt = 1, n = 0, h = 0;

void f(int u)
{
    no[u] = 0;
    yes[u] = val[u];

    for (int i = head[u]; i > 0; i = ne[i])
    {
        f(to[i]);
        
        no[u] += max(yes[to[i]], no[to[i]]);
        yes[u] += no[to[i]];
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }

    for (int i = 1, l = 0, k = 0; i <= n - 1; i++)
    {
        cin >> l >> k;

        ne[cnt] = head[k];
        to[cnt] = l;
        head[k] = cnt++;
        
        boss[l] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        if (boss[i])
        {
            h = i;
            break;
        }
    }

    f(h);

    cout << max(no[h], yes[h]) << endl;
}