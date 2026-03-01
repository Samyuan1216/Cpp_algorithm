#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010, MAXM = 100010;
vector<int> my_head(MAXN), my_next(MAXM), my_to(MAXM), my_indegree(MAXN);
int cnt = 1;

int main()
{
    ios::sync_with_stdio(false);

    int n = 0, m = 0;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x = 0, y = 0;
        cin >> x >> y;

        my_next[cnt] = my_head[x];
        my_to[cnt] = y;
        my_head[x] = cnt++;

        my_indegree[y]++;
    }

    priority_queue<int, vector<int>, greater<int>> my_q;
    for (int i = 1; i <= n; i++)
    {
        if (my_indegree[i] == 0)
        {
            my_q.push(i);
        }
    }

    while (my_q.empty() == false)
    {
        int cur = my_q.top();
        my_q.pop();

        for (int i = my_head[cur]; i > 0; i = my_next[i])
        {
            my_indegree[my_to[i]]--;
            if (my_indegree[my_to[i]] == 0)
            {
                my_q.push(my_to[i]);
            }
        }

        cout << cur << " ";
    }

    cout << endl;
}