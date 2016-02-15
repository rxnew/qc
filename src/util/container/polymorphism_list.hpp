#pragma once

#include <iterator>
#include <memory>
#include <algorithm>
#include <cassert>

namespace util {
namespace container {
template <class T>
class PolymorphismList {
 private:
  struct Node;
  class Iterator;
  class ConstIterator;

  using P = std::unique_ptr<T>;

  Node* top_;
  Node* rear_;
  size_t size_;

  auto push_front_(Node* node) -> void;
  auto push_back_(Node* node) -> void;
  auto insert_(ConstIterator pos, Node* node) -> Iterator;
  auto last_() noexcept -> Iterator;
  auto last_() const noexcept -> ConstIterator;

 public:
  using value_type = T;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  PolymorphismList();
  template <class U = T>
  explicit PolymorphismList(size_t size);
  template <class U>
  PolymorphismList(size_t size, const U& value);
  template <class InputIterator>
  PolymorphismList(InputIterator first, InputIterator last);
  PolymorphismList(const PolymorphismList& other);
  PolymorphismList(PolymorphismList&& other);
  PolymorphismList(std::initializer_list<T> list);
  ~PolymorphismList();
  auto operator=(const PolymorphismList& other) -> PolymorphismList&;
  auto operator=(PolymorphismList&& other) -> PolymorphismList&;
  auto operator=(std::initializer_list<T> list) -> PolymorphismList&;
  auto operator==(const PolymorphismList& other) const -> bool;
  auto operator!=(const PolymorphismList& other) const -> bool;
  auto begin() noexcept -> Iterator;
  auto begin() const noexcept -> ConstIterator;
  auto end() noexcept -> Iterator;
  auto end() const noexcept -> ConstIterator;
  auto cbegin() const noexcept -> ConstIterator;
  auto cend() const noexcept -> ConstIterator;
  auto empty() const noexcept -> bool;
  auto size() const noexcept -> size_t;
  auto front() -> T&;
  auto front() const -> const T&;
  auto back() -> T&;
  auto back() const -> const T&;
  template <class U = T, class... Args>
  auto emplace_front(Args&&... args) -> void;
  template <class U>
  auto push_front(U&& value) -> void;
  auto pop_front() -> void;
  template <class U = T, class... Args>
  auto emplace_back(Args&&... args) -> void;
  template <class U>
  auto push_back(U&& value) -> void;
  auto pop_back() -> void;
  template <class U = T, class... Args>
  auto emplace(ConstIterator pos, Args&&... args) -> Iterator;
  template <class U>
  auto insert(ConstIterator pos, U&& value) -> Iterator;
  template <class InputIterator>
  auto insert(ConstIterator pos, InputIterator first, InputIterator last)
    -> Iterator;
  auto erase(ConstIterator pos) -> Iterator;
  auto erase(ConstIterator first, ConstIterator last) -> Iterator;
  auto clear() -> void;
  auto remove(const T& value) -> void;

 private:
  struct Node {
    P value_;
    Node* prev_;
    Node* next_;

    Node(P&& value, Node* prev_, Node* next_);
    Node(P&& value);
  };

  class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
   private:
    const PolymorphismList* object_;
    Node* node_;

    Iterator(const PolymorphismList* object, Node* node);

   public:
    Iterator(const Iterator& other);
    auto operator++() -> Iterator&;
    auto operator++(int) -> Iterator;
    auto operator--() -> Iterator&;
    auto operator--(int) -> Iterator;
    auto operator*() -> T&;
    auto operator->() -> T*;
    auto operator==(const Iterator& other) const -> bool;
    auto operator!=(const Iterator& other) const -> bool;
    operator ConstIterator() const;

    friend class PolymorphismList;
  };

