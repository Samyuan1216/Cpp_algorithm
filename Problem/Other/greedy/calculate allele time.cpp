#include <bits/stdc++.h>
using namespace std;

int waiting_time1(vector<int> &arr, int m)
{
    struct compare
    {
        bool operator()(vector<int> &a, vector<int> &b)
        {
            return a[0] > b[0];
        }
    };

    priority_queue<vector<int>, vector<vector<int>>, compare> heap;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        heap.push(vector<int>{0, arr[i]});
    }

    for (int i = 0; i < m; i++)
    {
        vector<int> cur = heap.top();
        heap.pop();

        cur[0] += cur[1];
        heap.push(cur);
    }

    return heap.top()[0];
}

int f(vector<int> &arr, int m)
{
    int ans = 0;
    for (auto &x: arr)
    {
        ans += m / x + 1;
    }

    return ans;
}

int waitting_time2(vector<int> &arr, int m)
{
    int minn = *min_element(arr.begin(), arr.end());

    int ans = 0;
    for (int l = 0, r = minn * m, w = 0; l <= r;)
    {
        w = l + ((r - l) >> 1);
        if (f(arr, w) >= m + 1)
        {
            ans = w;
            r = w - 1;
        }
        else
        {
            l = w + 1;
        }
    }

    return ans;
}

random_device rd;
mt19937 gen(rd());
uniform_real_distribution dis(0.0, 1.0);

vector<int> random_array(int n, int V)
{
    vector<int> arr(n);
    for (auto &x: arr)
    {
        x = (int)(dis(gen) * V) + 1;
    }

    return arr;
}

int main()
{
    cout << "测试开始" << endl;

    int N = 50, V = 30, M = 3000, test_time = 2000;
    for (int i = 0; i < test_time; i++)
    {
        int n = (int)(dis(gen) * N) + 1;
        vector<int> arr = random_array(n, V);

        int m = (int)(dis(gen) * M);
        int ans1 = waiting_time1(arr, m);
        int ans2 = waitting_time2(arr, m);

        if (ans1 != ans2)
        {
            cout << "出错了" << endl;

            cout << ans1 << " " << ans2 << endl;

            cout << "arr: [ ";
            for (auto &x: arr)
            {
                cout << x << " ";
            }
            cout << "]" << endl;

            cout << "m: " << m << endl;
            break;
        }
    }

    cout << "测试结束" << endl;
}