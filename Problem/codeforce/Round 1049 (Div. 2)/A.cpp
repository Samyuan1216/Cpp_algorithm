#include <iostream>
#include <string>
using namespace std;

const int MAXN = 110;
string s;
int t = 0, n = 0, cnt1 = 0, cnt0 = 0;

int main()
{
    cin >> t;
    
    while (t--)
    {
        cin >> n;
        getchar();

        getline(cin, s);
        cnt1 = cnt0 = 0;

        for (auto &c: s)
        {
            if (c == '1')
            {
                cnt1++;
            }
        }

        for (int i = n - 1; i >= n - cnt1; i--)
        {
            if (s[i] == '0')
            {
                cnt0++;
            }
        }

        cout << cnt0 << endl;
    }

    return 0;
}