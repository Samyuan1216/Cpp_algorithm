#include <bits/stdc++.h>

using ll = long long;
using vll = std::vector<ll>;

const int MAXN = 55, BIT = 50;
vll arr(MAXN), basis(BIT + 1);
ll ans, x;
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
        std::cin >> x;

        insert(x);
    }

    for (int i = BIT; i >= 0; i--)
    {
        ans = std::max(ans, ans ^ basis[i]);
    }

    std::cout << ans << "\n";
}