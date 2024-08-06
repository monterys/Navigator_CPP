#include "my_queue.h"

namespace my {

Queue::Queue() : c_() {}
Queue::Queue(std::initializer_list<int> const &items) : c_(items) {}
Queue::Queue(const Queue &s) : c_(s.c_) {}
Queue::Queue(Queue &&s) noexcept : c_(std::move(s.c_)) {}
Queue::~Queue() {}

Queue &Queue::operator=(const Queue &s) {
  c_ = s.c_;
  return *this;
}

Queue &Queue::operator=(Queue &&s) noexcept {
  while (!empty()) {
    pop();
  }
  std::swap(c_, s.c_);
  return *this;
}

void Queue::push(const int &value) { c_.push_back(value); }

int Queue::pop() {
  int return_value{};
  if (!c_.empty()) {
    return_value = c_.front();
    c_.pop_front();
  }
  return return_value;
}

const int &Queue::front() const { return c_.front(); }

const int &Queue::back() const { return c_.back(); }

bool Queue::empty() const noexcept { return c_.empty(); }

size_t Queue::size() const noexcept { return c_.size(); }

void Queue::swap(Queue &other) { std::swap(c_, other.c_); }

}  // namespace my
