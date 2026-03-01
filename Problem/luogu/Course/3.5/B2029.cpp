#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int h = 0, r = 0;
    cin >> h >> r;

    cout << ceil(20 / (3.14 * pow(r, 2) * h / 1000)) << endl;
}