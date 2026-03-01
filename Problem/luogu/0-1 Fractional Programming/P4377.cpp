#include <bits/stdc++.h>

using vi = std::vector<int>;
using vd = std::vector<double>;

const int MAXN = 260, MAXW = 1010;
const double NA = -1e9, SML = 1e-6;
vi weight(MAXN), talent(MAXN);
vd value(MAXN), dp(MAXW);
double limit;
int n, w;

bool check(double x)
{
    for (int i = 1; i <= n; i++)
    {
        value[i] = (double)talent[i] - x * weight[i];
    }

    dp[0] = 0;
    std::fill(dp.begin() + 1, dp.begin() + w + 1, NA);

    for (int i = 1; i <= n; i++)
    {
        for (int p = w, j; p >= 0; p--)
        {
            j = std::min(int(p + weight[i]), w);
            dp[j] = std::max(dp[j], dp[p] + value[i]);
        }
    }

    return dp[w] >= 0;
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

    std::cin >> n >> w;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> weight[i] >> talent[i];

        limit += talent[i];
    }

    std::cout << int(find() * 1000) << "\n";
}