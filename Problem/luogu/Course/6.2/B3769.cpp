#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;

    int q = 0;
    cin >> q;

    while (q--)
    {
        int l1 = 0, r1 = 0, l2 = 0, r2 = 0;
        cin >> l1 >> r1 >> l2 >> r2;

        if (s.substr(l1 - 1, r1 - l1 + 1) < t.substr(l2 - 1, r2 - l2 + 1))
        {
            cout << "yifusuyi" << endl;
        }
        else if (s.substr(l1 - 1, r1 - l1 + 1) > t.substr(l2 - 1, r2 - l2 + 1))
        {
            cout << "erfusuer" << endl;
        }
        else
        {
            cout << "ovo" << endl;
        }
    }
}