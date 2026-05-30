/*
 * Ich habe den Code übernommen, den die Lösung vorgibt und habe lediglich die
 * drei zu implementierenden Methoden selbst implementiert, da der Code aus der
 * Aufgabenstellung selbst unvollständig war.
 */

#include <iostream>
using namespace std;

#define PRINT(x)                                                               \
    cout << #x << ": ";                                                        \
    while (x.size())                                                           \
        cout << x.pop() << " ";                                                \
    cout << endl;

#define T double

class stack {
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
    stack() : stack_size(0) { cout << "DFLT-CTOR\n"; }

    // Init-Konstruktor
    stack(size_t n, T v) : top{nullptr}, stack_size{0} {
        for (int i = 0; i < n; i++) {
            push(v);
        };
    }

    // Copy-Konstruktor (deep copy)
    stack(const stack &st) : top{nullptr}, stack_size{0} {
        // Falls stack leer ist
        if (st.top == nullptr)
            return;

        top = new node(st.top->value, nullptr);
        stack_size = 1;

        node *source = st.top->prev;
        node *copy = top;

        while (source != nullptr) {
            copy->prev = new node(source->value, nullptr);
            copy = copy->prev;
            source = source->prev;
            ++stack_size;
        }
    }

    // DTOR
    ~stack() {
        cout << "DFLT-DTOR\n";
        // empty whole stack...
        while (stack_size != 0)
            pop();
    }

    void push(T v) {
        // create new node as head node or as mid node...
        node *newNode;
        if (stack_size == 0)
            newNode = new node(v, 0);
        else
            newNode = new node(v, top);
        top = newNode;
        ++stack_size;
    }

    T pop() {
        // return most recent element and delete it...
        if (stack_size == 0)
            cerr << "ERROR: Nothing to pop." << endl;
        // we want to remember value after deletion...
        T v = top->value;
        node *newTop = top->prev;
        delete top;
        top = newTop;
        --stack_size;
        return v;
    }

    // Kopier Operator
    stack &operator=(const stack &st) {
        // Falls das Objekt selbst gleichgesetzt wird
        if (this == &st)
            return *this;

        while (stack_size != 0)
            pop();

        top = nullptr;
        stack_size = 0;

        // Falls stack leer ist -> leeren stack zurückgeben
        if (st.top == nullptr)
            return *this;

        top = new node(st.top->value, nullptr);
        stack_size = 1;

        node *source = st.top->prev;
        node *copy = top;

        while (source != nullptr) {
            copy->prev = new node(source->value, nullptr);
            copy = copy->prev;
            source = source->prev;
            ++stack_size;
        }

        return *this;
    }
};

int main() {
    stack S0;          // DFLT-CTOR
    stack S1(3, 3.14); // INIT-CTOR
    stack S2(S1);      // COPY-CTOR

    S2.push(4.5);
    S1 = S2;
    PRINT(S1);
    PRINT(S2);
}
