#include <iostream>
#include <format>
using namespace std;

int main()
{
    double a = 0;
    
    cin >> a;

    cout << format("{:.12f}", a) << endl;
}