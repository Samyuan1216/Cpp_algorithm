#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000010, MAXM = 4000010, MOD = 100003;
vector<int> head(MAXN), ne(MAXM), to(MAXM), dis(MAXN, INT_MAX), sum(MAXN);
priority_queue< vector<int>,
                vector<vector<int>>,
                decltype([](vector<int> &a, vector<int> &b)
                {
                    return a[1] > b[1];
                })> heap;
int cnt = 1, N = 0, M = 0, x = 0, y = 0;

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

        ne[cnt] = head[y];
        to[cnt] = x;
        head[y] = cnt++;
    }

    dis[1] = 0;
    sum[1] = 1;

    heap.push(vector<int>{1, 0});

    while (heap.empty() == false)
    {
        int cur = heap.top()[0];
        heap.pop();

        for (int i = head[cur]; i > 0; i = ne[i])
        {
            if (dis[cur] + 1 < dis[to[i]])
            {
                dis[to[i]] = dis[cur] + 1;
                sum[to[i]] = sum[cur];

                heap.push(vector<int>{to[i], dis[to[i]]});
            }
            else if (dis[cur] + 1 == dis[to[i]])
            {
                sum[to[i]] = (sum[to[i]] + sum[cur]) % MOD;
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        cout << sum[i] << endl;
    }
}