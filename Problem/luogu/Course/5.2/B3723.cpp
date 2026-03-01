#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    vector<long long> coin(n);
    for (auto &x: coin)
    {
        cin >> x;
    }

    sort(coin.begin(), coin.end());

    vector<long long> Farmer, Bessie;

    long long sumF = 0, sumB = 0;
    while (coin.empty() == false)
    {
        int index = -1;
        for (auto &x: coin)
        {
            if (sumF < x)
            {
                break;
            }

            index++;
        }

        if (index == -1)
        {
            sumF += coin[0];
            Farmer.push_back(coin[0]);
            coin.erase(coin.begin());
        }
        else
        {
            sumF += coin[index];
            Farmer.push_back(coin[index]);
            coin.erase(coin.begin() + index);
        }

        if (coin.empty() == true)
        {
            break;
        }

        index = -1;
        for (auto &x: coin)
        {
            if (sumB < x)
            {
                break;
            }

            index++;
        }

        if (index == -1)
        {
            sumB += coin[0];
            Bessie.push_back(coin[0]);
            coin.erase(coin.begin());
        }
        else
        {
            sumB += coin[index];
            Bessie.push_back(coin[index]);
            coin.erase(coin.begin() + index);
        }
    }

    cout << sumF << " " << sumB << endl;
}