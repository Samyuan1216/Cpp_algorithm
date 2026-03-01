#include <iostream>
#include <format>
using namespace std;

int main()
{
    float a = 0;
    
    cin >> a;

    cout << format("{:.3f}", a) << endl;
}