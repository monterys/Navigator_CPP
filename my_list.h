#ifndef CPP2_S21_CONTAINERS_2_S21_LIST_H
#define CPP2_S21_CONTAINERS_2_S21_LIST_H

#include <exception>
#include <iostream>
#include <limits>

namespace my {
template <class T>
class list {
 public:
  class ListIterator;
  class ListConstIterator;
  class Node;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;

  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l) noexcept;
  ~list();

  list &operator=(const list &l);
  list &operator=(list &&l) noexcept;

  const_reference front() const { return head_->value_; }
  const_reference back() const { return tail_->prev_->value_; }

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const noexcept;
  size_type size() const { return size_; }
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);

  void print() {
    Node *tmp = head_;
    while (tmp != tail_) {
      std::cout << tmp->value_ << " ";
      tmp = tmp->next_;
    }
    std::cout << std::endl;
  };

 private:
  size_type size_ = 0;
  Node *head_;
  Node *tail_;

  void tail_init();
  void mergeSort(Node **tmp, size_type size);
  void reconnectingPrev();
  void zeroSize();
};

template <class T>
class list<T>::Node {
 public:
  Node(T data);

 public:
  T value_;
  Node *next_;
  Node *prev_;
};

template <class T>
class list<T>::ListConstIterator {
 public:
  ListConstIterator(){};
  ListConstIterator(Node *ptr);

  const T &operator*();
  typename list<T>::ListConstIterator operator++();
  typename list<T>::ListConstIterator operator--();
  bool operator==(const ListConstIterator it);
  bool operator!=(const ListConstIterator it);

  const Node *Get() { return ptr_; }

 private:
  const Node *ptr_;
};

template <class T>
class list<T>::ListIterator {
 public:
  ListIterator(){};
  ListIterator(Node *l);

  T &operator*();
  typename list<T>::ListIterator operator++();
  typename list<T>::ListIterator operator--();
  bool operator==(const ListIterator it);
  bool operator!=(const ListIterator it);

  Node *Get() { return ptr_; }

 private:
  Node *ptr_;
};

// begin class const_iterator foo

template <class T>
list<T>::ListConstIterator::ListConstIterator(Node *ptr) : ptr_(ptr) {}

template <class T>
const T &list<T>::ListConstIterator::operator*() {
  return ptr_->value_;
}

template <class T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++() {
  ptr_ = ptr_->next_;
  return *this;
}

template <class T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--() {
  ptr_ = ptr_->prev_;
  return *this;
}

template <class T>
bool list<T>::ListConstIterator::operator==(const ListConstIterator it) {
  return ptr_ == it.ptr_ ? 1 : 0;
}

template <class T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator it) {
  return ptr_ == it.ptr_ ? 0 : 1;
}

// end class const_iterator foo

// begin class iterator foo

template <class T>
list<T>::ListIterator::ListIterator(Node *n) : ptr_(n) {}

template <class T>
T &list<T>::ListIterator::operator*() {
  return ptr_->value_;
}

template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator++() {
  ptr_ = ptr_->next_;
  return *this;
}

template <class T>
typename list<T>::ListIterator list<T>::ListIterator::operator--() {
  ptr_ = ptr_->prev_;
  return *this;
}

template <class T>
bool list<T>::ListIterator::operator==(const ListIterator it) {
  return ptr_ == it.ptr_ ? 1 : 0;
}

template <class T>
bool list<T>::ListIterator::operator!=(const ListIterator it) {
  return ptr_ == it.ptr_ ? 0 : 1;
}

// end class iterator foo

// class list foo

template <class T>
void list<T>::clear() {
  while (head_ != tail_) {
    pop_front();
  }
  tail_->prev_ = tail_;
}

template <class T>
typename list<T>::iterator list<T>::end() const {
  return iterator(tail_);
}

template <class T>
typename list<T>::iterator list<T>::begin() const {
  return iterator(head_);
}

template <class T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(tail_);
}

template <class T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(head_);
}

template <class T>
bool list<T>::empty() const noexcept {
  return size_ == 0 ? true : false;
}

template <class T>
size_t list<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(Node) / 2;
}

template <class T>
list<T>::Node::Node(T data) {
  next_ = prev_ = nullptr;
  value_ = data;
}

template <class T>
void list<T>::tail_init() {
  Node *tmp = new Node(T());
  size_ = 0;
  head_ = tmp;
  tail_ = tmp;
  tmp->next_ = tmp;
  tmp->prev_ = tmp;
};

template <class T>
list<T>::list() {
  tail_init();
};

template <class T>
list<T>::list(size_type n) {
  tail_init();
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
};

