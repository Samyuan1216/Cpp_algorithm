#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 1000010;
vi latest(MAXN, -1);
int n, s, e, ans;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s >> e;
        
        if (latest[e] == -1)
        {
            latest[e] = s;
        }
        else
        {
            latest[e] = max(latest[e], s);
        }
    }

    for (int cur = 0, ed = 0; ed < MAXN; ed++)
    {
        if (cur <= latest[ed])
        {
            ans++;
            cur = ed;
        }
    }

    cout << ans << endl;
}