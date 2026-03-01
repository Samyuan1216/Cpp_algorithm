#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    vector<int> cp(n);
    for (auto &x: cp)
    {
        cin >> x;
    }

    vector<priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>> task(n);
    while (m--)
    {
        int a = 0, b = 0, c = 0, d = 0;
        cin >> a >> b >> c >> d;

        while (task[b - 1].empty() == false && task[b - 1].top().first <= a)
        {
            cp[b - 1] += task[b - 1].top().second;
            task[b - 1].pop();
        }

        if (d <= cp[b - 1])
        {
            pair<int, int> temp(a + c, d);
            task[b - 1].push(temp);
            cp[b - 1] -= d;

            cout << cp[b - 1] << endl;
        }
        else
        {
            cout << "-1" << endl;
        }
    }
}