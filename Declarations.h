

#ifndef VECTOR_DECLARATIONS_H
#define VECTOR_DECLARATIONS_H
#include <iostream>
#include <cmath>
template<typename T>
class Vector
{
    T* values;
    size_t  v_size;
    size_t  v_capacity;

public:
    //iterators
    //======================================
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    //======================================
    //constructors/destructors
    //======================================
    Vector();
    Vector(size_t sz);
    Vector(size_t sz, const T& v );
    Vector(const std::initializer_list<T>& i_list );
    Vector(const Vector&);
    Vector(const Vector&&);

    ~Vector()
    {
        delete []  values;
    }
    //======================================
    // operators
    Vector<T>& operator=(Vector<T>);
    Vector<T>& operator=(Vector<T>&&) noexcept;
    //======================================

    // element access
    //======================================
    const T& front() const;
    T& front(); // actually I don't see why would we need this function to be a reference, I think it should be only a const reference, any insight?
    const T& back() const;
    T& back();
    T& operator[ ](size_t i);
    const T& operator[ ](size_t i) const;
    T& at(size_t i);
    const T& at(size_t i) const;
    constexpr T* data() noexcept;
    constexpr const T* data() const noexcept;
    //======================================
    // iterators
    //======================================
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator  cend() const;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator crend() const noexcept;
    //======================================

    // Modifiers
    template<typename... ARGS>
    void emplace_back(ARGS&&... args); // since C++17 the std::vector::emplace_back() function type is a reference T&, why is that? what does this change brings to the table?
    template<typename... ARGS>
    iterator emplace(const T* pos, ARGS&&... args);
    iterator insert(iterator pos, const T& v );
    iterator insert(const_iterator pos, const T& v );
    iterator insert(const_iterator pos, T&& v );
    void insert(iterator pos, size_t n, const T& v );
    iterator insert(const_iterator pos, size_t n, const T& v );
    void push_back(const T& v);
    void push_back(T&& v);
    void pop_back();
    iterator erase( const_iterator pos );
    iterator erase( iterator first, iterator last );
    void clear() noexcept;
    void resize(size_t n);
    void resize(size_t n, const T& v);


    // capacity
    int size() const noexcept;
    int capacity() const noexcept;
    constexpr bool empty() const noexcept;
    void reserve(size_t n);
    void shrink_to_fit();

    // Non-Member Functions
    template<typename H> friend bool operator==(const Vector<H>& lhs, const Vector<H>& rhs);

    // see https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    friend void swap(Vector& first, Vector& second)
    {
        using std::swap;

        swap(first.v_size, second.v_size);
        swap(first.v_capacity, second.v_capacity);
        swap(first.values, second.values);
    }

private:
    bool ctor_initialized = false;
    void reallocate();
};
#include "Implementations.hpp"
#endif //VECTOR_DECLARATIONS_H
