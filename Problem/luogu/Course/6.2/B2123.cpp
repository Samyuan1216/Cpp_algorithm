#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, res;
    getline(cin, s);

    char t = '\0';
    int cnt = 0;
    for (auto &x: s)
    {
        if (x != t)
        {
            if (cnt)
            {
                res += to_string(cnt) + t;
                cnt = 0;
            }

            t = x;
        }

        cnt++;
    }

    if (cnt)
    {
        res += to_string(cnt) + t;
        cnt = 0;
    }

    cout << res << endl;
}