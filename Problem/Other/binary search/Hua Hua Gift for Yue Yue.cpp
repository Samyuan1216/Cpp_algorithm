// https://www.nowcoder.com/share/jump/1961392931767359389351

#include <bits/stdc++.h>

using vi = std::vector<int>;

const int MAXN = 200010;
vi arr(MAXN);
int n, k, maxn;

bool check(int x)
{
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += arr[i] / x;
    }

    return ans >= k;
}

int find()
{
    int ans = 0, l = 1, r = maxn, mid;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
        maxn = std::max(maxn, arr[i]);
    }

    std::cout << find() << "\n";
}