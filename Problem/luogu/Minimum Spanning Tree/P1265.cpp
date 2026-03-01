#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
vector<pair<int, double>> heap(MAXN);
vector<int> where(MAXN, -1);
int heap_size = -1;

int left(int i)
{
    return i * 2 + 1;
}

int right(int i)
{
    return (i + 1) * 2;
}

int parent(int i)
{
    return (i - 1) / 2;
}

void heapify(int i)
{
    int l = left(i), r = right(i), minn = i;

    if (l <= heap_size && heap[l].second < heap[minn].second)
    {
        minn = l;
    }

    if (r <= heap_size && heap[r].second < heap[minn].second)
    {
        minn = r;
    }

    if (minn != i)
    {
        swap(heap[minn], heap[i]);
        swap(where[heap[minn].first], where[heap[i].first]);

        heapify(minn);
    }
}

void pus(int v, double w)
{
    heap_size++;
    heap[heap_size].first = v;
    heap[heap_size].second = w;
    where[v] = heap_size;

    for (int i = heap_size, p = parent(heap_size); i > 0 && heap[i].second < heap[p].second; i = p, p = parent(i))
    {
        swap(heap[i], heap[p]);
        swap(where[heap[i].first], where[heap[p].first]);
    }
}

void po()
{
    where[heap[0].first] = -2;
    swap(heap[heap_size], heap[0]);
    where[heap[0].first] = 0;
    heap_size--;

    heapify(0);
}

void ins(int v, double w)
{
    heap[where[v]].second = w;
    for (int i = where[v], p = parent(where[v]); i > 0 && heap[i].second < heap[p].second; i = p, p = parent(i))
    {
        swap(heap[i], heap[p]);
        swap(where[heap[i].first], where[heap[p].first]);
    }
}

vector<vector<int>> p(MAXN, vector<int>(2));
int n = 0;
double ans = 0;

double dis(vector<int> &a, vector<int> &b)
{
    return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &p[i][0], &p[i][1]);
    }

    where[1] = -2;
    for (int i = 2; i <= n; i++)
    {
        pus(i, dis(p[1], p[i]));
    }

    while (heap_size >= 0)
    {
        int u = heap[0].first;
        ans += heap[0].second;
        po();

        for (int v = 1; v <= n; v++)
        {
            if (u == v)
            {
                continue;
            }

            if (where[v] >= 0 && dis(p[u], p[v]) < heap[where[v]].second)
            {
                ins(v, dis(p[u], p[v]));
            }
            else if (where[v] == -1)
            {
                pus(v, dis(p[u], p[v]));
            }
        }
    }

    printf("%.2f", ans);
}