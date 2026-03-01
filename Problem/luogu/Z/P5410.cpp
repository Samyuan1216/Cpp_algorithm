#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 20000010;
vi z(MAXN), e(MAXN);
string a, b;
long long ans;

void z_array()
{
    z[0] = b.length();
    for (int i = 1, r = 0, c = 0, len; i < b.length(); i++)
    {
        len = (i < r? min(r - i, z[i - c]): 0);
        while (i + len < b.length() && b[i + len] == b[len])
        {
            len++;
        }

        if (i + len > r)
        {
            r = i + len;
            c = i;
        }

        z[i] = len;
    }
}

void e_array()
{
    for (int i = 0, r = 0, c = 0, len; i < a.length(); i++)
    {
        len = (i < r? min(r - i, z[i - c]): 0);
        while (i + len < a.length() && len < b.length() && a[i + len] == b[len])
        {
            len++;
        }

        if (i + len > r)
        {
            r = i + len;
            c = i;
        }

        e[i] = len;
    }
}

int main()
{
    cin >> a >> b;
    
    z_array();
    for (int i = 0; i < b.length(); i++)
    {
        ans ^= ((long long)z[i] + 1) * (i + 1);
    }
    cout << ans << endl;

    ans = 0;
    e_array();
    for (int i = 0; i < a.length(); i++)
    {
        ans ^= ((long long)e[i] + 1) * (i + 1);
    }
    cout << ans << endl;
}