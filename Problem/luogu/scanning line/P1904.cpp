#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

struct info
{
    int height;
    int right;

    info(int a, int b): height(a), right(b) {}

    bool operator<(const info &other) const
    {
        return height < other.height;
    }
};
priority_queue<info> heap;

const int MAXN = 5010;
vvi arr(MAXN, vi(3));
vi x(MAXN << 1), h(MAXN << 1), ans(MAXN << 2);
int xi, idx, n;

int main()
{
    while (cin >> arr[n][0] >> arr[n][1] >> arr[n][2])
    {
        x[xi++] = arr[n][0];
        x[xi++] = arr[n][2];
        n++;
    }

    sort(arr.begin(), arr.begin() + n, [](vi &a, vi &b)
    {
        return a[0] < b[0];
    });

    sort(x.begin(), x.begin() + xi);
    xi = unique(x.begin(), x.begin() + xi) - x.begin();

    for (int i = 0, j = 0; i < xi; i++)
    {
        while (!heap.empty() && heap.top().right <= x[i])
        {
            heap.pop();
        }

        while (j < n && arr[j][0] <= x[i])
        {
            heap.push(info(arr[j][1], arr[j][2]));
            j++;
        }

        if (!heap.empty())
        {
            h[i] = heap.top().height;
        }
    }

    for (int i = 0; i < xi; i++)
    {
        if (i == 0 || h[i] != h[i - 1])
        {
            ans[idx++] = x[i];
            ans[idx++] = h[i];
        }
    }

    for (int i = 0; i < idx; i++)
    {
        cout << ans[i] << " \n"[i == idx - 1];
    }
}