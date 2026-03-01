#include <iostream>
using namespace std;

int main()
{
    int N = 0;
    cin >> N;

    bool a[N] = {};
    for (int i = 2; i <= N; i++)
    {
        for (int j = i; j <= N; j += i)
        {
            a[j - 1] = !a[j - 1];
        }
    }

    for (int i = 0; i < N; i++)
    {
        if (a[i] == false)
        {
            cout << i + 1 << " ";
        }
    }
}