#include "my_stack.h"

namespace my {

Stack::Stack() : c_() {}
Stack::Stack(std::initializer_list<int> const &items) : c_(items) {}
Stack::Stack(const Stack &s) : c_(s.c_) {}
Stack::Stack(Stack &&s) noexcept : c_(std::move(s.c_)) {}
Stack::~Stack() {}

Stack &Stack::operator=(const Stack &s) {
  c_ = s.c_;
  return *this;
}

Stack &Stack::operator=(Stack &&s) noexcept {
  while (!empty()) {
    pop();
  }
  std::swap(c_, s.c_);
  return *this;
}

void Stack::push(const int &value) { c_.push_back(value); }

int Stack::pop() {
  int return_value{};
  if (!c_.empty()) {
    return_value = c_.back();
    c_.pop_back();
  }
  return return_value;
}

const int &Stack::top() const { return c_.back(); }

bool Stack::empty() const noexcept { return c_.empty(); }

size_t Stack::size() const noexcept { return c_.size(); }

void Stack::swap(Stack &other) { std::swap(c_, other.c_); }

}  // namespace my
