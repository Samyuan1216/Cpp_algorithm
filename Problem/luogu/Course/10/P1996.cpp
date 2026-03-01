#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }

    while (q.empty() == false)
    {
        for (int i = 1; i < m; i++)
        {
            int temp = q.front();
            q.pop();
            q.push(temp);
        }

        cout << q.front() << " ";
        q.pop();
    }
}