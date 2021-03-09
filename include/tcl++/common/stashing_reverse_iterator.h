#ifndef COMMON_STASHING_REVERSE_ITERATOR_H
#define COMMON_STASHING_REVERSE_ITERATOR_H

#include <iterator>
#include <optional>

namespace tcl::common {
template <class Iterator>
class stashing_reverse_iterator {
 public:
  using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
  using value_type = typename std::iterator_traits<Iterator>::value_type;
  using difference_type = typename std::iterator_traits<Iterator>::difference_type;
  using reference = typename std::iterator_traits<Iterator>::reference;
  using pointer = typename std::iterator_traits<Iterator>::pointer;

  stashing_reverse_iterator() : current() {}

  explicit stashing_reverse_iterator(Iterator x) : current(x) {}

  template <class U>
  stashing_reverse_iterator(const stashing_reverse_iterator<U>& u) : current(u.current) {}

  template <class U>
  stashing_reverse_iterator& operator=(const stashing_reverse_iterator<U>& u) {
    current = u.base();
    return *this;
  }

  Iterator base() const { return current; }

  /**
   * This differs from std::reverse_iterator::operator* in that it stores the
   * dereferenced iterator internally so that it doesn't go out of scope. The
   * standard version will return an invalid reference in that case.
   *
   * @note This results in an extra element overhead for this class.
   */
  reference operator*() const {
    m_deref_tmp = current;
    --m_deref_tmp.value();
    return **m_deref_tmp;
  }

  pointer operator->() const { return std::addressof(operator*()); }

  stashing_reverse_iterator& operator++() {
    --current;
    return *this;
  }

  stashing_reverse_iterator operator++(int) {
    stashing_reverse_iterator tmp = *this;
    --current;
    return tmp;
  }

  stashing_reverse_iterator& operator--() {
    ++current;
    return *this;
  }

  stashing_reverse_iterator operator--(int) {
    stashing_reverse_iterator tmp = *this;
    ++current;
    return tmp;
  }

  stashing_reverse_iterator operator+(difference_type n) const {
    return stashing_reverse_iterator(current - n);
  }

  stashing_reverse_iterator& operator+=(difference_type n) {
    current -= n;
    return *this;
  }

  stashing_reverse_iterator operator-(difference_type n) const {
    return stashing_reverse_iterator(current + n);
  }

  stashing_reverse_iterator& operator-=(difference_type n) {
    current += n;
    return *this;
  }

  // Differs from reverse_iterator::operator[]:
  // 1. const qualifier removed because this function makes use of operator*
  reference operator[](difference_type n) { return *(*this + n); }

 protected:
  Iterator current;

 private:
  // Note this element must be mutable so that we don't require the iterator to
  // be non-const when dereferencing.  Also, we use optional to avoid requiring
  // a default constructor (only a copy constructor is necessary).
  mutable std::optional<Iterator> m_deref_tmp;
};

template <class Iterator1, class Iterator2>
bool operator==(const stashing_reverse_iterator<Iterator1>& x,
                const stashing_reverse_iterator<Iterator2>& y) {
  return x.base() == y.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const stashing_reverse_iterator<Iterator1>& x,
               const stashing_reverse_iterator<Iterator2>& y) {
  return x.base() > y.base();
}

template <class Iterator1, class Iterator2>
bool operator!=(const stashing_reverse_iterator<Iterator1>& x,
                const stashing_reverse_iterator<Iterator2>& y) {
  return !(x.base() == y.base());
}

template <class Iterator1, class Iterator2>
bool operator>(const stashing_reverse_iterator<Iterator1>& x,
               const stashing_reverse_iterator<Iterator2>& y) {
  return x.base() < y.base();
}

template <class Iterator1, class Iterator2>
bool operator>=(const stashing_reverse_iterator<Iterator1>& x,
                const stashing_reverse_iterator<Iterator2>& y) {
  return x.base() <= y.base();
}

template <class Iterator1, class Iterator2>
bool operator<=(const stashing_reverse_iterator<Iterator1>& x,
                const stashing_reverse_iterator<Iterator2>& y) {
  return x.base() >= y.base();
}

template <class Iterator1, class Iterator2>
auto operator-(const stashing_reverse_iterator<Iterator1>& x,
               const stashing_reverse_iterator<Iterator2>& y) -> decltype(y.base() - x.base()) {
  return y.base() - x.base();
}

template <class Iterator>
stashing_reverse_iterator<Iterator> operator+(
    typename stashing_reverse_iterator<Iterator>::difference_type n,
    const stashing_reverse_iterator<Iterator>& x) {
  return stashing_reverse_iterator<Iterator>(x.base() - n);
}

template <class Iterator>
stashing_reverse_iterator<Iterator> make_stashing_reverse_iterator(Iterator i) {
  return stashing_reverse_iterator<Iterator>(i);
}
}  // namespace common

#endif
