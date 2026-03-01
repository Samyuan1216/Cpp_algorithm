#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
vi diff(MAXN), sta1(MAXN), sta2(MAXN);
int n, tp1, tp2, ans;

int fin(int l, int r, int v)
{
    int ans = -1, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (v < sta1[mid])
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

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> diff[i];
    }

    for (int i = 1; i <= n; i++)
    {
        while (tp1 > 0 && diff[i] <= diff[sta1[tp1 - 1]])
        {
            tp1--;
        }
        sta1[tp1++] = i;

        while (tp2 > 0 && diff[i] > diff[sta2[tp2 - 1]])
        {
            tp2--;
        }
        sta2[tp2++] = i;

        if (tp2 > 1)
        {
            int index = fin(0, tp1 - 2, sta2[tp2 - 2]);
            if (index >= 0)
            {
                ans = max(ans, sta1[tp1 - 1] - sta1[index] + 1);
            }
        }
        else if (tp1 > 1)
        {
            ans = max(ans, sta1[tp1 - 1] - sta1[0] + 1);
        }
    }

    cout << ans << endl;
}