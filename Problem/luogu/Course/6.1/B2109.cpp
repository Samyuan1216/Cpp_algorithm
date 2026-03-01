#include <iostream>
using namespace std;

int main()
{
    char s[256] = {};
    cin.getline(s, 255);

    int cnt = 0;
    for (auto &x: s)
    {
        if (x >= '0' && x <= '9')
        {
            cnt++;
        }
    }

    cout << cnt << endl;
}