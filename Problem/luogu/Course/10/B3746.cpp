#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    vector<vector<int>> ans(n);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    for (int i = 0; i < n; i++)
    {
        pq.emplace(0, i);
    }

    for (int i = 1; i <= m; i++)
    {
        int time = 0;
        cin >> time;

        auto p = pq.top();
        pq.pop();
        ans[p.second].push_back(i);
        pq.emplace(time + p.first, p.second);
    }

    for (auto &line: ans)
    {
        if (line.size() == 0)
        {
            cout << "0" << endl;
            continue;
        }

        for (auto &x: line)
        {
            cout << x << " ";
        }

        cout << endl;
    }
}