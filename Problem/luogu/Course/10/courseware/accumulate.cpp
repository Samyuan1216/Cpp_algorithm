#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <numeric>
using namespace std;

mt19937 rnd(time(0));

/**
 * #include <numeric>
 * Type accumulate(Iterator begin, Iterator end, Type init, Function Operator)
 * 对范围内的数值进行累加，可以修改累加函数
 * 
 * 复杂度 O(n)
 */
int main() {
  int n = 20;
  vector<int> a(n);
  for (int i = 0; i < n; i ++) a[i] = i + 1;


  // long long sum = 0;
  auto sum = 1ll;
  for (auto &item : a) sum *= item;
  cout << sum << endl;

  cout << accumulate(a.begin(), a.end(), 1ll, [](long long prev, int item) {
    return prev * item;
  }) << endl;
}