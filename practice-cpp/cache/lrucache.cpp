/*
Abstract base classes in C++ can only be used as base classes. 
Thus, they are allowed to have virtual member functions without definitions.

A cache is a component that stores data so future requests for that data can be served faster. 
The data stored in a cache might be the results of an earlier computation, or the duplicates 
of data stored elsewhere. A cache hit occurs when the requested data can be found in a cache, 
while a cache miss occurs when it cannot. Cache hits are served by reading data from the 
cache which is faster than recomputing a result or reading from a slower data store. Thus, 
the more requests that can be served from the cache, the faster the system performs.

One of the popular cache replacement policies is: "least recently used" (LRU). 
It discards the least recently used items first.
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache {
public:
    LRUCache(size_t capacity) {
        cp = capacity;
        head = NULL;
        tail = NULL;
    } // cp == 0 ERROR
    int get(int key) {
        if(mp.find(key) != mp.end()) return mp[key]->value;
        else return -1;
    }
    void set(int key, int value) {
        // when capacity >= 1 but no elements created
        if (mp.size() < cp) {
            Node* nd = new Node(NULL, head, key, value);
            tail = head;
            head = nd; 
            mp[key] = nd;
        }   
        else { // remove the last, add new one in front
            delete tail;
            mp.erase(key);
            set(key, value);
        }
    }
    
};


int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
