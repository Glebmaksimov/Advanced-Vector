
template<typename T>
inline Vector<T>::Vector()
{
    v_size = 0;
    v_capacity = 0;
    values = nullptr;
}

template<typename T>
inline Vector<T>::Vector(size_t sz)
{
    ctor_initialized = true;

    v_size = sz;
    v_capacity = sz;

    values = new T[v_capacity];

    for(int i = 0; i < sz; ++i)
        values[ i ] = T();
}

template<typename T>
inline Vector<T>::Vector(size_t sz, const T& v)
{
    ctor_initialized = true;

    v_size = sz;
    v_capacity = sz;

    values = new T[v_capacity];

    for(int i = 0; i < sz; ++i)
        values[ i ] = v;
}

template<typename T>
inline Vector<T>::Vector(const std::initializer_list<T>& i_list)
{
    int sz = i_list.size();

    v_size = sz;
    v_capacity = sz;

    values = new T[v_capacity];

    for(auto iter = i_list.begin(), i = 0; iter != i_list.end(); ++i, ++iter)
        values[ i ] = *iter;
}

template<typename T>
inline Vector<T>::Vector(const Vector<T>& src) : v_size(src.v_size), v_capacity(src.v_capacity),
                                                 values(new T[v_capacity])
{
    for(int i = 0; i < v_size; ++i)
        values[ i ] = src.values[ i ];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> src)
{
    swap(*this, src);

    return *this;
}

template<typename T>
inline Vector<T>::Vector(const Vector<T>&& mv)
{
    swap(*this, mv);
}

template<typename T>
inline const T& Vector<T>::back() const
{
    return values[v_size - 1];
}

template<typename T>
inline T& Vector<T>::back()
{
    return values[v_size - 1];
}

template<typename T>
inline const T& Vector<T>::front() const
{
    return values[0];
}

template<typename T>
inline T& Vector<T>::front()
{
    return values[0];
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::begin() noexcept
{
    return values;
}

template<typename T>
inline typename Vector<T>::const_iterator Vector<T>::begin() const noexcept
{
    return values;
}

template<typename T>
inline typename Vector<T>::iterator  Vector<T>::end() noexcept
{
    return values + v_size;
}

template<typename T>
inline typename Vector<T>::const_iterator  Vector<T>::end() const noexcept
{
    return values + v_size;
}

template<typename T>
inline typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    return values;
}

template<typename T>
inline typename Vector<T>::const_iterator  Vector<T>::cend() const
{
    return values + v_size;
}

template<typename T>
inline typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
{
    return reverse_iterator(end());
}

template<typename T>
inline typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
{
    return reverse_iterator(begin());
}

template<typename T>
inline typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept
{
    return rbegin();
}

template<typename T>
inline typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept
{
    return rend();
}




template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T>&& mv) noexcept
{
    swap(*this, mv);

    return *this;
}
template<typename T>
inline T& Vector<T>::operator[ ] (size_t i)
{
    return values[ i ];
}

template<typename T>
inline T& Vector<T>::at (size_t i)
{
    if(i >= v_size)
        throw std::runtime_error("out of range exception");
    else
        return values[ i ];
}

template<typename T>
inline const T& Vector<T>::operator[ ] (size_t i) const
{
    return values[ i ];
}

template<typename T>
inline const T& Vector<T>::at (size_t i) const
{
    if(i >= v_size)
        throw std::runtime_error("out of range exception");
    else
        return values[ i ];
}

template<typename T>
inline constexpr T* Vector<T>::data() noexcept
{
    return values;
}

template<typename T>
inline constexpr const T* Vector<T>::data() const noexcept
{
    return values;
}

template<typename T>
template<typename... ARGS>
void Vector<T>::emplace_back(ARGS&&... args)
{
    if(v_size == v_capacity)
    {
        if(ctor_initialized)
            v_capacity *= 2;
        else
        {
            if (v_size == 0)
                v_capacity = 1;
            else if(v_size < 8)
                v_capacity++;
            else if (v_size >= 8)
                v_capacity *= 2;
        }

        reallocate();
    }

    values[v_size++] = std::move(T(std::forward<ARGS>(args)...));
}

