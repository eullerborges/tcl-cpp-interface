#ifndef TCL_LIST_H
#define TCL_LIST_H

#include "Object.h"
#include "String.h"
#include "tcl++/common/stashing_reverse_iterator.h"

#include <optional>

namespace tcl {

class List : public Object {
 public:
  using Object::Object;

  List();

  //! Appends a given Tcl object to this list and returns reference to self.
  List& append(const Object& obj);
  //! Convenience method to ease up the addition of strings.
  List& append(const String& obj) { return append(static_cast<const Object&>(obj)); }
  //! Splices all elements from another list into this one (by copy).
  bool splice(const List& l);
  //! Returns the current list's size.
  std::size_t size() const;

  template <bool Const>
  class base_iterator;
  using iterator = base_iterator<false>;
  using const_iterator = base_iterator<true>;
  const_iterator begin() const;
  const_iterator end() const;
  iterator begin();
  iterator end();
  using reverse_iterator = common::stashing_reverse_iterator<iterator>;
  reverse_iterator rbegin();
  reverse_iterator rend();

 private:
  iterator getEndIterator();
};

template <bool Const>
class List::base_iterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = Object;
  using difference_type = std::ptrdiff_t;
  using pointer = typename std::conditional_t<Const, const Object*, Object*>;
  using reference = typename std::conditional_t<Const, const Object&, Object&>;

  explicit base_iterator(const List* parent, std::size_t idx) : m_parent(parent), m_idx(idx) {}

  base_iterator& operator++() { return operator+=(1); }
  base_iterator operator++(int);
  base_iterator& operator+=(std::size_t count) {
    m_idx += count;
    return *this;
  }
  base_iterator& operator--() { return operator-=(1); }
  base_iterator operator--(int);
  base_iterator& operator-=(std::size_t count) {
    m_idx -= count;
    return *this;
  }
  std::size_t operator-(const base_iterator& other) { return m_idx - other.m_idx; }

  bool operator==(const base_iterator& other) const {
    return m_parent == other.m_parent && m_idx == other.m_idx;
  }
  bool operator!=(const base_iterator& other) const { return !(*this == other); }

  pointer operator->() const;
  reference operator*() const { return *operator->(); }

 private:
  const List* m_parent{nullptr};
  std::size_t m_idx{0};
  std::optional<Object> m_value;
};

// Implementation detail
inline List::iterator List::begin() { return iterator(this, 0); }
inline List::iterator List::end() { return iterator(this, size()); }
inline List::const_iterator List::begin() const { return const_iterator(this, 0); }
inline List::const_iterator List::end() const { return const_iterator(this, size()); }
inline List::reverse_iterator List::rbegin() {
  return common::make_stashing_reverse_iterator(end());
}
inline List::reverse_iterator List::rend() {
  return common::make_stashing_reverse_iterator(begin());
}

template <bool Const>
List::base_iterator<Const> List::base_iterator<Const>::operator++(int) {
  List::base_iterator<Const> retval = *this;
  ++(*this);
  return retval;
}

template <bool Const>
List::base_iterator<Const> List::base_iterator<Const>::operator--(int) {
  List::base_iterator<Const> retval = *this;
  --(*this);
  return retval;
}

};  // namespace tcl

#endif
