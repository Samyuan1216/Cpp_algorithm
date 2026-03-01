#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400100, MAXM = 400100;
vector<int> head(MAXN), ne(MAXM), to(MAXM), father(MAXN);
bool des[MAXN] = {};
stack<int> s, ans;
int cnt = 1, n = 0, m = 0, k = 0, x = 0, y = 0, cont = 0;

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
    int ua = find(a), ub = find(b);
    if (ua != ub)
    {
        father[ua] = ub;
        cont--;
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;

        ne[cnt] = head[x];
        to[cnt] = y;
        head[x] = cnt++;

        ne[cnt] = head[y];
        to[cnt] = x;
        head[y] = cnt++;
    }

    cin >> k;

    cont = n;
    for (int i = 0; i < k; i++)
    {
        cin >> x;

        des[x] = true;
        s.push(x);
        cont--;
    }

    for (int i = 0; i < n; i++)
    {
        father[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        if (des[i] == true)
        {
            continue;
        }

        for (int j = head[i]; j > 0; j = ne[j])
        {
            if (des[to[j]] == true)
            {
                continue;
            }

            un(i, to[j]);
        }
    }

    for (int i = 0; i <= k; i++)
    {
        ans.push(cont);

        if (s.empty() == false)
        {
            x = s.top();
            s.pop();
            cont++;

            des[x] = false;

            for (int j = head[x]; j > 0; j = ne[j])
            {
                if (des[to[j]] == true)
                {
                    continue;
                }

                un(x, to[j]);
            }
        }
    }

    while (ans.empty() == false)
    {
        cout << ans.top() << endl;
        ans.pop();
    }
}