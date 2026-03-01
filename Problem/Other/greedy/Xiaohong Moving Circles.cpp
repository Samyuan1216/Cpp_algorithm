// https://www.nowcoder.com/share/jump/1961392931766759502604

#include <bits/stdc++.h>

using vd = std::vector<double>;

const int MAXN = 100010;
const double PI = std::acos(-1);
vd arr(MAXN);
int n, k, num;
double ans;

double dist(int x, int y)
{
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::cin >> n >> k;
    for (int i = 1, x, y, r; i <= n; i++)
    {
        std::cin >> x >> y >> r;

        double dis = dist(x, y);
        if (dis < r)
        {
            arr[num++] = (std::pow(r, 2) * PI) * (r - dis);
        }
    }

    std::sort(arr.begin(), arr.begin() + num);

    for (int i = 0; i < num - k; i++)
    {
        ans += arr[i];
    }

    std::cout << std::fixed << std::setprecision(16) << ans << "\n";
}