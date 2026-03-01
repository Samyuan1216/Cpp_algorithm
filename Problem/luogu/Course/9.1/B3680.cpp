#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    vector<tuple<string, string, long long>> characters(n + m);
    for (auto &[name, r, num]: characters)
    {
        cin >> name >> r >> num;
    }

    sort(characters.begin(), characters.end(), [](tuple<string, string, long long> &a, tuple<string, string, long long> &b)
    {
        auto &[_, ra, numa] = a;
        auto &[__, rb, numb] = b;

        if (ra != rb)
        {
            return (ra == "H"? true: false);
        }

        return numa > numb;
    });

    cout << get<0>(characters[2]) << endl;

    for (int i = m + 5; i < m + 9; i++)
    {
        cout << get<0>(characters[i]) << endl;
    }
}