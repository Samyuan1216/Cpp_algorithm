#include <bits/stdc++.h>

using ll = long long;
using vll = std::vector<ll>;

const int MAXN = 100010, BIT = 50;
vll arr(MAXN);
int n, m, len;
bool zero;

void basis()
{
    len = 1;
    for (int i = BIT; i >= 0; i--)
    {
        for (int j = len; j <= n; j++)
        {
            if ((arr[j] & (1ll << i)) != 0)
            {
                std::swap(arr[j], arr[len]);
                break;
            }
        }

        if ((arr[len] & (1ll << i)) != 0)
        {
            for (int j = 1; j <= n; j++)
            {
                if (j != len && (arr[j] & (1ll << i)) != 0)
                {
                    arr[j] ^= arr[len];
                }
            }

            len++;
        }
    }

    len--;
    zero = (len != n);
}

ll query(ll k)
{
    if (zero && k == 1)
    {
        return 0;
    }

    if (zero)
    {
        k--;
    }

    if (k >= (1ll << len))
    {
        return -1;
    }

    ll ans = 0;
    for (int i = len, j = 0; i >= 1; i--, j++)
    {
        if ((k & (1ll << j)) != 0)
        {
            ans ^= arr[i];
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    basis();

    std::cin >> m;
    for (int i = 1; i <= m; i++)
    {
        ll k;
        std::cin >> k;
        std::cout << query(k) << "\n";
    }
}