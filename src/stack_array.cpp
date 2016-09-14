#include "stack_array.hpp"

namespace ds = datastruct;

template <typename T, size_t N>
ds::stack<T, N>::stack() {}

template <typename T, size_t N>
ds::stack<T, N>::stack(const ds::stack<T, N>& other) :
    m_size(other.m_size),
    m_frames(std::make_unique<T[]>(m_capcity))
{
    std::copy(other.m_frames.get(),
              other.m_frames.get() + m_capcity,
              m_frames.get());
}

template <typename T, size_t N>
ds::stack<T, N>::stack(stack<T, N>&& other) {
    this->swap(other);
}

template <typename T, size_t N>
ds::stack<T, N>& ds::stack<T, N>::operator=(stack<T, N> other) {
    this->swap(other);
    return *this;
}

template <typename T, size_t N>
inline bool ds::stack<T, N>::empty() const noexcept {
    return m_size == 0;
}

template <typename T, size_t N>
size_t ds::stack<T, N>::size() const noexcept {
    return m_size;
}

template <typename T, size_t N>
size_t ds::stack<T, N>::capacity() const noexcept {
    return m_capcity;
}

template <typename T, size_t N>
inline void ds::stack<T, N>::push(const T& elem) {
    assert_not_full();
    m_frames[m_size++] = elem;
}
template <typename T, size_t N>
inline T& ds::stack<T, N>::top() const {
    assert_not_empty();
    return m_frames[m_size - 1];
}

template <typename T, size_t N>
inline void ds::stack<T, N>::pop() {
    assert_not_empty();
    m_size -= 1;
}

template <typename T, size_t N>
inline void ds::stack<T, N>::swap(stack& other) {
    std::swap(m_size, other.m_size);
    std::swap(m_frames, other.m_frames);
}
template <typename T, size_t N>
template <class ExceptionClass>
inline void ds::stack<T, N>::assert_that(bool condition) const {
    if (not condition)
        throw ExceptionClass();
}

template <typename T, size_t N>
inline void ds::stack<T, N>::assert_not_empty() const {
    assert_that<stack_empty_exception>(m_size > 0);
}

template <typename T, size_t N>
inline void ds::stack<T, N>::assert_not_full() const {
    assert_that<stack_full_exception>(m_size != m_capcity);
}