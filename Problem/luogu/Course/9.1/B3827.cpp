#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, k = 0;
    cin >> n >> k;

    vector<pair<int, int>> question(n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int x = 0;
            cin >> x;

            question[i - 1].first += x;
        }

        question[i - 1].second = i;
    }

    sort(question.begin(), question.end(), [](pair<int, int> &a, pair<int, int> &b)
    {
        if (a.first == b.first)
        {
            return a.second < b.second;
        }

        return a.first > b.first;
    });

    cout << question[0].second << endl;
    cout << question[1].second << endl;
}