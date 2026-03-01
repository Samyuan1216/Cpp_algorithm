#include <iostream>
#include <format>
using namespace std;

int main()
{
    char a = '0';
    int b = 0;
    float c = 0;
    double d = 0;

    cin >> a >> b >> c >> d;

    cout << format("{} {} {:.6f} {:.6f}", a, b, c, d);
}