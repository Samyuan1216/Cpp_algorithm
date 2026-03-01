#include <algorithm>
#include <iostream>
#include <chrono>
#include <format>
#include <random>
using namespace std;

mt19937 rnd(time(0));

/**
 * pair<Iterator, Iterator> minmax_element(Iterator begin, Iterator end, Function comp)
 * 返回最小最大值的迭代器，可自定义比较函数
 * Iterator min_element(Iterator begin, Iterator end, Function comp)
 * Iterator max_element(Iterator begin, Iterator end, Function comp)
 * 
 * 复杂度 O(n)
 */
int main() {
  int n = 10000000;
  vector<int> a(n);
  for (int i = 0; i < n; i ++) a[i] = rnd();
  auto [minIter, maxIter] = ranges::minmax_element(a);
  cout << *minIter << endl;
  cout << *maxIter << endl;
  cout << *ranges::min_element(a) << endl;
  cout << *ranges::max_element(a) << endl;
  int minId = 0, maxId = 0;
  for (int i = 0; i < n; i ++) {
    if (a[i] < a[minId]) minId = i;
    if (a[i] > a[maxId]) maxId = i;
  }
  cout << a[minId] << endl;
  cout << a[maxId] << endl;
}