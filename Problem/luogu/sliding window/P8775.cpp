#include <bits/stdc++.h>

using ll = long long;

const int MAXN = 100010;
int arr[MAXN];
int n, x, ans;
ll sum;

int main()
{
    std::cin >> n >> x;
    for (int i = 1; i < n; i++)
    {
        std::cin >> arr[i];
    }

    arr[n] = 2 * x;
    
    sum = arr[1];
    for (int l = 1, r = 2; l <= n; l++)
    {
        while (sum < 2 * x)
        {
            sum += arr[r++];
        }

        ans = std::max(ans, r - l);
        sum -= arr[l];
    }

    std::cout << ans << std::endl;
}