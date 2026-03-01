#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500010;
vector<vector<int>> tree(MAXN, vector<int>(2));
vector<int> pass(MAXN), ed(MAXN);
int cnt = 1, M = 0, N = 0, cur = 0, path = 0, x = 0;

void insert(int n)
{
    cur = 1;
    pass[cur]++;

    for (int i = 0; i < n; i++)
    {
        cin >> path;
        if (tree[cur][path] == 0)
        {
            cnt++;
            tree[cur][path] = cnt;
        }

        cur = tree[cur][path];
        pass[cur]++;
    }

    ed[cur]++;
}

int search(int n)
{
    cur = 1;

    int i = 0, sum = 0;
    for (i; i < n; i++)
    {
        cin >> path;
        if (tree[cur][path] == 0)
        {
            break;
        }

        cur = tree[cur][path];
        sum += ed[cur];
    }

    if (i == n)
    {
        sum = sum - ed[cur] + pass[cur];
    }

    for (i++; i < n; i++)
    {
        cin >> path;
    }

    return sum;
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> M >> N;

    while (M--)
    {
        cin >> x;
        insert(x);
    }

    while (N--)
    {
        cin >> x;
        cout << search(x) << endl;
    }
}