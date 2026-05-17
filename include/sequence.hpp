#pragma once

template<class T>
class sequence {
public:
    virtual ~sequence() = default;

    virtual size_t size() const noexcept = 0;
    virtual bool empty() const noexcept = 0;

    virtual T& front() = 0;
    virtual const T& front() const = 0;

    virtual T& back() = 0;
    virtual const T& back() const = 0;

    virtual T& operator[](size_t index) = 0;
    virtual const T& operator[](size_t index) const = 0;

    virtual T& get(size_t index) = 0;
    virtual const T& get(size_t index) const = 0;

    virtual void set(size_t index, const T& value) = 0;
    virtual void set(size_t index, T&& value) = 0;

    virtual void append(const T& value) = 0;
    virtual void append(T&& value) = 0;

    virtual void prepend(const T& value) = 0;
    virtual void prepend(T&& value) = 0;

    virtual void insert(size_t index, const T& value) = 0;
    virtual void insert(size_t index, T&& value) = 0;

    virtual void remove(size_t index) = 0;

    virtual void clear() = 0;
};