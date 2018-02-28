#include <iostream>
#include <exception>
#include <utility> // swap

class PriorityQueue
{
public:
    typedef unsigned int uint;
    
    explicit PriorityQueue();
    explicit PriorityQueue(uint length);
    
    ~PriorityQueue();
    
    int top();
    void insert(int item);
    bool isEmpty() const;
    void print() const;

private:
    uint leftChildIndex(uint index) const;
    uint rightChildIndex(uint index) const;
    uint parentIndex(uint index) const;
    
    void siftUp(uint index);
    void siftDown(uint index);
    
    void reallocMemory();
private:
    int *data;
    uint size;
    uint maxSize;
};


PriorityQueue::PriorityQueue()
    : size(0)
    , maxSize(4)
{
    data = new int[maxSize];
}

PriorityQueue::PriorityQueue(PriorityQueue::uint length)
: size(0)
, maxSize(length)
{
    data = new int[maxSize];
}

PriorityQueue::~PriorityQueue()
{
    delete[] data;
}

PriorityQueue::uint PriorityQueue::leftChildIndex(PriorityQueue::uint index) const
{
    return (2 * index + 1);
}

PriorityQueue::uint PriorityQueue::rightChildIndex(PriorityQueue::uint index) const
{
    return (2 * index + 2);
}

PriorityQueue::uint PriorityQueue::parentIndex(PriorityQueue::uint index) const
{
    return ((index - 1) / 2);
}

void PriorityQueue::siftUp(PriorityQueue::uint index)
{
    while(index > 0 && data[index] > data[parentIndex(index)])
    {
        //Swap
        std::swap(data[index], data[parentIndex(index)]);
        index = parentIndex(index);
    }
}

void PriorityQueue::siftDown(PriorityQueue::uint index)
{
    uint maxChildIndex = index;
    
    uint leftIndex = leftChildIndex(index);
    if (leftIndex < size && data[index] < data[leftIndex])
    {
        maxChildIndex = leftIndex;
    }
    
    uint rightIndex = rightChildIndex(index);
    if (rightIndex < size && data[leftIndex] < data[rightIndex])
    {
        maxChildIndex = rightIndex;
    }
    
    if (index != maxChildIndex)
    {
        std::swap(data[index], data[maxChildIndex]);
        siftDown(maxChildIndex);
    }
}

int PriorityQueue::top()
{
    int ret = data[0];
    data[0] = data[--size];
    siftDown(0);
    return ret;
}

void PriorityQueue::insert(int item)
{
    if (size >= maxSize)
        reallocMemory();
    
    data[size++] = item;
    siftUp(size - 1);
}

bool PriorityQueue::isEmpty() const
{
    return (this->size == 0);
}

void PriorityQueue::reallocMemory()
{
    maxSize *= 2;
    int *newData = new int[maxSize];
    
    for(int i = 0; i < size; ++i)
        newData[i] = data[i];
    
    delete[] data;
    data = newData;
}

void PriorityQueue::print() const
{
    for (int i = 0; i < size - 1; ++i)
        std::cout << data[i] << ", ";
    std::cout << data[size - 1] << std::endl;
}


void test()
{
    int n = 99999;
    PriorityQueue q;
    for(int i = 0; i < n; ++i)
        q.insert(i);
    while(!q.isEmpty())
    {
        if (q.top() != --n)
            std::cout << "Error occured!" << std::endl;
    }
    if (n == 0)
        std::cout << "Success" << std::endl;
    
}


int main()
{
    test();
}


