#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using umii = unordered_map<int, int>;

const int MAXN = 1000010;
vvi qu(MAXN, vi(3));
vi diff(MAXN), ans(MAXN);
umii mp;
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

bool compare(vi &a, vi &b)
{
    return a[1] < b[1];
}

template<typename T> inline T read()
{
    T x = 0, f = 1;
    char ch = '\0';

    for (; isdigit(ch) == 0; ch = getchar())
    {
        if (ch == '-')
        {
            f = -1;
        }
    }

    for (; isdigit(ch) != 0; ch = getchar())
    {
        x = (x << 3) + (x << 1) + (ch - '0');
    }

    return x * f;
}

template<typename T> inline void write(T x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }

    static int sta[40] = {};
    int top = 0;

    do
    {
        sta[top++] = x % 10;
        x /= 10;
    } while (x > 0);
    
    while (top > 0)
    {
        putchar(sta[--top] + '0');
    }
    putchar('\n');
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    n = read<int>();
    for (int i = 1; i <= n; i++)
    {
        diff[i] = read<int>();
    }

    m = read<int>();
    for (int i = 1; i <= m; i++)
    {
        qu[i][0] = read<int>();
        qu[i][1] = read<int>();
        qu[i][2] = i;
    }

    sort(qu.begin() + 1, qu.begin() + m + 1, compare);

    for (int s = 1, q = 1, l, r, i; q <= m; q++)
    {
        r = qu[q][1];
        for (; s <= r; s++)
        {
            int color = diff[s];
            if (mp[color] != 0)
            {
                BIT::add(mp[color], -1);
            }

            BIT::add(s, 1);
            mp[color] = s;
        }

        l = qu[q][0];
        i = qu[q][2];
        ans[i] = BIT::query(l, r);
    }

    for (int i = 1; i <= m; i++)
    {
        write<int>(ans[i]);
    }
}