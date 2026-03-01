#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110, MAXM = 4510;
vector<int> head(MAXN), ne(MAXM), to(MAXM), indegree(MAXN), q(MAXN), father(MAXN);
bool path[MAXN][MAXN];
int cnt = 1, l = 0, r = 0, N = 0, M = 0, A = 0, B = 0, ans = 0, roots = 0;

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

int main()
{
    ios::sync_with_stdio(false);

    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        father[i] = i;
        path[i][i] = true;
    }

    for (int i = 0; i < M; i++)
    {
        cin >> A >> B;

        un(A, B);

        ne[cnt] = head[A];
        to[cnt] = B;
        head[A] = cnt++;

        indegree[B]++;
    }

    for (int i = 1; i <= N; i++)
    {
        if (i == father[i])
        {
            roots++;
        }
    }

    if (roots > 1)
    {
        cout << 0 << endl;
        return 0;
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
        if (l == r)
        {
            bool status = true;
            for (int i = 0; i < r; i++)
            {
                if (path[cur][q[i]] == false)
                {
                    status = false;
                    break;
                }
            }

            if (status == true)
            {
                ans++;
            }
        }

        for (int i = head[cur]; i > 0; i = ne[i])
        {
            for (int j = 0; j < r; j++)
            {
                path[to[i]][q[j]] |= path[cur][q[j]];
            }

            indegree[to[i]]--;
            if (indegree[to[i]] == 0)
            {
                q[r++] = to[i];
            }
        }
    }

    cout << ans << endl;
}