#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 500010;
int n, m;

namespace BIT
{
    vi tree(MAXN);

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(int i, int v)
    {
        while (i <= n)
        {
            tree[i] += v;
            i += lowbit(i);
        }
    }

    int query(int i)
    {
        int ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;

        BIT::add(i, x);
        BIT::add(i + 1, -x);
    }

    for (int i = 1, a, x, y, k; i <= m; i++)
    {
        cin >> a;
        if (a == 1)
        {
            cin >> x >> y >> k;
            
            BIT::add(x, k);
            BIT::add(y + 1, -k);
        }
        else
        {
            cin >> x;
            cout << BIT::query(x) << endl;
        }
    }
}