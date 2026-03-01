#include <iostream>
#include <format>
using namespace std;

int main()
{
    double a = 0;

    cin >> a;

    cout << format("{0:f}\n{0:.5f}\n{0:e}\n{0:g}", a);
}