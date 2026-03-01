#include <iostream>
#include <vector>
using namespace std;

vector <int> shift(vector <int> v);

int main()
{
    int n = 0;
    
    cin >> n;

    vector <int> p(n);

    for (auto& x: p)
    {
        cin >> x;
    }

    do
    {
        p = shift(p);
        
        for (auto& x: p)
        {
            cout << x << " ";
        }

        cout << endl;
    } while (p.back() != n);
    
}

vector <int> shift(vector <int> v)
{
    int i = 0;

    i = v.back();
    v.pop_back();
    v.insert(v.begin(), i);

    return v;
}