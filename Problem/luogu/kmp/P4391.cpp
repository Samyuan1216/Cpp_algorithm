#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

const int MAXL = 1000010;
vi ne(MAXL);
string s;
int l;

int main()
{
    cin >> l >> s;

    ne[0] = -1;
    ne[1] = 0;
    
    int i = 2, cn = 0;
    while (i <= l)
    {
        if (s[i - 1] == s[cn])
        {
            ne[i++] = ++cn;
        }
        else if (cn > 0)
        {
            cn = ne[cn];
        }
        else
        {
            ne[i++] = 0;
        }
    }

    cout << l - ne[l] << endl;
}