// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;
    explicit Node(const T& val) : data(val), next(nullptr) {}
  };
  Node* head_;

 public:
  TPQueue() : head_(nullptr) {}
  TPQueue(const TPQueue&) = delete;
  TPQueue& operator=(const TPQueue&) = delete;

  ~TPQueue() {
    while (head_ != nullptr) {
      Node* temp = head_;
      head_ = head_->next;
      delete temp;
    }
  }

  void push(const T& item) {
    Node* new_node = new Node(item);
    if (head_ == nullptr || item.prior > head_->data.prior) {
      new_node->next = head_;
      head_ = new_node;
      return;
    }
    Node* current = head_;
    while (current->next != nullptr &&
           current->next->data.prior >= item.prior) {
      current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
  }

  T pop() {
    if (head_ == nullptr) {
      throw std::runtime_error("Empty");
    }
    Node* temp = head_;
    T value = temp->data;
    head_ = head_->next;
    delete temp;
    return value;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