template <class T>
list<T>::list(std::initializer_list<value_type> const &items) {
  tail_init();
  auto iter = items.begin();
  for (size_type i = 0; i < items.size(); ++i) {
    push_back(*(iter + i));
  }
};

template <class T>
list<T>::list(const list &l) {
  tail_init();
  Node *ptr = l.head_;
  for (size_type i = 0; i < l.size_; ++i) {
    push_back(ptr->value_);
    ptr = ptr->next_;
  }
};

template <class T>
list<T>::list(list &&l) noexcept {
  tail_init();
  std::swap(size_, l.size_);
  std::swap(head_, l.head_);
  std::swap(tail_, l.tail_);
};

template <class T>
list<T>::~list() {
  while (head_ != tail_) {
    pop_front();
  }
  delete tail_;
};

template <class T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this == &l) return *this;
  size_ = 0;
  std::swap(head_, l.head_);
  std::swap(size_, l.size_);
  std::swap(tail_, l.tail_);
  return *this;
}

template <class T>
list<T> &list<T>::operator=(const list &l) {
  if (this == &l) return *this;
  list<T> tmp(l);
  *this = std::move(tmp);
  return *this;
}

template <class T>
void list<T>::push_back(const_reference value) {
  Node *tmp = new Node(value);
  size_++;
  tail_->value_ = size_;
  tmp->next_ = tail_;
  tmp->prev_ = tail_->prev_;
  tail_->prev_ = tmp;
  if (head_ == tail_) {
    head_ = tmp;
    tail_->next_ = head_;
  } else {
    Node *ptr = tmp->prev_;
    ptr->next_ = tmp;
  }
};

template <class T>
void list<T>::push_front(const_reference value) {
  Node *tmp = new Node(value);
  size_++;
  tail_->value_ = size_;
  tmp->next_ = head_;
  tmp->prev_ = tail_;
  tail_->next_ = tmp;
  if (head_ != tail_) {
    Node *ptr = head_;
    ptr->prev_ = tmp;
  }
  head_ = tmp;
};

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *elem = new Node(value);
  size_++;
  tail_->value_ = size_;
  Node *tmp = pos.Get();
  elem->prev_ = tmp->prev_;
  tmp->prev_->next_ = elem;
  elem->next_ = tmp;
  tmp->prev_ = elem;
  return iterator(elem);
}

template <class T>
void list<T>::erase(iterator pos) {
  Node *tmp = pos.Get();
  size_--;
  tail_->value_ = size_;
  tmp->prev_->next_ = tmp->next_;
  tmp->next_->prev_ = tmp->prev_;
  delete tmp;
}

template <class T>
void list<T>::pop_front() {
  if (head_ != tail_) {
    Node *tmp = head_;
    head_ = tmp->next_;
    tmp->prev_ = tail_;
    tail_->next_ = head_;
    delete tmp;
    size_--;
    tail_->value_ = size_;
  }
}

template <class T>
void list<T>::pop_back() {
  if (tail_ != head_) {
    Node *tmp = tail_->prev_;
    tmp->prev_->next_ = tail_;
    tail_->prev_ = tmp->prev_;
    head_ = tail_->next_;
    delete tmp;
    size_--;
    tail_->value_ = size_;
  }
}

