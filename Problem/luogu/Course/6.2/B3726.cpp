#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n = 0, q = 0;
    cin >> n >> q;

    vector<string> s(n);
    for (auto &str: s)
    {
        cin >> str;
    }

    while (q--)
    {
        int op = 0;
        cin >> op;

        if (op == 1)
        {
            int x = 0, y = 0, i = 0;
            cin >> x >> y >> i;

            s[y - 1].insert(i, s[x - 1]);
        }
        else if (op == 2)
        {
            int y = 0;
            cin >> y;

            cout << s[y - 1] << endl;
        }
    }
}