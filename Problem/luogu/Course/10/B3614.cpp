#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main()
{
    int T = 0;
    cin >> T;

    while (T--)
    {
        int n = 0;
        cin >> n;

        stack<unsigned long long> s;
        while (n--)
        {
            string str;
            cin >> str;

            unsigned long long x = 0;
            if (str == "push")
            {
                cin >> x;
                s.push(x);
            }
            else if (str == "pop")
            {
                if (s.empty() == true)
                {
                    cout << "Empty" << endl;
                }
                else
                {
                    s.pop();
                }
            }
            else if (str == "query")
            {
                if (s.empty() == true)
                {
                    cout << "Anguei!" << endl;
                }
                else
                {
                    cout << s.top() << endl;
                }
            }
            else if (str == "size")
            {
                cout << s.size() << endl;
            }
        }
    }
}