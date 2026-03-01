#include <bits/stdc++.h>

using ll = long long;
using vll = std::vector<ll>;

const int MAXN = 55, MOD = 2008;
vll arr(MAXN), basis(MAXN);
std::string s;
int n, m;

bool insert(ll num)
{
    for (int i = MAXN; i >= 0; i--)
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

    std::cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        std::cin >> s;
        for (int j = 0; j < n; j++)
        {
            if (s[j] == 'O')
            {
                arr[i] |= 1ll << j;
            }
        }
    }

    int size = 0;
    for (int i = 1; i <= m; i++)
    {
        if (insert(arr[i]))
        {
            size++;
        }
    }

    std::cout << (1ll << size) % MOD << "\n";
}