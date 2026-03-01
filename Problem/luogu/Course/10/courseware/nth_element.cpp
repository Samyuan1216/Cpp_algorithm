#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
using namespace std;

mt19937 rnd(time(0));

void benchmark(const string &name, const auto &func) {
  auto start = std::chrono::high_resolution_clock::now();
  func();
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  cout << format("{} execution time: {} ms\n", name, duration.count());
}

/**
 * nth_element(Iterator begin, Iterator nth, Iterator end, Function comp)
 * 将第 nth 小的数移动到第 nth 位
 * 
 * 复杂度 O(n)
 */
int main() {
  int n = 10000000;
  vector<int> a(n);
  for (int i = 0; i < n; i ++) a[i] = rnd();
  vector<int> b = a;
  int k = rnd() % n;

  benchmark("[sort]", [&](){
    ranges::sort(a);
    cout << a[k] << endl;
  });

  benchmark("[nth_element]", [&]() {
    nth_element(b.begin(), b.begin() + k, b.end());
    cout << b[k] << endl;
  });
}