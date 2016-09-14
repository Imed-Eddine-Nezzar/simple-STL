#ifndef __STACK_ARRAY_HPP__
#define __STACK_ARRAY_HPP__

#include <algorithm>    // std::copy
#include <cstddef>      // ::size_t
#include <memory>       // std::unique_ptr, std::make_unique
#include <stdexcept>    // std::runtime_error
#include <utility>      // std::swap

namespace datastruct {

template <typename T, size_t N>
class stack {
public:
    /********************************************************
    *   constructors
    **/

    // default constructor
    stack();

    // copy constructor
    stack(const stack<T, N>& other);

    // move constructor
    stack(stack<T, N>&& other);

    // assignment operator
    stack<T, N>& operator=(stack<T, N> other);

    /********************************************************
    *   member functions
    **/

    inline bool empty() const noexcept;

    inline size_t size() const noexcept;

    inline size_t   capacity()  const noexcept;

    inline void push(const T& elem);

    inline T& top() const;

    inline void pop();

    inline void swap(stack& other);

private:
    /********************************************************
    *   data members
    **/
    
    size_t m_size = 0;
    size_t m_capcity = N;
    std::unique_ptr<T[]> m_frames = std::make_unique<T[]>(N);

    /********************************************************
    *   Exceptions
    **/

    class stack_exception : public std::runtime_error {
    public:
        explicit stack_exception(const char* what_args):
            std::runtime_error(what_args)
        {}
    };

    class stack_full_exception : public stack_exception {
    public:
        explicit stack_full_exception() :
            stack_exception("maximum size reached")
        {}
    };

    class stack_empty_exception : public stack_exception {
    public:
        explicit stack_empty_exception() :
            stack_exception("no frames on stack")
        {}
    };

    /********************************************************
    *   assertions
    **/

    template <class ExceptionClass>
    inline void assert_that(bool condition) const;

    inline void assert_not_empty() const;

    inline void assert_not_full() const;
}; // class stack

} // namespace datastructure

#endif  // __STACK_ARRAY_HPP__