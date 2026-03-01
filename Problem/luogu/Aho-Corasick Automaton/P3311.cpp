#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using v4i = vector<vvvi>;

const int MAXN = 1310, MAXL = 2010, MOD = 1000000007;

namespace AC
{
    vvi tree(MAXL, vi(10));
    vi fail(MAXL), box(MAXL);
    bool alert[MAXL];
    int cnt;

    void insert(string &str)
    {
        int u = 0;
        for (int i = 0, cur; i < str.length(); i++)
        {
            cur = str[i] - '0';
            if (tree[u][cur] == 0)
            {
                tree[u][cur] = ++cnt;
            }

            u = tree[u][cur];
        }

        alert[u] = true;
    }

    void set_fail()
    {
        int l = 0, r = 0;
        for (int i = 0; i < 10; i++)
        {
            if (tree[0][i] > 0)
            {
                box[r++] = tree[0][i];
            }
        }

        while (l < r)
        {
            int u = box[l++];
            for (int i = 0; i < 10; i++)
            {
                if (tree[u][i])
                {
                    fail[tree[u][i]] = tree[fail[u]][i];
                    box[r++] = tree[u][i];
                }
                else
                {
                    tree[u][i] = tree[fail[u]][i];
                }
            }

            alert[u] |= alert[fail[u]];
        }
    }
}

v4i dp(MAXN, vvvi(MAXL, vvi(2, vi(2, -1))));
string n, s;
int m;

int dfs(int i, int j, int free, int has)
{
    if (AC::alert[j])
    {
        return 0;
    }

    if (i == n.length())
    {
        return has;
    }

    if (dp[i][j][free][has] != -1)
    {
        return dp[i][j][free][has];
    }

    int ans = 0, cur = n[i] - '0';
    if (free == 0)
    {
        if (has == 0)
        {
            ans = dfs(i + 1, j, 1, 0);
            for (int pick = 1; pick < cur; pick++)
            {
                ans = (ans + dfs(i + 1, AC::tree[j][pick], 1, 1)) % MOD;
            }
            ans = (ans + dfs(i + 1, AC::tree[j][cur], 0, 1)) % MOD;
        }
        else
        {
            for (int pick = 0; pick < cur; pick++)
            {
                ans = (ans + dfs(i + 1, AC::tree[j][pick], 1, 1)) % MOD;
            }
            ans = (ans + dfs(i + 1, AC::tree[j][cur], 0, 1)) % MOD;
        }
    }
    else
    {
        if (has == 0)
        {
            ans = dfs(i + 1, j, 1, 0);
            for (int pick = 1; pick < 10; pick++)
            {
                ans = (ans + dfs(i + 1, AC::tree[j][pick], 1, 1)) % MOD;
            }
        }
        else
        {
            for (int pick = 0; pick < 10; pick++)
            {
                ans = (ans + dfs(i + 1, AC::tree[j][pick], 1, 1)) % MOD;
            }
        }
    }

    dp[i][j][free][has] = ans;
    return ans;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        AC::insert(s);
    }
    AC::set_fail();

    cout << dfs(0, 0, 0, 0) << endl;
}