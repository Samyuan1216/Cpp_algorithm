#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
vector<int> nums(MAXN), dp(MAXN);
int n;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    sort(nums.begin(), nums.begin() + n);

    dp[0] = nums[0];
    dp[1] = nums[1];
    dp[2] = nums[0] + nums[1] + nums[2];
    for (int i = 3; i < n; i++)
    {
        dp[i] = min(nums[0] + nums[i] + dp[i - 1], nums[1] + nums[1] + nums[i] + nums[0] + dp[i - 2]);
    }

    cout << dp[n - 1] << endl;
}