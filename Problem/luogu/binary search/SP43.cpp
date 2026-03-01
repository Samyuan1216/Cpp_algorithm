#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 510;
vi arr(MAXN), sp(MAXN);
int n, m, k, res, le, ri;

bool check(int v)
{
    int cnt = 0, sum = 0;
    for (int i = m; i >= 1; i--)
    {
        if (sum + arr[i] <= v)
        {
            sum += arr[i];
        }
        else
        {
            sum = arr[i];
            cnt++;
        }
    }

    return cnt < k;
}

int bs()
{
    int ans = 0, l = le, r = ri, mid;
    while (l <= r)
    {
        mid = l + ((r - l) >> 1);
        if (check(mid))
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
    while (n--)
    {
        le = 0, ri = 0;

        cin >> m >> k;
        for (int i = 1; i <= m; i++)
        {
            cin >> arr[i];

            le = max(le, arr[i]);
            ri += arr[i];
        }

        res = bs();
        for (int i = m, j = k, sum = 0; i >= 1; i--)
        {
            if (sum + arr[i] > res || j - 1 == i)
            {
                sum = arr[i];
                sp[--j] = i;
            }
            else
            {
                sum += arr[i];
            }
        }

        for (int i = 1, j = 1; i <= m; i++)
        {
            cout << arr[i] << " \n"[i == m];
            if (j < k && sp[j] == i)
            {
                cout << "/ ";
                j++;
            }
        }
    }
}