#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000001;
const int OFFSET = 30001;
int arr[OFFSET + MAXN + OFFSET];
int n, m;

void set_a(int l, int r, int s, int e, int d)
{
    arr[l + OFFSET] += s;
    arr[l + 1 + OFFSET] += d - s;
    arr[r + 1 + OFFSET] -= d + e;
    arr[r + 2 + OFFSET] += e;
}

void fall(int v, int x)
{
    set_a(x - 3 * v + 1, x - 2 * v, 1, v, 1);
    set_a(x - 2 * v + 1, x, v - 1, -v, -1);
    set_a(x + 1, x + 2 * v, -v + 1, v, 1);
    set_a(x + 2 * v + 1, x + 3 * v - 1, v - 1, 1, -1);
}

void build()
{
    for (int i = 1; i <= m + OFFSET; i++)
    {
        arr[i] += arr[i- 1];
    }

    for (int i = 1; i <= m + OFFSET; i++)
    {
        arr[i] += arr[i- 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0, v = 0, x = 0; i < n; i++)
    {
        cin >> v >> x;

        fall(v, x);
    }

    build();

    int start = OFFSET + 1;
    cout << arr[start];

    for (int i = 2; i <= m; i++)
    {
        start++;
        cout << " " << arr[start];
    }

    cout << endl;
}
