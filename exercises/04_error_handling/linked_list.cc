// Exercises - session 04
// Linked list
// Implement a linked list using unique pointers

// reset() calls the destructor for the object currently managed and takes
// the ownership.
// release() releases ownership of its stored pointer, by returning its
// value and replacing it with a null pointer.

#include <iostream>
#include <memory>  // for smart pointers

// scoped enum
enum class Insertion_method { push_back, push_front };

template <typename value_type>
class List {
 public:
  // implement suitable constructor(s) for List
  List() : _size{0}, head{nullptr} {}

  void insert(const value_type& v, const Insertion_method m);
  // passing v by reference because I don't know its size,
  // otherwise it's better to pass by value.

  void print();

  // return the size of the list
  unsigned int size() { return _size; }

  void reset();

  void prune_node(const value_type v);

 private:
  // private struct node with the proper value_type
  struct node {
    value_type val;
    std::unique_ptr<node> next;  // automatically deleted when out of scope
    node(const value_type v) : val{v}, next{nullptr} {}
    ~node(){};  // default destructor
  };

  // append the newly created node at the end of the list
  void push_back(const value_type& v);

  // insert the newly created node in front of the list
  void push_front(const value_type& v);

  std::unique_ptr<node> head;  // unique pointer to the first node
  unsigned int _size;          // number of nodes
};

// insert a new node with the value v according to the method m
// this method should be used to fill the list
template <typename value_type>
void List<value_type>::insert(const value_type& v, const Insertion_method m) {
  switch (m) {
    case Insertion_method::push_back:
      push_back(v);
      break;
    case Insertion_method::push_front:
      push_front(v);
      break;
  }
}

// print the values of the nodes
template <typename value_type>
void List<value_type>::print() {
  node* temp = head.get();  // get() returns a pointer to the managed object

  while (temp) {  // temp != nullptr
    std::cout << " -> " << temp->val;
    temp = (temp->next).get();  // "temp->next" is equal to "(*temp).next"
  }

  std::cout << std::endl;
}

// delete all the nodes of the list

// template <typename value_type>
// void List<value_type>::reset() {
//   std::unique_ptr<node> temp = std::move(head);
//   while (temp) {  // temp != nullptr
//     temp->next = std::move(temp);
//   }
//   temp = nullptr;  // non serve
//   _size = 0;
// }

template <typename value_type>
void List<value_type>::reset() {
  head.reset();
  _size = 0;
}

// prune node storing the value v
template <typename value_type>
void List<value_type>::prune_node(const value_type v) {
  if (_size == 1) {
    head = std::move(head->next);
    _size = _size - 1;
  } else {
    node* previous = head.get();
    node* temp = head->next.get();

    while (temp->next) {  // temp->next != nullptr
      if (head->val == v) {
        previous = previous->next.get();
        temp = temp->next.get();
        head = std::move(head->next);
        _size = _size - 1;
      }
      if (temp->val == v) {
        previous->next.reset(temp->next.release());
        temp = (previous->next).get();  // move to the next node
        _size = _size - 1;
      }
      temp = temp->next.get();
      previous = previous->next.get();
    }
  }
}

// push front adds a new node where the head is pointing
template <typename value_type>
void List<value_type>::push_front(const value_type& v) {
  std::unique_ptr<node> temp(new node(v));  // () creates a unique_ptr
  // temp points to a new node with value v and pointer nullptr
  temp->next = std::move(head);
  head = std::move(temp);
  _size++;
}

// push back adds a new node pointed by the last nullptr
template <typename value_type>
void List<value_type>::push_back(const value_type& v) {
  node* temp = head.get();
  while (temp->next) {          // temp->next != nullptr
    temp = (temp->next).get();  // move along all the nodes
  }
  std::unique_ptr<node> ptr(new node(v));
  temp->next = std::move(ptr);  // move ptr to the last nullptr
  _size++;
}

int main(int argc, char const* argv[]) {
  List<int> list{};

  std::cout << "Empty list: ";
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push front value 1: ";
  list.insert(1, Insertion_method::push_front);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push front value 2: ";
  list.insert(2, Insertion_method::push_front);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push back value 3: ";
  list.insert(3, Insertion_method::push_back);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push front value 4: ";
  list.insert(4, Insertion_method::push_front);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Push front value 2: ";
  list.insert(2, Insertion_method::push_front);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Prune value 2: ";
  list.prune_node(2);
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  std::cout << "Reset the list: ";
  list.reset();
  list.print();
  std::cout << "Size is " << list.size() << ".\n\n";

  return 0;
}