template <class T>
void list<T>::swap(list &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template <class T>
void list<T>::merge(list &other) {
  if (this == &other) return;
  Node *fir = head_;
  Node *sec = other.head_;
  Node *res = tail_;
  while (fir != tail_ && sec != other.tail_) {
    if (fir->value_ <= sec->value_) {
      res->next_ = fir;
      fir = fir->next_;
    } else {
      res->next_ = sec;
      sec = sec->next_;
    }
    res = res->next_;
  }
  if (fir != tail_) {
    res->next_ = fir;
  } else {
    res->next_ = sec;
    other.tail_->prev_->next_ = tail_;
  }
  head_ = tail_->next_;
  head_->prev_ = tail_;
  reconnectingPrev();
  size_ += other.size_;
  tail_->value_ = size_;
  other.zeroSize();
}

template <class T>
void list<T>::splice(const_iterator pos, list &other) {
  if (!other.size_) return;
  if (!size_) {
    tail_->next_ = other.tail_->next_;
    tail_->prev_ = other.tail_->prev_;
    other.tail_->prev_->next_ = tail_;
    head_ = tail_->next_;
    head_->prev_ = tail_;
  } else if (pos.Get() == head_) {
    Node *tmp = head_;
    head_ = other.head_;
    head_->prev_ = tail_;
    tail_->next_ = head_;
    tmp->prev_ = other.tail_->prev_;
    other.tail_->prev_->next_ = tmp;
  } else {
    Node *tmp = pos.Get()->prev_;
    Node *tmp2 = tmp->next_;
    tmp2->prev_ = other.tail_->prev_;
    other.tail_->prev_->next_ = tmp2;
    tmp->next_ = other.head_;
    other.head_->prev_ = tmp;
  }
  size_ += other.size_;
  tail_->value_ = size_;
  other.zeroSize();
}

template <class T>
void list<T>::reverse() {
  Node *tmp = head_;
  head_ = tail_->prev_;
  while (tmp != tail_) {
    Node *tmp2 = tmp->next_;
    tmp->next_ = tmp->prev_;
    tmp->prev_ = tmp2;
    tmp = tmp->prev_;
  }
  tmp = tail_->next_;
  tail_->next_ = tail_->prev_;
  tail_->prev_ = tmp;
}

template <class T>
void list<T>::unique() {
  Node *uni = head_;
  while (uni != tail_) {
    while (uni->value_ == uni->next_->value_) {
      iterator it(uni->next_);
      erase(it);
    }
    uni = uni->next_;
  }
}

template <class T>
void list<T>::sort() {
  if (size_ <= 1) return;
  tail_->prev_->next_ = nullptr;
  mergeSort(&head_, size_);
  Node *tmp = head_;
  for (size_type i = 0; i < size_ - 1; ++i) tmp = tmp->next_;
  tmp->next_ = tail_;
  tail_->next_ = head_;
  head_->prev_ = tail_;
  reconnectingPrev();
}

template <class T>
void list<T>::reconnectingPrev() {
  Node *tmp = head_;
  while (tmp != tail_) {
    Node *next = tmp->next_;
    next->prev_ = tmp;
    tmp = tmp->next_;
  }
}

template <class T>
void list<T>::mergeSort(Node **temp, size_type size) {
  if (size <= 1) return;
  Node *left = *temp;
  Node *tmp = *temp;
  size_type left_size = size / 2;
  size_type right_size = size - left_size;
  for (size_type i = 0; i < left_size; ++i) tmp = tmp->next_;
  Node *right = tmp;
  for (size_type i = 0; i < right_size - 1; ++i) tmp = tmp->next_;
  right->prev_->next_ = nullptr;
  tmp->next_ = nullptr;
  mergeSort(&left, left_size);
  mergeSort(&right, right_size);
  Node *start = nullptr;
  if (left->value_ <= right->value_) {
    start = left;
    left = left->next_;
  } else {
    start = right;
    right = right->next_;
  }
  Node *res = start;
  while (left != nullptr && right != nullptr) {
    if (left->value_ <= right->value_) {
      res->next_ = left;
      left = left->next_;
    } else {
      res->next_ = right;
      right = right->next_;
    }
    res = res->next_;
  }
  if (left != nullptr) {
    res->next_ = left;
  } else {
    res->next_ = right;
  }
  *temp = start;
}

template <class T>
void list<T>::zeroSize() {
  size_ = 0;
  tail_->value_ = size_;
  head_ = tail_;
  tail_->next_ = tail_;
  tail_->prev_ = tail_;
}

template <class T>
template <typename... Args>
typename list<T>::ListIterator list<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  if (!sizeof...(args)) return iterator(head_);
  list<T> tmp{args...};
  size_ += tmp.size_;
  Node *left = pos.Get()->prev_;
  Node *right = left->next_;
  left->next_ = tmp.head_;
  tmp.head_->prev_ = left;
  right->prev_ = tmp.tail_->prev_;
  tmp.tail_->prev_->next_ = right;
  tmp.zeroSize();
  return iterator(head_);
}

template <class T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  if (!sizeof...(args)) return;
  list<T> tmp{args...};
  size_ += tmp.size_;
  tail_->prev_->next_ = tmp.head_;
  tmp.head_->prev_ = tail_->prev_;
  tail_->prev_ = tmp.tail_->prev_;
  tmp.tail_->prev_->next_ = tail_;
  tmp.zeroSize();
}

template <class T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  if (!sizeof...(args)) return;
  list<T> tmp{args...};
  size_ += tmp.size_;
  tail_->next_ = tmp.head_;
  tmp.head_->prev_ = tail_;
  head_->prev_ = tmp.tail_->prev_;
  tmp.tail_->prev_->next_ = head_;
  head_ = tmp.head_;
  tmp.zeroSize();
}

}  // namespace my

#endif  // CPP2_S21_CONTAINERS_2_S21_LIST_H