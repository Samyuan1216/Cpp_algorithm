#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXN = 100010;
int n, m;

namespace BIT
{
    vi tree(MAXN);

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(int i)
    {
        while (i <= n)
        {
            tree[i] = (tree[i] + 1) & 1;
            i += lowbit(i);
        }
    }

    void add(int l, int r)
    {
        add(l);
        add(r + 1);
    }

    int query(int i)
    {
        int ans = 0;
        while (i > 0)
        {
            ans = (ans + tree[i]) & 1;
            i -= lowbit(i);
        }

        return ans;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1, x, a, b; i <= m; i++)
    {
        cin >> x;
        if (x == 1)
        {
            cin >> a >> b;
            BIT::add(a, b);
        }
        else
        {
            cin >> a;
            cout << BIT::query(a) << endl;
        }
    }
}