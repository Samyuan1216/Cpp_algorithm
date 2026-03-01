#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 20010;
vvi rec(MAXN, vi(4)), lines(MAXN, vi(4));
vi arr(MAXN);
int n, m;
ll ans;

int rk(int num)
{
    int ans = 0, l = 1, r = m, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (num <= arr[mid])
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return ans;
}

namespace ST
{
    vi len(MAXN << 1), cover(MAXN << 1), times(MAXN << 1);

    void up(int i)
    {
        if (times[i] > 0)
        {
            cover[i] = len[i];
        }
        else
        {
            cover[i] = cover[i << 1] + cover[i << 1 | 1];
        }
    }

    void build(int l, int r, int i)
    {
        if (l < r)
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
        }

        len[i] = arr[r + 1] - arr[l];
        cover[i] = 0;
        times[i] = 0;
    }
    
    void add(int jobl, int jobr, int jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            times[i] += jobv;
        }
        else
        {
            int mid = l + ((r - l) >> 1);

            if (jobl <= mid)
            {
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }
        }

        up(i);
    }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> rec[i][0] >> rec[i][1] >> rec[i][2] >> rec[i][3];
    }

    for (int i = 1, j = 1 + n, x1, y1, x2, y2; i <= n; i++, j++)
    {
        x1 = rec[i][0], y1 = rec[i][1], x2 = rec[i][2], y2 = rec[i][3];

        arr[i] = y1, arr[j] = y2;

        lines[i][0] = x1, lines[i][1] = y1, lines[i][2] = y2, lines[i][3] = 1;
        lines[j][0] = x2, lines[j][1] = y1, lines[j][2] = y2, lines[j][3] = -1;
    }

    sort(arr.begin() + 1, arr.begin() + (n << 1) + 1);
    m = unique(arr.begin() + 1, arr.begin() + (n << 1) + 1) - arr.begin() - 1;
    arr[m + 1] = arr[m];

    ST::build(1, m, 1);

    sort(lines.begin() + 1, lines.begin() + (n << 1) + 1, [](vi &a, vi &b)
    {
        return (a[0] != b[0]? (a[0] < b[0]): (a[3] > b[3]));
    });

    for (int i = 1, pre; i <= (n << 1); i++)
    {
        pre = ST::cover[1];
        ST::add(rk(lines[i][1]), rk(lines[i][2]) - 1, lines[i][3], 1, m, 1);
        ans += abs(ST::cover[1] - pre);
    }

    for (int i = 1, j = 1 + n, x1, y1, x2, y2; i <= n; i++, j++)
    {
        x1 = rec[i][0], y1 = rec[i][1], x2 = rec[i][2], y2 = rec[i][3];

        arr[i] = x1, arr[j] = x2;

        lines[i][0] = y1, lines[i][1] = x1, lines[i][2] = x2, lines[i][3] = 1;
        lines[j][0] = y2, lines[j][1] = x1, lines[j][2] = x2, lines[j][3] = -1;
    }

    sort(arr.begin() + 1, arr.begin() + (n << 1) + 1);
    m = unique(arr.begin() + 1, arr.begin() + (n << 1) + 1) - arr.begin() - 1;
    arr[m + 1] = arr[m];

    ST::build(1, m, 1);

    sort(lines.begin() + 1, lines.begin() + (n << 1) + 1, [](vi &a, vi &b)
    {
        return (a[0] != b[0]? (a[0] < b[0]): (a[3] > b[3]));
    });

    for (int i = 1, pre; i <= (n << 1); i++)
    {
        pre = ST::cover[1];
        ST::add(rk(lines[i][1]), rk(lines[i][2]) - 1, lines[i][3], 1, m, 1);
        ans += abs(ST::cover[1] - pre);
    }

    cout << ans << endl;
}