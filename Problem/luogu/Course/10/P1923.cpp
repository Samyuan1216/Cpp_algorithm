#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);

    vector<int> a(n);
    for (auto &x: a)
    {
        scanf("%d", &x);
    }

    nth_element(a.begin(), a.begin() + k, a.end());
    printf("%d", a[k]);
}