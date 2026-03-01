#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;
vector<vector<int>> g(MAXN, vector<int>(MAXN));
int n = 0, ans = 0;

vector<vector<int>> heap(MAXN, vector<int>(2));
vector<int> where(MAXN, -1);
int heap_size = -1;

void heapify(int i)
{
    int l = i * 2 + 1, r = (i + 1) * 2, minn = i;
    if (l <= heap_size && heap[l][1] < heap[minn][1])
    {
        minn = l;
    }

    if (r <= heap_size && heap[r][1] < heap[minn][1])
    {
        minn = r;
    }

    if (minn != i)
    {
        swap(heap[minn], heap[i]);
        swap(where[heap[minn][0]], where[heap[i][0]]);

        heapify(minn);
    }
}

void pus(int v, int w)
{
    heap_size++;
    heap[heap_size][0] = v;
    heap[heap_size][1] = w;
    where[v] = heap_size;

    for (int i = heap_size, p = (heap_size - 1) / 2; i > 0 && heap[i][1] < heap[p][1]; i = p, p = (i - 1) / 2)
    {
        swap(heap[i], heap[p]);
        swap(where[heap[i][0]], where[heap[p][0]]);
    }
}

void po()
{
    where[heap[0][0]] = -2;
    swap(heap[0], heap[heap_size]);
    where[heap[0][0]] = 0;
    heap_size--;

    heapify(0);
}

void ins(int v, int w)
{
    heap[where[v]][1] = w;
    for (int i = where[v], p = (where[v] - 1) / 2; i > 0 && heap[i][1] < heap[p][1]; i = p, p = (i - 1) / 2)
    {
        swap(heap[i], heap[p]);
        swap(where[heap[i][0]], where[heap[p][0]]);
    }
}

int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> g[i][j];
        }
    }

    for (int i = 2; i <= n; i++)
    {
        pus(i, g[1][i]);
    }

    where[1] = -2;

    while (heap_size >= 0)
    {
        int u = heap[0][0];
        ans += heap[0][1];
        po();

        for (int v = 1; v <= n; v++)
        {
            if (u == v)
            {
                continue;
            }

            if (where[v] >= 0 && g[u][v] < heap[where[v]][1])
            {
                ins(v, g[u][v]);
            }
            else if (where[v] == -1)
            {
                pus(v, g[u][v]);
            }
        }
    }

    cout << ans << endl;
}