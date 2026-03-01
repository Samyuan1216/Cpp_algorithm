#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <queue>
#include <stack>
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
 * push/emplace
 * pop
 * 
 * top
 * empty
 * size
 * 
 * [] <-- push
 *    --> pop
 * 
 * cannot []
 */
int main() {
  stack<int> stk;
  for (int i = 0; i < 10; i ++) {
    stk.push(i);
  }
  while (!stk.empty()) {
    int top = stk.top();
    stk.pop();
    cout << top << endl;
  }
  int n = 100000000;
  benchmark("push", [&]() {
    for (int i = 0; i < n; i ++) stk.push(rnd());
  });
  benchmark("pop", [&]() {
    for (int i = 0; i < n; i ++) stk.pop();
  });
  vector<int> vec;
  // vec.reserve(n);
  benchmark("vector push", [&]() {
    for (int i = 0; i < n; i ++) vec.push_back(rnd());
  });
  benchmark("vector pop", [&]() {
    for (int i = 0; i < n; i ++) vec.pop_back();
  });
}