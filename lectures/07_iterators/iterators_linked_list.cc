// lesson 28/11/17 on ITERATORS

// Iterators allow the user to apply a method to the data contained inside the
// list without knowing its structure

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

// using namespace std;

// scoped enum
enum class Insertion_method { push_back, push_front };

template <typename value_type>
class List {
  // private by default
  // private struct node with the proper value_type
  struct node {
    value_type val;
    std::unique_ptr<node> next;  // automatically deleted when out of scope
    node(const value_type& v, node* n = nullptr) : val{v}, next{n} {}
    // if I don't specify anything, next pointer is nullptr
    ~node(){};  // default destructor
  };

  std::unique_ptr<node> head;  // unique pointer to the first node
  unsigned int _size;          // number of nodes

  // append the newly created node at the end of the list
  void push_back(const value_type& v);

  // insert the newly created node in front of the list
  void push_front(const value_type& v);

 public:
  // implement suitable constructor(s) for List
  List() : head{nullptr}, _size{0} {}

  void insert(const value_type& v,
              const Insertion_method m = Insertion_method::push_front);
  // passing v by reference because I don't know its size,
  // otherwise it's better to pass by value.

  void print() const;

  // return the size of the list
  unsigned int size() { return _size; }

  void call_custom_function() {
    node* temp{head.get()};
    while (temp) {
      custom_function(temp->val);
      temp = temp->next.get();
    }
  }

  std::function<void(value_type& v)> custom_function;

  // ITERATOR DECLARATION

  // we define the iterator inside the class so we know that it iterates through
  // a list
  class Iterator;
  Iterator begin() { return Iterator{head.get()}; }
  Iterator end() { return Iterator{nullptr}; }

  class constIterator;  // const constructors for class Iterator are not enough
  Iterator begin() const { return Iterator{head.get()}; }
  Iterator end() const { return Iterator{nullptr}; }
};

template <typename value_type>
class List<value_type>::Iterator {
  using node = List<value_type>::node;  // using an alias
  node* current;

 public:
  Iterator(node* n) : current{n} {}

  // dereference operator
  value_type& operator*() const { return current->val; }

  // ++it operator
  Iterator& operator++() {
    current = current->next.get();
    return *this;
  }

  // it++ operator
  Iterator& operator++(int) {  // we take an int to distinguish it from ++it
    Iterator it{current};
    ++(*this);  // increment the current value calling the ++it operator
    return it;  // return by value the previous one
  }

  bool operator==(const Iterator& other) {
    return this->current ==
           other.current;  // two iterators are equal if they are
                           // pointing to the same element
  }

  bool operator!=(const Iterator& other) {
    return !(*this == other);  // return current != other.current; works as well
  }
};

// constIterator constructor

template <typename value_type>
class List<value_type>::constIterator : public List<value_type>::Iterator {
  using parent = List<value_type>::Iterator;

 public:
  using List<value_type>::Iterator;
  const value_type& operator*() const { return parent::operator*(); }
};

// insert a new node with the value v according to the method m
// this method should be used to fill the list
template <typename value_type>
void List<value_type>::insert(const value_type& v, const Insertion_method m) {
  if (head.get() == nullptr) {
    head.reset(new node{v});  // reset returns a raw pointer
    // head.reset(new node{v, nullptr});  is the same
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
template <typename value_type>
void List<value_type>::print() const {
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

// template <typename value_type>
// void List<value_type>::reset() {
//   std::unique_ptr<node> temp = std::move(head);
//   while (temp) {  // temp != nullptr
//     temp->next = std::move(temp);
//   }
//   temp = nullptr;
//   _size = 0;
// }

// push front adds a new node where the head is pointing
template <typename value_type>
void List<value_type>::push_front(const value_type& v) {
  head.reset(new node{v, head.release()});
  // we release the ownership of head
  // and reset it to a pointer to a new node
  _size++;
}

// push back adds a new node pointed by the last nullptr
template <typename value_type>
void List<value_type>::push_back(const value_type& v) {
  node* temp = head.get();
  while (temp->next) {          // or while (temp->next.get() != nullprt) {
    temp = (temp->next).get();  // move along all the nodes
  }
  temp->next.reset(new node{v});  // move ptr to the last nullptr
  _size++;
}

int main() {
  List<double> list{};

  std::cout << "Empty list: ";
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push value 1: ";
  list.insert(1.1);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push value 2: ";
  list.insert(2.2);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  double sum{0};
  list.custom_function = [&sum](double& d) { sum += d; };
  std::cout << "The sum is " << sum << std::endl;

  list.call_custom_function();  // internally, the list will call
                                // custom_function

  // an alternative would be using lambda functions

  // auto my_sum = [&sum] (double& d){
  //   sum+=d;
  // };
  // list.custom_function = my_sum;

  sum = 0;
  auto last = list.end();
  for (auto it = list.begin(); it != last; ++it) {
    sum += *it;
  }

  // // or I can write
  //   for(auto & x: list){
  //     sum += x++;
  //   }

  return 0;
}