template<typename T>
template<typename... ARGS>
inline typename Vector<T>::iterator Vector<T>::emplace(const T* pos, ARGS&&... args)
{

    const size_t dist = pos - begin();

    if(dist == v_capacity)
    {
        emplace_back(T(std::forward<T>(args)...));
    }
    else
    {
        if(v_size == v_capacity)
        {
            v_capacity *= 2;

            reallocate();
        }

        std::move_backward(begin() + dist, end(), end() + 1);

        iterator iter = &values[dist];

        *iter = std::move(T(std::forward<ARGS>(args)...));

        ++v_size;

        return iter;
    }
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T& v )
{
    emplace(pos, v);
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const T& v )
{
    emplace(pos, v);
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, T&& v )
{
    emplace(pos, std::forward<T>(v));
}

template<typename T>
void Vector<T>::insert(iterator pos, size_t n, const T& v )
{
    const size_t dist = pos - begin();

    if(v_size + n > v_capacity)
    {
        v_capacity *= 2;

        reallocate();
    }

    std::move_backward(begin() + dist, end(), end() + n);

    for(int i = dist; i < dist + n; ++i)
        values[ i ] = v;

    v_size += n;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_t n, const T& v )
{
    const size_t dist = pos - begin();

    if(v_size + n > v_capacity)
    {
        v_capacity *= 2;

        reallocate();
    }

    T* iter = &values[dist];

    std::move_backward(begin() + dist, end(), end() + n);

    for(int i = dist; i < dist + n; ++i)
        *iter++ = v;

    v_size += n;

    return &values[dist];
}

template<typename T>
inline void Vector<T>::push_back(const T& v)
{
    emplace_back(v);
}

template<typename T>
inline void Vector<T>::push_back(T&& v)
{
    emplace_back(std::forward<T>(v));
}

template<typename T>
inline void Vector<T>::pop_back()
{
    --v_size;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::erase( const_iterator pos )
{
  

    const size_t dist = pos - begin();

    if(v_size != 0)
        --v_size;

    int inc;
    for(inc = 2; v_size > pow(2, inc); ++inc);

    if(v_size == 0)
        v_capacity = 0;
    else
        v_capacity = pow(2, inc);

    if(v_capacity != 0)
    {
        T* temp = new T[v_capacity];

        for(int i = 0, j = 0; j <= v_size; ++j)
        {
            if(j != dist)
                temp[ i++ ] = values[ j ];
        }

        delete [ ] values;
        values = temp;
    }

    return &values[ dist ];
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::erase(  iterator first, iterator last )
{
    const size_t n = last - first;

    std::move(last, end(), first);

    v_size -= n;
}

template<typename T>
inline void  Vector<T>::clear() noexcept
{
    v_size = 0;
}

template<typename T>
inline void Vector<T>::shrink_to_fit()
{
    v_capacity = v_size;
    reallocate();
}

template<typename T>
inline void Vector<T>::reserve(size_t n)
{
    if (n > v_capacity)
    {
        v_capacity = n;
        reallocate();
    }
}

template<typename T>
inline void Vector<T>::resize(size_t n)
{
    if(n > v_capacity)
    {
        ctor_initialized = true;

        v_capacity = n;
        reallocate();
    }

    v_size = n;
}

template<typename T>
inline void Vector<T>::resize(size_t n, const T& v)
{
    if(n > v_capacity)
    {
        ctor_initialized = true;

        v_capacity = n;
        reallocate();
    }

    if(n > v_size)
    {
        for(int i = v_size; i < n; ++i)
            values[ i ] = v;
    }

    v_size = n;
}

template<typename T>
inline int  Vector<T>::size() const noexcept
{
    return v_size;
}

template<typename T>
inline int  Vector<T>::capacity() const noexcept
{
    return v_capacity;
}

template<typename T>
inline constexpr bool  Vector<T>:: empty() const noexcept
{
    return begin() == end();
}

template<typename T>
inline void Vector<T>::reallocate()
{
    T* temp = new T[ v_capacity ];

    for(int i = 0; i < v_size; ++i)
        temp[ i ] = values[ i ];

    delete[ ] values;
    values = temp;
}

template<typename H>
inline bool operator==(const Vector<H>& lhs, const Vector<H>& rhs)
{
    if(lhs.v_size != rhs.v_size)
        return false;

    for(int i = 0; i < lhs.v_size; ++i)
        if(lhs.values[ i ] != rhs.values[ i ])
            return false;

    return true;
}
