#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <set>
#include <unordered_set>
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
 * set 有序 唯一
 * multiset 有序 不唯一
 * unordered_set 无序 唯一
 * 
 * insert  O(logn)         O(1) * C
 * erase
 * find
 * count           O(n)
 * 
 * 有序 元素支持 <
 * 无需 元素支持 hash
 */
int main() {
  unordered_set<double, decltype([](double x) {
    return (size_t)(x * 1e6);
  }), decltype([](double a, double b) {
    return fabs(a - b) < 1e-6;
  })> us;
  // unordered_set<double> us;
  us.insert(0.1 + 0.2);
  us.insert(0.3);
  cout << us.size() << endl;
  // multiset<int, decltype([](int a, int b) {
  //   return a > b;
  // })> ms{1, 2, 3, 4, 8, 16, 77};
  // auto iter = ms.lower_bound(9);
  // if (iter != ms.end()) {
  //   *iter == 9;
  //   iter != ms.begin();
  //   --iter;
  // }

  // set<int> s;
  // s.insert(1);
  // s.emplace(2);
  // if (auto iter = s.find(1); iter != s.end()) {
  //   cout << *iter << endl;
  // }
  // if (s.count(123)) {
  //   cout << "found" << endl;
  // }
  // s.erase(1);
  // if (s.count(1)) {
  //   cout << "found" << endl;
  // }

  // set<int> s{1, 1, 8, 4, 2, 2, 4, 8};
  // multiset<int> ms{1, 1, 8, 4, 2, 2, 4, 8};
  // unordered_set<int> us{1, 1, 8, 4, 2, 2, 4, 8};
  // for (auto &x : s) cout << x << ' ';
  // cout << endl;
  // for (auto &x : ms) cout << x << ' ';
  // cout << endl;
  // for (auto &x : us) cout << x << ' ';
  // cout << endl;
}