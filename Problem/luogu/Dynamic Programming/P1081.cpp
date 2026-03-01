#include <bits/stdc++.h>

using arri = std::array<int, 2>;

const int MAXN = 100010, MAXP = 20;
int arr[MAXN], to1[MAXN], dist1[MAXN], to2[MAXN], dist2[MAXN], last[MAXN], next[MAXN];
int stto[MAXN][MAXP + 1], stdist[MAXN][MAXP + 1], sta[MAXN][MAXP + 1], stb[MAXN][MAXP + 1];
arri rank[MAXN];
int n, m, x0, a, b;

void update(int i, int j)
{
    if (j == 0)
    {
        return;
    }

    int dist = std::abs(arr[i] - arr[j]);
    if (to1[i] == 0 || dist < dist1[i] || (dist == dist1[i] && arr[j] < arr[to1[i]]))
    {
        to2[i] = to1[i];
        dist2[i] = dist1[i];

        to1[i] = j;
        dist1[i] = dist;
    }
    else if (to2[i] == 0 || dist < dist2[i] || (dist == dist2[i] && arr[j] < arr[to2[i]]))
    {
        to2[i] = j;
        dist2[i] = dist;
    }
}

void del(int i)
{
    int l = last[i], r = next[i];
    if (l != 0)
    {
        next[l] = r;
    }

    if (r != 0)
    {
        last[r] = l;
    }
}

void near()
{
    for (int i = 1; i <= n; i++)
    {
        rank[i][0] = i;
        rank[i][1] = arr[i];
    }

    std::sort(rank + 1, rank + n + 1, [](arri &a, arri &b)
    {
        return a[1] < b[1];
    });

    for (int i = 1; i <= n; i++)
    {
        last[rank[i][0]] = rank[i - 1][0];
        next[rank[i][0]] = rank[i + 1][0];
    }

    for (int i = 1; i <= n; i++)
    {
        update(i, last[i]);
        update(i, last[last[i]]);
        update(i, next[i]);
        update(i, next[next[i]]);

        del(i);
    }
}

void st()
{
    for (int i = 1; i <= n; i++)
    {
        stto[i][0] = to1[to2[i]];
        stdist[i][0] = dist2[i] + dist1[to2[i]];
        sta[i][0] = dist2[i];
        stb[i][0] = dist1[to2[i]];
    }

    for (int p = 1; p <= MAXP; p++)
    {
        for (int i = 1; i <= n; i++)
        {
            stto[i][p] = stto[stto[i][p - 1]][p - 1];
            if (stto[i][p] != 0)
            {
                stdist[i][p] = stdist[i][p - 1] + stdist[stto[i][p - 1]][p - 1];
                sta[i][p] = sta[i][p - 1] + sta[stto[i][p - 1]][p - 1];
                stb[i][p] = stb[i][p - 1] + stb[stto[i][p - 1]][p - 1];
            }
        }
    }
}

void travel(int s, int x)
{
    a = b = 0;
    for (int p = MAXP; p >= 0; p--)
    {
        if (stto[s][p] != 0 && stdist[s][p] <= x)
        {
            x -= stdist[s][p];
            a += sta[s][p];
            b += stb[s][p];
            s = stto[s][p];
        }
    }

    if (dist2[s] <= x)
    {
        a += dist2[s];
    }
}

int best(int x0)
{
    int ans = 0;
    double minn = DBL_MAX, cur;
    for (int i = 1; i < n; i++)
    {
        travel(i, x0);

        cur = (b == 0? DBL_MAX: ((double)a / (double)b));
        if (ans == 0 || cur < minn || (cur == minn && arr[i] > arr[ans]))
        {
            ans = i;
            minn = cur;
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    near();
    st();

    std::cin >> x0;
    std::cout << best(x0) << "\n";

    std::cin >> m;
    for (int i = 1, s, x; i <= m; i++)
    {
        std::cin >> s >> x;

        travel(s, x);
        std::cout << a << " " << b << "\n";
    }
}