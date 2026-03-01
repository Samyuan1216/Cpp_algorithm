#include <iostream>
#include <cmath>
#include <format>
using namespace std;

int main()
{
    float AB = 0;
    float A[2] = {0}, B[2] = {0};

    cin >> A[0] >> A[1];
    cin >> B[0] >> B[1];

    AB = sqrt(pow(A[0] - B[0], 2) + pow(A[1] - B[1], 2));

    cout << format("{:.3f}", AB) << endl;
}