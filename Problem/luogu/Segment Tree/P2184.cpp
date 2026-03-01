#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
int n, m, op, a, b;

namespace ST
{
    vi start(MAXN << 2), eds(MAXN << 2);

    void up(int i)
    {
        start[i] = start[i << 1] + start[i << 1 | 1];
        eds[i] = eds[i << 1] + eds[i << 1 | 1];
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            start[i] = eds[i] = 0;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(i);
        }
    }

    int query(int jobt, int jobl, int jobr, int l, int r, int i)
    {
        if (l >= jobl && r <= jobr)
        {
            return (jobt == 0? start[i]: eds[i]);
        }
        
        int mid = l + ((r - l) >> 1), ans = 0;
        if (jobl <= mid)
        {
            ans += query(jobt, jobl, jobr, l, mid, i << 1);
        }

        if (jobr >= mid + 1)
        {
            ans += query(jobt, jobl, jobr, mid + 1, r, i << 1 | 1);
        }

        return ans;
    }

    void add(int jobt, int jobi, int l, int r, int i)
    {
        if (l == r)
        {
            jobt == 0? start[i]++: eds[i]++;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            if (jobi <= mid)
            {
                add(jobt, jobi, l, mid, i << 1);
            }
            else
            {
                add(jobt, jobi, mid + 1, r, i << 1 | 1);
            }

            up(i);
        }
    }
}

int main()
{
    cin >> n >> m;
    ST::build(1, n, 1);

    while (m--)
    {
        cin >> op >> a >> b;
        if (op == 1)
        {
            ST::add(0, a, 1, n, 1);
            ST::add(1, b, 1, n, 1);
        }
        else
        {
            int s = ST::query(0, 1, b, 1, n, 1);
            int e = (a == 1? 0: ST::query(1, 1, a - 1, 1, n, 1));
            cout << s - e << endl;
        }
    }
}