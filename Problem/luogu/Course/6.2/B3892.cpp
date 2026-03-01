#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int n = 0, Q = 0;
    cin >> n >> Q;

    vector<string> s(n);
    for (auto &str: s)
    {
        cin >> str;
    }

    vector<int> a, b, c;
    for (auto &str: s)
    {
        int x = str.find("x");
        int equal = str.find("=");

        a.push_back(stoi(str.substr(0, x)));
        b.push_back(stoi(str.substr(x + 1, equal - x - 1)));
        c.push_back(stoi(str.substr(equal + 1)));
    }

    while (Q--)
    {
        int l = 0, r = 0;
        cin >> l >> r;

        int cnt = 0;
        for (int x = l; x <= r; x++)
        {
            for (int i = 0; i < a.size(); i++)
            {
                if (a[i] * x + b[i] == c[i])
                {
                    cnt++;
                    break;
                }
            }
        }

        cout << cnt << endl;
    }
}