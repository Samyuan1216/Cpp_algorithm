#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 21, MAXV = 101;
vi nums(MAXN), sg(MAXN);
bool appear[MAXV];
int t, n;

void build()
{
    for (int i = 1; i < MAXN; i++)
    {
        fill(appear, appear + MAXV, false);
        for (int j = i - 1; j >= 0; j--)
        {
            for (int k = j; k >= 0; k--)
            {
                appear[sg[j] ^ sg[k]] = true;
            }
        }

        for (int s = 0; s < MAXV; s++)
        {
            if (!appear[s])
            {
                sg[i] = s;
                break;
            }
        }
    }
}

void solve()
{
    cin >> n;
    for (int i = n - 1; i >= 0; i--)
    {
        cin >> nums[i];
    }

    int eor = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] & 1)
        {
            eor ^= sg[i];
        }
    }

    if (!eor)
    {
        cout << "-1 -1 -1" << endl;
        cout << "0" << endl;

        return;
    }

    int cnt = 0, a = -1, b = -1, c = -1, pos;
    for (int i = n - 1; i >= 1; i--)
    {
        if (nums[i])
        {
            for (int j = i - 1; j >= 0; j--)
            {
                for (int k = j; k >= 0; k--)
                {
                    pos = eor ^ sg[i] ^ sg[j] ^ sg[k];
                    if (!pos)
                    {
                        cnt++;
                        if (a == -1)
                        {
                            a = i;
                            b = j;
                            c = k;
                        }
                    }
                }
            }
        }
    }

    cout << n - a - 1 << " " << n - b - 1 << " " << n - c - 1 << endl;
    cout << cnt << endl;
}

int main()
{
    build();

    cin >> t;
    while (t--)
    {
        solve();
    }
}