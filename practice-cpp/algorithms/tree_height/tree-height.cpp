#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
    
    
    static int height_recursion(const Node* node)
    {
        if (node == NULL)
            return 0;
        
        int height = 0;
        
        for (const auto child : node->children)
            height = std::max(height, height_recursion(child));
        
        return 1 + height;
    }
    
    static int height_q(const Node* node)
    {
        std::queue<const Node*> nodes;
        nodes.push(node);
        
        int height = 0;
        int size = nodes.size();
 
        while (!nodes.empty())
        {
            height++;
            int newsize = 0;
            while (size--)
            {
                for (const auto node : nodes.front()->children)
                {
                    nodes.push(node);
                    newsize++;
                }
                nodes.pop();
            }
            size = newsize;
            
        }
        return height;
    }
    
    
    static void fillDepth(const std::vector<Node>& in, int i, int depth[])
    {
        if (i > in.size())
            return;
        
        if (depth[i])
            return;
        
        if (in.at(i).parent == NULL)
        {
            depth[i] = 1;
            return;
        }
        
        const int parent = in.at(i).parent->key;
        if (depth[parent] == 0)
            fillDepth(in, parent, depth);
            
        depth[i] = depth[parent] + 1;
        return;
    }
    
    static int height_array(const std::vector<Node>& in)
    {
        if (in.empty())
            return 0;
        
        const int n = in.size();
        int depth[n];
        for (int i = 0; i < n; ++i)
            depth[i] = 0;
        
        for (int i = 0; i < n; ++i)
            fillDepth(in, i, depth);
        
        int max = 0;
        for(int i = 0; i < n; ++i)
            max = std::max(max, depth[i]);
        
        return max;
    }
    
    
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

    
    int maxHeight = Node::height_array(nodes);
    
    
  std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
