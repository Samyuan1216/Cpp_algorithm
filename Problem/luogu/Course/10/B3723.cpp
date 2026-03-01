#include <iostream>
#include <set>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    multiset<unsigned long long> coins;
    while (n--)
    {
        unsigned long long coin;
        cin >> coin;

        coins.insert(coin);
    }

    unsigned long long p1 = 0, p2 = 0;
    auto select = [&](unsigned long long &sum)
    {
        auto iter = coins.upper_bound(sum);
        if (iter != coins.begin())
        {
            iter--;
        }

        sum += *iter;
        coins.erase(iter);
    };

    while (coins.empty() == false)
    {
        select(p1);
        if (coins.empty() == true)
        {
            break;
        }

        select(p2);
    }

    cout << p1 << " " << p2 << endl;
}