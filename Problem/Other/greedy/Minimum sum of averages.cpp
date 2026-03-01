#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

int f(vi &arr, int i, vi &sum, vi &cnt)
{
    if (i == arr.size())
    {
        int ans = 0;
        for (int j = 0; j < sum.size(); j++)
        {
            if (cnt[j] == 0) {
                return INT32_MAX;
            }
            ans += sum[j] / cnt[j];
        }
        return ans;
    }
    else
    {
        int ans = INT32_MAX;
        for (int j = 0; j < sum.size(); j++)
        {
            sum[j] += arr[i];
            cnt[j]++;
            ans = min(ans, f(arr, i + 1, sum, cnt));
            sum[j] -= arr[i];
            cnt[j]--;
        }
        return ans;
    }
}

int minAverageSum1(vi &arr, int k)
{
    vi sum(k);
    vi cnt(k);
    return f(arr, 0, sum, cnt);
}

int min_average_sum2(vi &arr, int k)
{
    sort(arr.begin(), arr.end());

    int ans = 0;
    for (int i = 0; i < k - 1; i++)
    {
        ans += arr[i];
    }

    int sum = 0;
    for (int i = k - 1; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    ans += sum / (arr.size() - k + 1);
    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution dis(0.0, 1.0);

vi random_array(int n, int v)
{
    vi arr(n);
    for (auto &x: arr)
    {
        x = dis(gen) * v;
    }
    
    return arr;
}

int main()
{
    int N = 8;
    int V = 10000;
    int testTimes = 2000;
    cout << "测试开始" << endl;
    for (int i = 1; i <= testTimes; i++)
    {
        int n = (int) (dis(gen) * N) + 1;
        vi arr = random_array(n, V);
        int k = (int) (dis(gen) * n) + 1;
        int ans1 = minAverageSum1(arr, k);
        int ans2 = min_average_sum2(arr, k);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
            break;
        }
    }
    cout << "测试结束" << endl;
}