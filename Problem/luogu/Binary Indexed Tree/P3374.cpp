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

    int sum(int i)
    {
        int ans = 0;
        while (i > 0)
        {
            ans += tree[i];
            i -= lowbit(i);
        }

        return ans;
    }

    int query(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        BIT::add(i, x);
    }

    for (int i = 1, a, b, c; i <= m; i++)
    {
        cin >> a >> b >> c;
        if (a == 1)
        {
            BIT::add(b, c);
        }
        else
        {
            cout << BIT::query(b, c) << endl;
        }
    }
}