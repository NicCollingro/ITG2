#include <iostream>
#include <stdexcept>
using namespace std;
#define T double
#define PRINT(x)                                                               \
  cout << #x << ": ";                                                          \
  while (x.size())                                                             \
    cout << x.pop() << " ";                                                    \
  cout << endl;

class Stack {
private:
  // stack element for single linked list
  struct node {
    T value;
    node *prev;
    node(T v, node *p) : value(v), prev(p) {}
  };

  // last inserted element
  node *top;

  // stack size
  size_t stack_size;

public:
  // getter for stack size as const member function
  size_t size() const { return stack_size; }

  // DFLT-CTOR
  Stack() : top(nullptr), stack_size(0) { cout << "DFLT-CTOR\n"; }

  // DTOR
  ~Stack() {
    cout << "DFLT-DTOR\n";
    while (stack_size > 0) {
      pop();
    }
  }

  void push(T v) {
    node *NodeNew = new node(v, top);
    top = NodeNew;
    stack_size++;
    // create new node as head node or as mid node ...
  }

  T pop() {
    // Since pop() returns value, its best to throw a runtime_error if used on
    // empty stack
    if (stack_size == 0) {
      throw runtime_error("pop() used while stack was empty");
    }

    T value = top->value;
    node *newTop = top->prev;
    delete top;
    top = newTop;
    stack_size--;
    return value;
    // return most recent element and delete it ...
  }
};

int main() {
  Stack S0; // DFLT-CTOR
  S0.push(11.1);
  S0.push(12.2);
  S0.push(13.3);
  S0.push(14.4);
  PRINT(S0);
}
