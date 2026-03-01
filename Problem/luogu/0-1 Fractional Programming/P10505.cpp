#include <bits/stdc++.h>

using vd = std::vector<double>;
using v2d = std::vector<vd>;

const int MAXN = 1010;
const double SML = 1e-6;
v2d arr(MAXN, vd(3));
int n, k;
double limit;

bool check(double x)
{
    for (int i = 1; i <= n; i++)
    {
        arr[i][2] = arr[i][0] - x * arr[i][1];
    }

    std::sort(arr.begin() + 1, arr.begin() + n + 1, [](vd &a, vd &b)
    {
        return a[2] > b[2];
    });

    double sum = 0;
    for (int i = 1; i <= k; i++)
    {
        sum += arr[i][2];
    }

    return sum >= 0;
}

double find()
{
    double ans = 0, l = 0, r = limit, mid;
    while (l < r && r - l >= SML)
    {
        mid = l + (r - l) / 2;
        if (check(mid))
        {
            ans = mid;
            l = mid + SML;
        }
        else
        {
            r = mid - SML;
        }
    }

    return ans;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    while (n != 0 || k != 0)
    {
        k = n - k;
        limit = 0;

        for (int i = 1; i <= n; i++)
        {
            std::cin >> arr[i][0];

            limit += arr[i][0];
        }

        for (int i = 1; i <= n; i++)
        {
            std::cin >> arr[i][1];
        }

        std::cout << int(100 * (find() + 0.005)) << "\n";

        std::cin >> n >> k;
    }
}