#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 100010;
ll sum[MAXN], dp[MAXN];
int arr[MAXN], q[MAXN];
int n, k, l, r;

ll value(int i)
{
    return (i == 0? 0: (dp[i - 1] - sum[i]));
}

void add(int i)
{
    while (l < r && value(q[r - 1]) <= value(i))
    {
        r--;
    }

    q[r++] = i;
}

void del(int i)
{
    if (l < r && q[l] == i)
    {
        l++;
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];

        sum[i] = sum[i - 1] + arr[i];
    }

    q[r++] = 0;
    for (int i = 1; i <= n; i++)
    {
        add(i);
        del(i - k - 1);

        dp[i] = value(q[l]) + sum[i];
    }

    std::cout << dp[n] << "\n";
}