#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    int N = 0;
    cin >> N;

    vector<pair<int, string>> stu(N);
    for (auto &[score, name]: stu)
    {
        cin >> score >> name;
    }

    sort(stu.begin(), stu.end());
    cout << stu[N - 1].second << endl;
}