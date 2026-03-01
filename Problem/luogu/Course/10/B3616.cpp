#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    queue<int> q;
    while (n--)
    {
        int index = 0, x = 0;
        cin >> index;

        switch (index)
        {
        case 1:
            cin >> x;

            q.push(x);
            break;

        case 2:
            if (q.empty() == true)
            {
                cout << "ERR_CANNOT_POP" << endl;
            }
            else
            {
                q.pop();
            }

            break;

        case 3:
            if (q.empty() == true)
            {
                cout << "ERR_CANNOT_QUERY" << endl;
            }
            else
            {
                cout << q.front() << endl;
            }

            break;

        case 4:
            cout << q.size() << endl;
            break;
        }
    }
}