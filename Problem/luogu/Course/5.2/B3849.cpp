#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N = 0, R = 0;
    cin >> N >> R;

    vector<int> digits;
    while (N > 0)
    {
        digits.push_back(N % R);
        N /= R;
    }

    reverse(digits.begin(), digits.end());

    for (auto &d: digits)
    {
        if (d < 10)
        {
            cout << d;
        }
        else
        {
            cout << char((d - 10) + 'A');
        }
    }
}