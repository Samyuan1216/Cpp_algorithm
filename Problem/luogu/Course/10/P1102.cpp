#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    int N = 0, C = 0;
    cin >> N >> C;

    unordered_map<int, int> um;

    long long cnt = 0;
    while (N--)
    {
        int x = 0;
        cin >> x;

        cnt += um[x + C];
        cnt += um[x - C];
        um[x]++;
    }

    cout << cnt << endl;
}