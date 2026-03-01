#include <bits/stdc++.h>
using namespace std;

priority_queue<int, vector<int>, greater<int>> heap;
int n, x, ans;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        heap.push(x);
    }

    while (heap.size() > 1)
    {
        x = heap.top();
        heap.pop();

        x += heap.top();
        heap.pop();

        ans += x;
        heap.push(x);
    }

    cout << ans << endl;
}