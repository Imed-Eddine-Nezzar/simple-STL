#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <memory>
#include <algorithm>


namespace local {

template <typename T, size_t N>
class array {
public:

    class out_of_range : public std::runtime_error {
    public:
        out_of_range() :
            std::runtime_error("index out of range")
        { }
    };

    class size_miss_match : public std::runtime_error {
    public:
        size_miss_match() :
            std::runtime_error("size miss match")
        {}
    };

    // default constructor
    array();
    // copy constructor
    explicit array(const array<T, N>& other);
    // move constructor
    explicit array(array<T, N>&& other);
    // intializer_list constructor
    array(std::initializer_list<T> ilist);

    // copy assignment
    array<T, N>& operator=(const array<T, N>& other);
    // move assignment
    array<T, N>& operator=(array<T, N>&& other);

    // subscript operator
    T& operator[](size_t pos);
    T& operator[](size_t pos) const;

    inline size_t size() const { return m_size; }

    inline T& at(size_t pos) {
        bound_check(pos);
        return m_data[pos];
    }

    inline T& at(size_t pos) const {
        bound_check(pos);
        return m_data[pos];
    }

    void swap(array<T, N>& other);


private:
    inline void bound_check(size_t pos) {
        if (pos < 0 or pos >= m_size)
            throw out_of_range();
    }
    std::unique_ptr<T[]> m_data = std::make_unique<T[]>(N);
    size_t m_size = N;

    friend std::ostream& operator<<(std::ostream& os,
                                    const array<T, N>& arr) {
        for (size_t i = 0; i < arr.size(); ++i)
            os << arr[i] << " ";
        return os;
    }
};

} // namespace local

#endif // __ARRAY_HPP__