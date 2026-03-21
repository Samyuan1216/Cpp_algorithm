#include <bits/stdc++.h>

const int MAXN = 100010;
double help1[MAXN], dp1[MAXN][2];
int arr[MAXN], sorted[MAXN], help2[MAXN], dp2[MAXN][2];
int n;

bool check1(double x)
{
    for (int i = 1; i <= n; i++)
    {
        help1[i] = (double)arr[i] - x;
    }

    for (int i = n; i >= 1; i--)
    {
        dp1[i][0] = std::max(help1[i] + dp1[i + 1][0], dp1[i + 1][1]);
        dp1[i][1] = help1[i] + dp1[i + 1][0];
    }

    return dp1[1][0] >= 0;
}

double average()
{
    double l, r, mid;
    l = (double)*std::min_element(arr + 1, arr + n + 1);
    r = (double)*std::max_element(arr + 1, arr + n + 1);

    for (int i = 1; i <= 60; i++)
    {
        mid = l + ((r - l) / 2);
        if (check1(mid))
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }

    return l;
}

bool check2(int x)
{
    for (int i = 1; i <= n; i++)
    {
        help2[i] = (arr[i] < x? -1: 1);
    }

    for (int i = n; i >= 1; i--)
    {
        dp2[i][0] = std::max(help2[i] + dp2[i + 1][0], dp2[i + 1][1]);
        dp2[i][1] = help2[i] + dp2[i + 1][0];
    }

    return dp2[1][0] > 0;
}

int median()
{
    for (int i = 1; i <= n; i++)
    {
        sorted[i] = arr[i];
    }

    std::sort(sorted + 1, sorted + n + 1);

    int ans = 0, l = 1, r = n, mid;
    while (l <= r)
    {
        mid = l + ((r - l) / 2);
        if (check2(sorted[mid]))
        {
            ans = sorted[mid];
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
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
    {
        std::cin >> arr[i];
    }

    std::cout << average() << std::endl;
    std::cout << median() << std::endl;
}