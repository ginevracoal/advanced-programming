// lesson 28/11/17 on ITERATORS

// Iterators allow the user to apply a method to the data contained inside the
// list without knowing its structure.

// Linked list
// Implement a linked list using unique pointers
// we'll use three basic functions of unique pointers:
// get(), release(), reset()

// a unique ptr to a node has the following structure:
// {
//   bool owned;
//   node * ptr;
// }
// get() returns ptr
// release() sets owned to false and returns ptr
// reset() resets the ownership

#include <iostream>
#include <memory>  // for smart pointers

#include "../../exercises/08_stl/unique_ptr.h"

// using namespace std;

// scoped enum
enum class Insertion_method { push_back, push_front };

template <typename T>
class List {
  // private by default
  // private struct node with the proper T
  struct node {
    T val;                  // value type
    unique_ptr<node> next;  // automatically deleted when out of scope
    node(const T& v, node* n = nullptr) : val{v}, next{n} {}
    // if I don't specify anything, next pointer is nullptr
    ~node(){};  // default destructor
  };

  std::unique_ptr<node> head;  // unique pointer to the first node
  unsigned int _size;          // number of nodes

  // append the newly created node at the end of the list
  void push_back(const T& v);

  // insert the newly created node in front of the list
  void push_front(const T& v);

 public:
  // implement suitable constructor(s) for List
  List() : head{nullptr}, _size{0} {}

  void insert(const T& v,
              const Insertion_method m = Insertion_method::push_front);
  // passing v by reference because I don't know its size,
  // otherwise it's better to pass by value.

  void print() const;

  // print the size of the list
  void printSize() { std::cout << "Size is " << _size << ".\n\n"; }

  void call_custom_function() {
    node* temp{head.get()};
    while (temp) {  // temp != nullptr
      custom_function(temp->val);
      temp = temp->next.get();
    }
  }

  std::function<void(T& v)> custom_function;

  // ITERATORS

  /** We define the iterator inside the class so we know that it iterates
   * through a list.*/

  class Iterator;

  Iterator begin() { return Iterator{head.get()}; }
  Iterator end() { return Iterator{nullptr}; }

  class ConstIterator;
  /** ConstIterator begin() and end() are const member functions, meaning that
   * they do not modify the state of a tree. The compiler will catch accidental
   * attempts to violate this promise. Iterator is not enough: Const functions
   * can be called on any type of object, while non-const functions can only be
   * called on non-const objects.
  */
  ConstIterator begin() const { return ConstIterator{head.get()}; }
  ConstIterator end() const { return ConstIterator{nullptr}; }
};

// ======================================================
// ITERATOR DEFINITIONS

template <typename T>
class List<T>::Iterator {
  using node = List<T>::node;  // using an alias for readability
  node* current;

 public:
  Iterator(node* n) : current{n} {}

  /** dereference operator returns the object pointed to by the iterator */
  T& operator*() const { return current->val; }

  // ++it operator
  Iterator& operator++() {
    current = current->next.get();
    return *this;
  }

  // it++ operator
  Iterator operator++(int) {  // we take an int to distinguish it from ++it
    Iterator it{current};
    ++(*this);  // increment the current value calling the ++it operator
    return it;  // return the previous one
  }

  /** Two iterators are equal if they point to the same object. The operator is
   * passed through const reference. */
  bool operator==(const Iterator& other) {
    return this->current == other.current;
    // return current == other.current; // is the same
  }

  bool operator!=(const Iterator& other) {
    return !(*this == other);
    // return current != other.current; // is the same
  }
};

/** ConstIterator inherits Iterator class. */
template <typename T>
class List<T>::ConstIterator : public List<T>::Iterator {
  using parent = List<T>::Iterator;

 public:
  using parent::Iterator;
  /** The only difference with Iterator class is the dereference: in this case
   * you can't reset the pointer to a new object, because it is a const
   * reference. */
  const T& operator*() const { return parent::operator*(); }
};

// ======================================================
// MEMBER FUNCTIONS

// insert a new node with the value v according to the method m
// this method should be used to fill the list
template <typename T>
void List<T>::insert(const T& v, const Insertion_method m) {
  std::cout << "\nPush value " << v << ":\n";
  if (head.get() == nullptr) {
    head.reset(new node{v});  // reset returns a raw pointer
                              // head.reset(new node{v, nullptr});  is the same
    ++_size;
  } else {
    switch (m) {
      case Insertion_method::push_back:
        push_back(v);
        break;

      case Insertion_method::push_front:
        push_front(v);
        break;

      default:
        std::cerr << "error\n";
        break;
    }
  }
}

// print the values of the nodes
template <typename T>
void List<T>::print() const {
  // node* temp = head.get();  // get() returns a pointer to the managed object

  // while (temp) {  // temp != nullptr
  //   std::cout << " -> " << temp->val;
  //   temp = (temp->next).get();  // "temp->next" is equal to "(*temp).next"
  // }

  // for (const auto& x : *this) {
  //   std::cout << x << std::endl;
  // }

  auto it{this->begin()};
  auto it_end{this->end()};
  for (; it != it_end; ++it) {
    std::cout << *it << std::endl;
    // the constIterator doesn't allow to modify it value
  }
}

// delete all the nodes of the list

// template <typename T>
// void List<T>::reset() {
//   std::unique_ptr<node> temp = std::move(head);
//   while (temp) {  // temp != nullptr
//     temp->next = std::move(temp);
//   }
//   temp = nullptr;
//   _size = 0;
// }

// push front adds a new node where the head is pointing
template <typename T>
void List<T>::push_front(const T& v) {
  head.reset(new node{v, head.release()});
  // we release the ownership of head
  // and reset it to a pointer to a new node
  ++_size;
}

// push back adds a new node pointed by the last nullptr
template <typename T>
void List<T>::push_back(const T& v) {
  node* temp = head.get();
  while (temp->next) {          // or while (temp->next.get() != nullprt) {
    temp = (temp->next).get();  // move along all the nodes
  }
  temp->next.reset(new node{v});  // move ptr to the last nullptr
  ++_size;
}

// ======================================================
//  MAIN

int main() {
  List<double> list{};

  list.print();
  list.printSize();

  list.insert(1.1);
  list.print();
  list.printSize();

  list.insert(2.2);
  list.print();
  list.printSize();

  double sum{0};

  // using lambda functions
  auto my_sum = [&sum](double& d) { sum += d; };
  list.custom_function = my_sum;

  list.call_custom_function();  // internally, the list will call
                                // custom_function
  std::cout << "The sum is " << sum << std::endl;

  // sum = 0;
  // auto last = list.end();
  // for (auto it = list.begin(); it != last; ++it) {
  //   sum += *it;
  // }

  // // or I can write
  //   for(auto & x: list){
  //     sum += x++;
  //   }

  return 0;
}
