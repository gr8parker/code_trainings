#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>

void sift_down(std::vector<int> &v, int idx, int size);

void heap_sort(std::vector<int> &v)
{
    int size = v.size();
    while(--size)
    {
        std::swap(v[0], v[size]);
        sift_down(v, 0, size);
    }
}

void sift_down(std::vector<int> &v, int idx, int size)
{
    int leftIndex = 2 * idx + 1;
    int rightIndex = 2 * idx + 2;
    int maxIndex = idx;
    
    if (leftIndex < size && v[idx] < v[leftIndex])
        maxIndex = leftIndex;
    
    if (rightIndex < size && v[leftIndex] < v[rightIndex])
        maxIndex = rightIndex;
    
    if (maxIndex != idx)
    {
        std::swap(v[idx], v[maxIndex]);
        sift_down(v, maxIndex, size);
    }
}

int main()
{
    std::vector<int> test;
    for (int i = 50; i > 0; --i)
        test.push_back(i);
    
    std::copy(test.begin(), test.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    heap_sort(test);
    std::cout <<"Heap sort:" << std::endl;
    std::copy(test.begin(), test.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
