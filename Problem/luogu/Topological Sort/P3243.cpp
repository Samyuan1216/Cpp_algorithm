#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010, MAXM = 100010;
vector<int> head(MAXN), ne(MAXM), to(MAXM), indegree(MAXN), ans(MAXN);
int cnt = 1, t = 0, n = 0, m = 0, x = 0, y = 0, pc = 0;

priority_queue<int> heap;

void build()
{
    cnt = 1;
    pc = 0;
    fill(head.begin() + 1, head.begin() + n + 1, 0);
    fill(indegree.begin() + 1, indegree.begin() + n + 1, 0);
    fill(ans.begin(), ans.begin() + n, 0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        build();

        for (int i = 0; i < m; i++)
        {
            cin >> x >> y;

            ne[cnt] = head[y];
            to[cnt] = x;
            head[y] = cnt++;

            indegree[x]++;
        }

        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                heap.push(i);
            }
        }

        while (heap.empty() == false)
        {
            int cur = heap.top();
            heap.pop();

            for (int i = head[cur]; i > 0; i = ne[i])
            {
                if (--indegree[to[i]] == 0)
                {
                    heap.push(to[i]);
                }
            }

            ans[pc++] = cur;
        }

        if (pc != n)
        {
            cout << "Impossible!" << endl;
        }
        else
        {
            for (int i = n - 1; i >= 0; i--)
            {
                cout << ans[i] << " ";
            }

            cout << endl;
        }
    }
}