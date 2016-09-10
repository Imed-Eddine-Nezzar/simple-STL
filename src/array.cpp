#include "array.hpp"

namespace local {

// default constructor
template <typename T, size_t N>
array<T, N>::array() { }

// copy constructor
template <typename T, size_t N>
array<T, N>::array(const array<T, N>& other) {
    std::copy(other.m_data.get(),
              other.m_data.get() + N,
              m_data.get());
}

// move constructor
template <typename T, size_t N>
array<T, N>::array(array<T, N>&& other) {
    this->swap(other);
}

// intializer_list constructor
template <typename T, size_t N>
array<T, N>::array(std::initializer_list<T> ilist)
{
    if (m_size < ilist.size())
        throw size_miss_match();

    std::copy(ilist.begin(), ilist.end(), m_data.get());
}

// copy assignment
template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(const array<T, N>& other) {
    array<T, N> tmp(other);
    this->swap(tmp);
    return *this;
}

// move assignment
template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& other) {
    this->swap(other);
}

// subscript operator
template <typename T, size_t N>
T& array<T, N>::operator[](size_t pos) {
    return m_data[pos];
}

template <typename T, size_t N>
T& array<T, N>::operator[](size_t pos) const {
    return m_data[pos];
}


// swap function
template <typename T, size_t N>
void array<T, N>::swap(array<T, N>& other) {
    std::swap(this->m_data, other.m_data);
}

} // namespace local