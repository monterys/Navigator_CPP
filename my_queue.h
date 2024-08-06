#ifndef A2_SimpleNavigator_v1_0_CPP_1_S21_QUEUE_H
#define A2_SimpleNavigator_v1_0_CPP_1_S21_QUEUE_H

#include "my_list.h"

namespace my {

class IQueue {
 public:
  // virtual queue() = 0;
  virtual void push(const int &value) = 0;
  virtual int pop() = 0;
  virtual const int &front() const = 0;
  virtual const int &back() const = 0;
};

class Queue : public IQueue {
 public:
  Queue();
  Queue(std::initializer_list<int> const &items);
  Queue(const Queue &s);
  Queue(Queue &&s) noexcept;
  ~Queue();

  Queue &operator=(const Queue &s);
  Queue &operator=(Queue &&s) noexcept;

  void push(const int &value) override;
  int pop() override;
  const int &front() const override;
  const int &back() const override;

  bool empty() const noexcept;
  size_t size() const noexcept;

  void swap(Queue &other);

 private:
  my::list<int> c_;
};

}  // namespace my

#endif  // A2_SimpleNavigator_v1_0_CPP_1_S21_QUEUE_H
