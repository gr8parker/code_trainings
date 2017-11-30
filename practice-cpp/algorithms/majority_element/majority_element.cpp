#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  
  int element = -1;
  int counter = 0;
  for (const auto el : a) {
    
    if (counter == 0)
    {
      element = el;
      counter++;
    }
    else if (el == element)
    {
      counter++;
    }
    else 
    {
      counter--;
    }
  }

  counter = 0;
  for (const auto el : a) {
    if (el == element)
      counter++;
  }

  if (counter > a.size() / 2)
    return element;
   
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
