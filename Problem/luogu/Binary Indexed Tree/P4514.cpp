#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 2050;
int n, m, a, b, c, d, delta;
string op;

namespace BIT
{
    vvi info1(MAXN, vi(MAXN)), info2(MAXN, vi(MAXN)), info3(MAXN, vi(MAXN)), info4(MAXN, vi(MAXN));

    int lowbit(int i)
    {
        return i & -i;
    }

    void add(int x, int y, int v)
    {
        int v1 = v, v2 = v * x, v3 = v * y, v4 = v * x * y;
        for (int i = x; i <= n; i += lowbit(i))
        {
            for (int j = y; j <= m; j += lowbit(j))
            {
                info1[i][j] += v1;
                info2[i][j] += v2;
                info3[i][j] += v3;
                info4[i][j] += v4;
            }
        }
    }

    void add(int a, int b, int c, int d, int v)
    {
        add(a, b, v);
        add(a, d + 1, -v);
        add(c + 1, b, -v);
        add(c + 1, d + 1, v);
    }

    int sum(int x, int y)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
        {
            for (int j = y; j > 0; j -= lowbit(j))
            {
                ans += (x + 1) * (y + 1) * info1[i][j] - (y + 1) * info2[i][j] - (x + 1) * info3[i][j] + info4[i][j];
            }
        }

        return ans;
    }

    int query(int a, int b, int c, int d)
    {
        return sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
    }
}

int main()
{
    cin >> op >> n >> m;
    while (cin >> op >> a >> b >> c >> d)
    {
        if (op == "L")
        {
            cin >> delta;
            BIT::add(a, b, c, d, delta);
        }
        else
        {
            cout << BIT::query(a, b, c, d) << endl;
        }
    }
}