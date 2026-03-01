#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAXN = 1010;
vvi diff(MAXN, vi(2));
double ans;
int n, sum;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> diff[i][0];
        diff[i][1] = i + 1;
    }

    sort(diff.begin(), diff.begin() + n, [](vi &a, vi&b)
    {
        return a[0] < b[0];
    });

    for (int i = 0; i < n; i++)
    {
        cout << diff[i][1] << " \n"[i == n - 1];
    }

    for (int i = 0; i < n - 1; i++)
    {
        sum += diff[i][0];
        ans += sum;
    }

    printf("%.2f\n", ans / n);
}