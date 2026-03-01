#include <iostream>
#include <format>
#include <cmath>
using namespace std;

int main()
{
    double S = 0;
    double AB = 0, AC = 0, BC = 0, p = 0;
    double A[2] = {0}, B[2] = {0}, C[2] = {0};

    cin >> A[0] >> A[1];
    cin >> B[0] >> B[1];
    cin >> C[0] >> C[1];

    AB = sqrt(pow(A[0] - B[0], 2) + pow(A[1] - B[1], 2));
    AC = sqrt(pow(A[0] - C[0], 2) + pow(A[1] - C[1], 2));
    BC = sqrt(pow(B[0] - C[0], 2) + pow(B[1] - C[1], 2));
    p = (AB + AC + BC) / 2;

    S = sqrt(p * (p - AB) * (p - AC) * (p - BC));

    cout << format("{:.2f}", S) << endl;
}