#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010, MAXM = 100010, MAXK = 11;
vector<int> head(MAXN), ne(MAXM), to(MAXM), weight(MAXM);
vector<vector<int>> dis(MAXN, vector<int>(MAXK, INT_MAX)), visited(MAXN, vector<int>(MAXK));
int n = 0, m = 0, k = 0, s = 0, t = 0, a = 0, b = 0, c = 0, cnt = 1;

priority_queue< vector<int>,
                vector<vector<int>>,
                decltype([](vector<int> &a, vector<int> &b)
                {
                    return a[2] > b[2];
                })> heap;

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m >> k >> s >> t;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;

        ne[cnt] = head[a];
        to[cnt] = b;
        weight[cnt] = c;
        head[a] = cnt++;

        ne[cnt] = head[b];
        to[cnt] = a;
        weight[cnt] = c;
        head[b] = cnt++;
    }

    dis[s][k] = 0;
    heap.push(vector<int>{s, k, 0});

    while (heap.empty() == false)
    {
        int cur = heap.top()[0], count = heap.top()[1], cost = heap.top()[2];
        heap.pop();

        if (visited[cur][count] == 1)
        {
            continue;
        }

        if (cur == t)
        {
            cout << cost << endl;
            return 0;
        }

        visited[cur][count] = 1;
        for (int i = head[cur]; i > 0; i = ne[i])
        {
            int next_city = to[i], next_cost = weight[i];
            if (count > 0 && visited[next_city][count - 1] == 0 && cost < dis[next_city][count - 1])
            {
                dis[next_city][count - 1] = cost;
                heap.push(vector<int>{next_city, count - 1, cost});
            }

            if (visited[next_city][count] == 0 && cost + next_cost < dis[next_city][count])
            {
                dis[next_city][count] = cost + next_cost;
                heap.push(vector<int>{next_city, count, cost + next_cost});
            }
        }
    }

    return -1;
}