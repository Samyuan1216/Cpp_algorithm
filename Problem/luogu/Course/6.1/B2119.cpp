#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    char tail[][4] = {"re", "yl", "gni"};
    char s[40] = {};
    cin >> s;

    int len = strlen(s);
    reverse(s, s + len);

    for (auto &str: tail)
    {
        char *c = strstr(s, str);
        if (c != NULL)
        {
            s[strlen(str) - 1] = '\0';
            break;
        }
    }

    reverse(s, s + len);
    cout << s << endl;
}