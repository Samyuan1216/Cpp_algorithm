#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vc = vector<char>;

const int MAXN = 1000010, MOD = 19930726;
vi p(MAXN << 1), cnt(MAXN);
vc ss(MAXN << 1);
string s;
ll n, m, k;

void manacherss()
{
    n = 2 * m + 1;
    for (int i = 0, j = 0; i < n; i++)
    {
        ss[i] = (i & 1? s[j++]: '#');
    }
}

void manacher()
{
    manacherss();
    for (int i = 0, c = 0, r = 0, len; i < n; i++)
    {
        len = (i < r? min(r - i, p[2 * c - i]): 1);
        while (i + len < n && i - len >= 0 && ss[i + len] == ss[i - len])
        {
            len++;
        }

        if (i + len > r)
        {
            r = i + len;
            c = i;
        }

        p[i] = len;
    }
}

ll power(ll x, ll n)
{
    ll ans = 1;
    while (n > 0)
    {
        if (n & 1)
        {
            ans = (ans * x) % MOD;
        }

        x = (x * x) % MOD;
        n >>= 1;
    }

    return ans;
}

int main()
{
    cin >> m >> k >> s;
    manacher();

    for (int i = 1; i < n; i += 2)
    {
        cnt[p[i] - 1]++;
    }

    ll ans = 1, sum = 0;
    for (int len = (m & 1? m: m - 1); len >= 1 && k > 0; len -= 2)
    {
        sum += cnt[len];
        ans = (ans * power(len, min(k, sum))) % MOD;
        k -= sum;
    }

    cout << (k > 0? -1: ans) << endl;
}