#include <bits/stdc++.h>
using namespace std;

using vd = vector<double>;

const int MAXN = 100010;
vd arr(MAXN);

namespace ST
{
    vd sum1(MAXN << 2), sum2(MAXN << 2), ad(MAXN << 2);

    void lazy(int i, double v, int n)
    {
        sum2[i] += 2 * v * sum1[i] + n * v * v;
        sum1[i] += v * n;
        ad[i] += v;
    }

    void up(int i)
    {
        sum1[i] = sum1[i << 1] + sum1[i << 1 | 1];
        sum2[i] = sum2[i << 1] + sum2[i << 1 | 1];
    }

    void down(int i, int ln, int rn)
    {
        if (ad[i] != 0)
        {
            lazy(i << 1, ad[i], ln);
            lazy(i << 1 | 1, ad[i], rn);

            ad[i] = 0;
        }
    }
    
    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum1[i] = arr[l];
            sum2[i] = arr[l] * arr[l];
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }

        ad[i] = 0;
    }

    void add(int jobl, int jobr, double jobv, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            lazy(i, jobv, r - l + 1);
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            down(i, mid - l + 1, r - mid);

            if (jobl <= mid)
            {
                add(jobl, jobr, jobv, l, mid, i << 1);
            }

            if (jobr >= mid + 1)
            {
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }

    double query(vd &sum, int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return sum[i];
        }

        int mid = l + ((r - l) >> 1);
        down(i, mid - l + 1, r - mid);

        double ans = 0;
        if (jobl <= mid)
        {
            ans += query(sum, jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            ans += query(sum, jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &arr[i]);
    }

    ST::build(1, n, 1);

    while (m--)
    {
        int op;
        cin >> op;

        if (op == 1)
        {
            int x, y;
            double k;
            scanf("%d %d %lf", &x, &y, &k);

            ST::add(x, y, k, 1, n, 1);
        }
        else if (op == 2)
        {
            int x, y;
            scanf("%d %d", &x, &y);

            double ans = ST::query(ST::sum1, x, y, 1, n, 1) / (y - x + 1);
            printf("%.4lf\n", ans);
        }
        else
        {
            int x, y;
            scanf("%d %d", &x, &y);

            double a = ST::query(ST::sum1, x, y, 1, n, 1);
            double b = ST::query(ST::sum2, x, y, 1, n, 1);
            double size = y - x + 1;
            double ans = b / size - (a / size) * (a / size);
            printf("%.4lf\n", ans);
        }
    }
}