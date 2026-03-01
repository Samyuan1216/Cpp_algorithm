#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

// 暴力方法
// 为了验证
int len1(const vi& arr)
{
    unordered_map<int, unordered_map<int, int>> map;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        int zero = 0;
        int one = 0;
        for (int j = i; j < n; j++)
        {
            zero += arr[j] == 0 ? 1 : 0;
            one += arr[j] == 1 ? 1 : 0;
            map[zero][one]++;
        }
    }
    int ans = 0;
    for (const auto& zeros : map)
    {
        for (const auto& ones : zeros.second)
        {
            int num = ones.second;
            if (num > 1)
            {
                ans = max(ans, zeros.first + ones.first);
            }
        }
    }
    return ans;
}

// 正式方法
// 时间复杂度 O(n)
int len2(const vi& arr)
{
    int leftZero = -1, rightZero = -1;
    int leftOne = -1, rightOne = -1;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            leftZero = i;
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 1)
        {
            leftOne = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] == 0)
        {
            rightZero = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] == 1)
        {
            rightOne = i;
            break;
        }
    }
    int p1 = rightZero - leftZero;
    int p2 = rightOne - leftOne;
    return max(p1, p2);
}

// 为了验证
vi randomArray(int len)
{
    vi ans(len);
    for (int i = 0; i < len; i++)
    {
        ans[i] = rand() % 2;
    }
    return ans;
}

int main()
{
    int N = 250;
    int testTimes = 2000;
    cout << "测试开始" << endl;
    for (int i = 1; i <= testTimes; i++)
    {
        int n = rand() % N + 2;
        vi arr = randomArray(n);
        int ans1 = len1(arr);
        int ans2 = len2(arr);
        if (ans1 != ans2)
        {
            cout << "出错了!" << endl;
        }
        if (i % 100 == 0)
        {
            cout << "测试到第" << i << "组" << endl;
        }
    }
    cout << "测试结束" << endl;
    return 0;
}
