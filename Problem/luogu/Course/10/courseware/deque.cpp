#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
#include <queue>
#include <stack>
#include <deque>
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
 * push_back/emplace_back
 * pop_back
 * push_front/emplace_front
 * pop_front
 * 
 * front
 * back
 * empty
 * size
 * 
 * can []
 */
int main() {
  deque<int> deq;
  int n = 100000000;
  benchmark("push_back", [&]() {
    for (int i = 0; i < n; i ++) deq.push_back(rnd());
  });
  vector<int> vec;
  benchmark("vector push_back", [&]() {
    for (int i = 0; i < n; i ++) vec.push_back(rnd());
  });
  benchmark("access", [&]() {
    for (int i = 0; i < n; i ++) deq[i] = i;
  });
  benchmark("vector access", [&]() {
    for (int i = 0; i < n; i ++) vec[i] = i;
  });
  // benchmark("pop_back", [&]() {
  //   for (int i = 0; i < n; i ++) deq.pop_back();
  // });
  // benchmark("push_front", [&]() {
  //   for (int i = 0; i < n; i ++) deq.push_front(rnd());
  // });
  // benchmark("pop_front", [&]() {
  //   for (int i = 0; i < n; i ++) deq.pop_front();
  // });
}