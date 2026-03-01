#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> pq;
    while (n--)
    {
        int index = 0;
        cin >> index;

        if (index == 1)
        {
            int x = 0;
            cin >> x;

            pq.push(x);
        }
        else if (index == 2)
        {
            cout << pq.top() << endl;
        }
        else if (index == 3)
        {
            pq.pop();
        }
    }
}