#ifndef A2_SimpleNavigator_v1_0_CPP_1_S21_STACK_H
#define A2_SimpleNavigator_v1_0_CPP_1_S21_STACK_H

#include "my_list.h"

namespace my {

class IStack {
 public:
  //   virtual stack() = 0;
  virtual void push(const int &value) = 0;
  virtual int pop() = 0;
  virtual const int &top() const = 0;
};

class Stack : public IStack {
 public:
  Stack();
  Stack(std::initializer_list<int> const &items);
  Stack(const Stack &s);
  Stack(Stack &&s) noexcept;
  ~Stack();

  Stack &operator=(const Stack &s);
  Stack &operator=(Stack &&s) noexcept;

  void push(const int &value) override;
  int pop() override;
  const int &top() const override;

  bool empty() const noexcept;
  size_t size() const noexcept;

  void swap(Stack &other);

 private:
  my::list<int> c_;
};

}  // namespace my

#endif  // A2_SimpleNavigator_v1_0_CPP_1_S21_STACK_H
