#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <ranges>
using namespace std;

mt19937 rnd(time(0));

// 用法 70%
// 原理 20%
// 实现 10%

void benchmark(const string &name, const auto &func) {
  auto start = chrono::high_resolution_clock::now();
  func();
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
  cout << format("{} execution time: {} ms\n", name, duration.count());
}

/**
 * sort(Iterator begin, Iterator end, Function comp)
 * 从小到大排序
 * 
 * 复杂度 O(nlogn)
 */
int main() {
  int n = 100000;
  vector<int> vec(n);
  for (int i = 0; i < n; i ++) vec[i] = rnd();
  vector<int> vec2 = vec;

  benchmark("[选择排序]", [&](){
    // O(n^2)
    for (int i = 0; i < n; i ++) {
      int minId = i;
      for (int j = i + 1; j < n; j ++) {
        if (vec[j] < vec[minId]) minId = j;
      }
      swap(vec[i], vec[minId]);
    }
  });

  // int arr[1000];
  benchmark("[sort]", [&]() {
    sort(vec2.begin(), vec2.end());
    // c++ 20
    // ranges::sort(vec2);
  });
  // for (int i = 0; i < n; i ++) {
  //   if (vec[i] != vec2[i]) {
  //     cout << "error" << endl;
  //     break;
  //   }
  //   cout << vec[i] << endl;
  // }
}