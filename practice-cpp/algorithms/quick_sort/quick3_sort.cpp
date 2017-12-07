#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <utility>
#include <ctime>

using std::vector;
using std::swap;


std::pair<long, long> partition3(vector<long> &a, long l, long r)
{
    long x = l;
    long j = l;
    for (long i = l + 1; i <= r; i++)
    {
        if (a.at(i) < a.at(x))
        {
            j++;
            swap(a.at(i), a.at(j));
        }
        else if (a.at(i) == a.at(x))
        {
            j++;
            swap(a.at(i), a.at(++x));
        }
    }
    
    for (long i = 0; i <= x - l; ++i)
        swap(a.at(l+i), a.at(j-i));
    
    return std::make_pair(j - (x - l), j);
}

void quick_sort(vector<long> &a, long l, long r) {
    while (l < r)
    {
        int k = l + rand() % (r - l + 1);
        swap(a[l], a[k]);
        std::pair<long, long> limits = partition3(a, l, r);
        if ((limits.first - l) < (r - limits.second))
        {
            quick_sort(a, l, limits.first - 1);
            l = limits.second + 1;
        }
        else
        {
            quick_sort(a, limits.second + 1, r);
            r = limits.first - 1;
        }
    }
}

int partition2(vector<int> &a, int l, int r) {
    int x = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }
    
    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    int m = partition2(a, l, r);
    
    randomized_quick_sort(a, l, m - 1);
    randomized_quick_sort(a, m + 1, r);
}

void stress_test(int maxLength)
{
    if (maxLength < 0)
        return;
    while (1)
    {
        std::srand(unsigned(std::time(0)));
        int length =  rand() % maxLength;
        vector<int> qtest2;
        vector<long> qtest3;
        for (int i = 0; i < length; ++i)
        {
            int a = rand();
            qtest2.push_back(a);
            qtest3.push_back(a);
        }
        
        randomized_quick_sort(qtest2, 0, qtest2.size() - 1);
        quick_sort(qtest3, 0, qtest3.size() - 1);
        
        for (int i = 0; i < qtest2.size(); ++i)
        {
            if (qtest2.at(i) != qtest3.at(i))
            {
                std::cout << "2 partitions sort:" << std::endl;
                std::copy(qtest2.begin(), qtest2.end(), std::ostream_iterator<int>(std::cout, " "));
                
                std::cout << "\n\n3 partitions sort:" << std::endl;
                std::copy(qtest3.begin(), qtest3.end(), std::ostream_iterator<int>(std::cout, " "));
                std::cout << std::endl;
                return;
            }
        }
        std::cout << "passed on " << length << " events" << std::endl;
    }
}
int main() {
   // stress_test(100000);
  long n;
  std::cin >> n;
  vector<long> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }

}
