#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 200010;

namespace ST
{
    vi arr(MAXN), len(MAXN << 2), pre(MAXN << 2), suf(MAXN << 2);

    void up(int l, int r, int i)
    {
        len[i] = max(len[i << 1], len[i << 1 | 1]);
        pre[i] = pre[i << 1];
        suf[i] = suf[i << 1 | 1];

        int mid = l + ((r - l) >> 1);
        if (arr[mid] != arr[mid + 1])
        {
            len[i] = max(len[i], suf[i << 1] + pre[i << 1 | 1]);
            if (len[i << 1] == mid - l + 1)
            {
                pre[i] += pre[i << 1 | 1];
            }

            if (len[i << 1 | 1] == r - mid)
            {
                suf[i] += suf[i << 1];
            }
        }
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            len[i] = pre[i] = suf[i] = 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);

            up(l, r, i);
        }
    }

    void rever(int jobi, int l, int r, int i)
    {
        if (l == r)
        {
            arr[jobi] ^= 1;
        }
        else
        {
            int mid = l + ((r - l) >> 1);

            if (jobi <= mid)
            {
                rever(jobi, l, mid, i << 1);
            }
            else
            {
                rever(jobi, mid + 1, r, i << 1 | 1);
            }

            up(l, r, i);
        }
    }
}

int n, q, x;

int main()
{
    cin >> n >> q;
    ST::build(1, n, 1);

    while (q--)
    {
        cin >> x;
        ST::rever(x, 1, n, 1);
        cout << ST::len[1] << endl;
    }
}