  class ConstIterator
    : public std::iterator<std::bidirectional_iterator_tag, T> {
   private:
    const PolymorphismList* object_;
    const Node* node_;

    ConstIterator(const PolymorphismList* object, const Node* node);

   public:
    ConstIterator(const ConstIterator& other);
    auto operator++() -> ConstIterator&;
    auto operator++(int) -> ConstIterator;
    auto operator--() -> ConstIterator&;
    auto operator--(int) -> ConstIterator;
    auto operator*() -> const T&;
    auto operator->() -> const T*;
    auto operator==(const ConstIterator& other) const -> bool;
    auto operator!=(const ConstIterator& other) const -> bool;

    friend class PolymorphismList;
  };
};

template <class T>
auto PolymorphismList<T>::push_front_(Node* node) -> void {
  if(this->size_) this->top_->prev_ = node;
  else            this->rear_ = node;
  this->top_ = node;
  this->size_++;
}

template <class T>
auto PolymorphismList<T>::push_back_(Node* node) -> void {
  if(this->size_) this->rear_->next_ = node;
  else            this->top_ = node;
  this->rear_ = node;
  this->size_++;
}

template <class T>
auto PolymorphismList<T>::insert_(ConstIterator pos, Node* node) -> Iterator {
  if(pos == this->cbegin())    this->push_front_(node);
  else if(pos == this->cend()) this->push_back_(node);
  else {
    auto prev = const_cast<Node*>(pos.node_->prev_);
    auto next = const_cast<Node*>(pos.node_);
    node->prev_ = prev;
    node->next_ = next;
    prev->next_ = node;
    next->prev_ = node;
    this->size_++;
  }
  return Iterator(this, node);
}

template <class T>
inline auto PolymorphismList<T>::last_() noexcept -> Iterator {
  return Iterator(this, this->rear_);
}

template <class T>
inline auto PolymorphismList<T>::last_() const noexcept -> ConstIterator {
  return ConstIterator(this, this->rear_);
}

template <class T>
inline PolymorphismList<T>::PolymorphismList()
  : top_(nullptr), rear_(nullptr), size_(0) {
}

template <class T>
template <class U>
PolymorphismList<T>::PolymorphismList(size_t size) : PolymorphismList<T>() {
  while(this->size_ < size) this->emplace_back<U>();
}

template <class T>
template <class U>
PolymorphismList<T>::PolymorphismList(size_t size, const U& value)
  : PolymorphismList<T>() {
  while(this->size_ < size) this->push_back(value);
}

template <class T>
template <class InputIterator>
inline PolymorphismList<T>::PolymorphismList(InputIterator first, \
                                             InputIterator last)
  : PolymorphismList<T>() {
  this->insert(this->cbegin(), first, last);
}

template <class T>
inline PolymorphismList<T>::PolymorphismList(const PolymorphismList<T>& other)
  : PolymorphismList<T>() {
  this->operator=(other);
}

template <class T>
inline PolymorphismList<T>::PolymorphismList(PolymorphismList<T>&& other)
  : top_(other.top_), rear_(other.rear_), size_(other.size_) {
  this->operator=(std::move(other));
}

template <class T>
inline PolymorphismList<T>::PolymorphismList(std::initializer_list<T> list)
  : PolymorphismList<T>() {
  this->operator=(list);
}

template <class T>
inline PolymorphismList<T>::~PolymorphismList() {
  this->clear();
}

template <class T>
auto PolymorphismList<T>::operator=(const PolymorphismList<T>& other)
  -> PolymorphismList<T>& {
  this->clear();
  for(const auto& value : other) this->push_back(value);
  return *this;
}

template <class T>
auto PolymorphismList<T>::operator=(PolymorphismList<T>&& other)
  -> PolymorphismList<T>& {
  this->clear();
  other.top_ = other.rear_ = nullptr;
  other.size_ = 0;
  return *this;
}

template <class T>
auto PolymorphismList<T>::operator=(std::initializer_list<T> list)
  -> PolymorphismList<T>& {
  this->clear();
  for(const auto& value : list) this->push_back(value);
  return *this;
}

template <class T>
auto PolymorphismList<T>::operator==(const PolymorphismList<T>& other) const
  -> bool {
  if(this->size_ != other.size_) return false;
  auto it = this->cbegin();
  auto jt = other.cbegin();
  while(it != this->cend()) {
    if(*it != *jt) return false;
    it++, jt++;
  }
  return true;
}

template <class T>
inline auto PolymorphismList<T>::operator!=(const PolymorphismList<T>& other)
  const -> bool {
  return !(*this == other);
}

template <class T>
inline auto PolymorphismList<T>::begin() noexcept -> Iterator {
  return Iterator(this, this->top_);
}

template <class T>
inline auto PolymorphismList<T>::begin() const noexcept -> ConstIterator {
  return ConstIterator(this, this->top_);
}

template <class T>
inline auto PolymorphismList<T>::end() noexcept -> Iterator {
  return Iterator(this, nullptr);
}

template <class T>
inline auto PolymorphismList<T>::end() const noexcept -> ConstIterator {
  return ConstIterator(this, nullptr);
}

template <class T>
inline auto PolymorphismList<T>::cbegin() const noexcept -> ConstIterator {
  return ConstIterator(this, this->top_);
}

template <class T>
inline auto PolymorphismList<T>::cend() const noexcept -> ConstIterator {
  return ConstIterator(this, nullptr);
}

template <class T>
inline auto PolymorphismList<T>::empty() const noexcept -> bool {
  return !this->size_;
}

template <class T>
inline auto PolymorphismList<T>::size() const noexcept -> size_t {
  return this->size_;
}

template <class T>
inline auto PolymorphismList<T>::front() -> T& {
  return *this->begin();
}

template <class T>
inline auto PolymorphismList<T>::front() const -> const T& {
  return *this->cbegin();
}

template <class T>
inline auto PolymorphismList<T>::back() -> T& {
  return *this->last_();
}

template <class T>
inline auto PolymorphismList<T>::back() const -> const T& {
  return *this->last_();
}

template <class T>
template <class U, class... Args>
inline auto PolymorphismList<T>::emplace_front(Args&&... args) -> void {
  auto p = new U(std::forward<Args>(args)...);
  this->push_front_(new Node(P(p), this->rear_, nullptr));
}

template <class T>
template <class U>
inline auto PolymorphismList<T>::push_front(U&& value) -> void {
  auto p = new U(std::forward<U>(value));
  this->push_front_(new Node(P(p), nullptr, this->top_));
}

template <class T>
auto PolymorphismList<T>::pop_front() -> void {
  if(!this->size_) return;
  auto top = this->top_->next_;
  delete this->top_;
  this->top_ = top;
  if(!top) this->rear_ = nullptr;
  else     top->prev_ = nullptr;
  this->size_--;
}

template <class T>
template <class U, class... Args>
inline auto PolymorphismList<T>::emplace_back(Args&&... args) -> void {
  auto p = new U(std::forward<Args>(args)...);
  this->push_back_(new Node(P(p), this->rear_, nullptr));
}

template <class T>
template <class U>
inline auto PolymorphismList<T>::push_back(U&& value) -> void {
  auto p = new U(std::forward<U>(value));
  this->push_back_(new Node(P(p), this->rear_, nullptr));
}

template <class T>
auto PolymorphismList<T>::pop_back() -> void {
  if(!this->size_) return;
  auto rear = this->rear_->prev_;
  delete this->rear_;
  this->rear_ = rear;
  if(!rear) this->top_ = nullptr;
  else      rear->next_ = nullptr;
  this->size_--;
}

template <class T>
template <class U, class... Args>
inline auto PolymorphismList<T>::emplace(ConstIterator pos, Args&&... args)
  -> Iterator {
  auto p = new U(std::forward<Args>(args)...);
  return this->insert_(pos, new Node(P(p)));
}

template <class T>
template <class U>
inline auto PolymorphismList<T>::insert(ConstIterator pos, U&& value)
  -> Iterator {
  auto p = new U(std::forward<U>(value));
  return this->insert_(pos, new Node(P(p)));
}

template <class T>
template <class InputIterator>
auto PolymorphismList<T>::insert(ConstIterator pos, \
                                 InputIterator first, \
                                 InputIterator last) -> Iterator {
  for(auto it = first; it != last; it++) this->insert(pos, *it);
}

template <class T>
auto PolymorphismList<T>::erase(ConstIterator pos) -> Iterator {
  assert(pos != this->cend());

  auto iter = Iterator(this, pos.node_->next_);

  if(pos == this->cbegin())     this->pop_front();
  else if(pos == this->last_()) this->pop_back();
  else {
    auto prev = const_cast<Node*>(pos.node_->prev_);
    auto next = const_cast<Node*>(pos.node_->next_);
    delete pos.node_;
    prev->next_ = next;
    next->prev_ = prev;
    this->size_--;
  }

  return iter;
}

template <class T>
auto PolymorphismList<T>::erase(ConstIterator first, ConstIterator last)
  -> Iterator {
  while(first != last) first = this->erase(first);
  return this->erase(first);
}

template <class T>
auto PolymorphismList<T>::clear() -> void {
  while(!this->top_) this->pop_back();
}

template <class T>
inline auto PolymorphismList<T>::remove(const T& value) -> void {
  auto pos = std::find(this->cbegin(), this->cend(), value);
  if(pos != this->cend()) this->erase(pos);
}

template <class T>
inline PolymorphismList<T>::Node::Node(P&& value, Node* prev, Node* next)
  : value_(std::move(value)), prev_(prev), next_(next) {
}

template <class T>
inline PolymorphismList<T>::Node::Node(P&& value)
  : value_(std::move(value)), prev_(nullptr), next_(nullptr) {
}
 
template <class T>
inline PolymorphismList<T>::Iterator::Iterator(const PolymorphismList* object, \
                                               Node* node)
  : object_(object), node_(node) {
}

template <class T>
inline PolymorphismList<T>::Iterator::Iterator(const Iterator& other)
  : object_(other.object_), node_(other.node_) {
}

template <class T>
inline auto PolymorphismList<T>::Iterator::operator++() -> Iterator& {
  assert(this->node_);
  this->node_ = this->node_->next_;
  return *this;
}
 
template <class T>
auto PolymorphismList<T>::Iterator::operator++(int) -> Iterator {
  assert(this->node_);
  auto result = *this;
  this->node_ = this->node_->next_;
  return result;
}

template <class T>
inline auto PolymorphismList<T>::Iterator::operator--() -> Iterator& {
  this->node_ = this->node_ ? this->node_->prev_ : object_->rear_;
  assert(this->node_);
  return *this;
}
 
template <class T>
auto PolymorphismList<T>::Iterator::operator--(int) -> Iterator {
  auto result = *this;
  this->node_ = this->node_ ? this->node_->prev_ : object_->rear_;
  assert(this->node_);
  return result;
}

template <class T>
inline auto PolymorphismList<T>::Iterator::operator*() -> T& {
  assert(this->node_);
  return *this->node_->value_;
}

template <class T>
inline auto PolymorphismList<T>::Iterator::operator->() -> T* {
  assert(this->node_);
  return this->node_->value_.get();
}

template <class T>
inline auto PolymorphismList<T>::Iterator::operator==(const Iterator& other)
  const -> bool {
  return this->object_ == other.object_ && this->node_ == other.node_;
}
 
template <class T>
inline auto PolymorphismList<T>::Iterator::operator!=(const Iterator& other)
  const -> bool {
  return !(*this == other);
}

template <class T>
inline PolymorphismList<T>::Iterator::operator ConstIterator() const {
  return ConstIterator(this->object_, this->node_);
}

template <class T>
inline PolymorphismList<T>::ConstIterator::ConstIterator
(const PolymorphismList* object, const Node* node)
  : object_(object), node_(node) {
}

template <class T>
inline PolymorphismList<T>::ConstIterator::ConstIterator
(const ConstIterator& other) : object_(other.object_), node_(other.node_) {
}

template <class T>
inline auto PolymorphismList<T>::ConstIterator::operator++() -> ConstIterator& {
  assert(this->node_);
  this->node_ = this->node_->next_;
  return *this;
}
 
template <class T>
auto PolymorphismList<T>::ConstIterator::operator++(int) -> ConstIterator {
  assert(this->node_);
  auto result = *this;
  this->node_ = this->node_->next_;
  return result;
}

template <class T>
inline auto PolymorphismList<T>::ConstIterator::operator--() -> ConstIterator& {
  this->node_ = this->node_ ? this->node_->prev_ : object_->rear_;
  assert(this->node_);
  return *this;
}
 
template <class T>
auto PolymorphismList<T>::ConstIterator::operator--(int) -> ConstIterator {
  auto result = *this;
  this->node_ = this->node_ ? this->node_->prev_ : object_->rear_;
  assert(this->node_);
  return result;
}

template <class T>
inline auto PolymorphismList<T>::ConstIterator::operator*() -> const T& {
  assert(this->node_);
  return *this->node_->value_;
}

template <class T>
inline auto PolymorphismList<T>::ConstIterator::operator->() -> const T* {
  assert(this->node_);
  return this->node_->value_.get();
}

template <class T>
inline auto PolymorphismList<T>::ConstIterator::operator==
(const ConstIterator& other) const -> bool {
  return this->object_ == other.object_ && this->node_ == other.node_;
}
 
template <class T>
inline auto PolymorphismList<T>::ConstIterator::operator!=
(const ConstIterator& other) const -> bool {
  return !(*this == other);
}
}
}
