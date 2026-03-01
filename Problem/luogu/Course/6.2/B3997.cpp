#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
    string S;
    getline(cin, S);

    int index = 0, len = 1, cnt = 0;
    while (index < S.length())
    {
        string t = S.substr(index, len);
        string r = t;
        reverse(r.begin(), r.end());

        if (t == r)
        {
            cnt++;
        }

        index += len;
        len++;
    }

    cout << cnt << endl;
}