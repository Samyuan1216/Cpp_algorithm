#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
vi mp(MAXN), eds(MAXN), p1(MAXN), p2(MAXN);
int n, len = -1;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p1[i];
        mp[p1[i]] = i;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> p2[i];
        p2[i] = mp[p2[i]];
    }

    for (int i = 0; i < n; i++)
    {
        if (len == -1 || p2[i] > eds[len])
        {
            eds[++len] = p2[i];
        }
        else
        {
            int ans = len;
            for (int l = 0, r = len - 1, m; l <= r;)
            {
                m = l + ((r - l) >> 1);
                if (p2[i] <= eds[m])
                {
                    ans = m;
                    r = m - 1;
                }
                else
                {
                    l = m + 1;
                }
            }

            eds[ans] = p2[i];
        }
    }

    cout << len + 1 << endl;
}