#include <iostream>
#include <format>
using namespace std;

int main()
{
    int a = 0, b = 0, c = 0;

    cin >> a >> b >> c;

    cout << format("{:8} {:8} {:8}", a, b, c);
}