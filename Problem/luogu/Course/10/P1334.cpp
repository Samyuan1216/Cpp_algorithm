#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    while (n--)
    {
        int x = 0;
        cin >> x;

        pq.push(x);
    }

    long long sum = 0;
    while (pq.empty() == false)
    {
        long long x = pq.top();
        pq.pop();

        if (pq.empty() == true)
        {
            break;
        }

        long long y = pq.top();
        pq.pop();

        sum += x + y;
        pq.push(x + y);
    }

    cout << sum << endl;
}