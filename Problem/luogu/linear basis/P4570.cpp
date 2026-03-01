#include <bits/stdc++.h>

using ll = long long;
using vll = std::vector<ll>;
using v2ll = std::vector<vll>;

const int MAXN = 1010, BIT = 60;
v2ll arr(MAXN, vll(2));
vll basis(BIT + 1);
int n;

bool insert(ll num)
{
    for (int i = BIT; i >= 0; i--)
    {
        if (num >> i == 1)
        {
            if (basis[i] == 0)
            {
                basis[i] = num;
                return true;
            }

            num ^= basis[i];
        }
    }

    return false;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i][0] >> arr[i][1];
    }

    std::sort(arr.begin() + 1, arr.begin() + n + 1, [](vll &a, vll &b)
    {
        return a[1] > b[1];
    });

    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (insert(arr[i][0]))
        {
            ans += arr[i][1];
        }
    }

    std::cout << ans << "\n";
}