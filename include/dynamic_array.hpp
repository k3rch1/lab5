#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<class T>
class dynamic_array {
private:
    T* items;
    size_t size_;

public:
    using iterator = T*;
    using const_iterator = const T*;

    dynamic_array();
    explicit dynamic_array(size_t count);
    dynamic_array(const T* items, size_t count);
    dynamic_array(std::initializer_list<T> init);

    dynamic_array(dynamic_array<T>&& other) noexcept;
    dynamic_array(const dynamic_array<T>& other);

    ~dynamic_array();

    dynamic_array<T>& operator=(dynamic_array<T>&& other) noexcept;
    dynamic_array<T>& operator=(const dynamic_array<T>& other);

    size_t size() const noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& get(size_t index);
    const T& get(size_t index) const;

    void set(size_t index, const T& value);
    void set(size_t index, T&& value);

    void push_front(const T& value);
    void push_front(T&& value);

    void push_back(const T& value);
    void push_back(T&& value);

    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);

    void remove(size_t index);

    void resize(size_t new_size);

    dynamic_array<T> slice(size_t start, size_t end) const;
    dynamic_array<T> operator()(size_t start, size_t end) const;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
};

template <typename T>
dynamic_array<T>::dynamic_array() : items(nullptr), size_(0) {}

template<class T>
dynamic_array<T>::dynamic_array(size_t count) : items(new T[count]()), size_(count) {}

template<class T>
dynamic_array<T>::dynamic_array(const T* items, size_t count) : items(new T[count]), size_(count) {
    std::copy(items, items + count, this->items);
}

template<class T>
dynamic_array<T>::dynamic_array(std::initializer_list<T> init) : items(new T[init.size()]), size_(init.size()) {
    std::copy(init.begin(), init.end(), items);
}

template<class T>
dynamic_array<T>::dynamic_array(dynamic_array<T>&& other) noexcept : items(other.items), size_(other.size_) {
    other.items = nullptr;
    other.size_ = 0;
}

template<class T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& other) : items(new T[other.size_]), size_(other.size_) {
    std::copy(other.items, other.items + size_, items);
}

template<class T>
dynamic_array<T>::~dynamic_array() {
    delete[] items;
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T>&& other) noexcept {
    if (this != &other) {
        delete[] items;

        items = other.items;
        size_ = other.size_;

        other.items = nullptr;
        other.size_ = 0;
    }

    return *this;
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array<T>& other) {
    if (this != &other) {
        delete[] items;

        size_ = other.size_;
        items = new T[size_]();

        std::copy(other.items, other.items + size_, items);
    }

    return *this;
}

template<class T>
size_t dynamic_array<T>::size() const noexcept {
    return size_;
}

template<class T>
T& dynamic_array<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("out of range");
    }
    return items[index];
}

template<class T>
const T& dynamic_array<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("out of range");
    }
    return items[index];
}

template<class T>
T& dynamic_array<T>::get(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("out of range");
    }
    return items[index];
}

template<class T>
const T& dynamic_array<T>::get(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("out of range");
    }
    return items[index];
}

template<class T>
void dynamic_array<T>::set(size_t index, const T& value) {
    if (index >= size_) throw std::out_of_range("out of range");
    items[index] = value;
}

template<class T>
void dynamic_array<T>::set(size_t index, T&& value) {
    if (index >= size_) throw std::out_of_range("out of range");
    items[index] = std::move(value);
}

template<class T>
void dynamic_array<T>::push_front(const T& value) {
    resize(size_ + 1);

    for (size_t i = size_ - 1; i > 0; --i) {
        items[i] = std::move(items[i - 1]);
    }

    items[0] = value;
}

template<class T>
void dynamic_array<T>::push_front(T&& value) {
    resize(size_ + 1);

    for (size_t i = size_ - 1; i > 0; --i) {
        items[i] = std::move(items[i - 1]);
    }

    items[0] = std::move(value);
}

template<class T>
void dynamic_array<T>::push_back(const T& value) {
    resize(size_ + 1);
    items[size_ - 1] = value;
}

template<class T>
void dynamic_array<T>::push_back(T&& value) {
    resize(size_ + 1);
    items[size_ - 1] = std::move(value);
}

template<class T>
void dynamic_array<T>::insert(size_t index, const T& value) {
    if (index > size_) {
        throw std::out_of_range("out of range");
    }

    resize(size_ + 1);

    for (size_t i = size_ - 1; i > index; --i) {
        items[i] = std::move(items[i - 1]);
    }

    items[index] = value;
}

template<class T>
void dynamic_array<T>::insert(size_t index, T&& value) {
    if (index > size_) {
        throw std::out_of_range("out of range");
    }

    resize(size_ + 1);

    for (size_t i = size_ - 1; i > index; --i) {
        items[i] = std::move(items[i - 1]);
    }

    items[index] = std::move(value);
}

template<class T>
void dynamic_array<T>::remove(size_t index) {
    if (index >= size_)
        throw std::out_of_range("out of range");

    for (auto i = index; i + 1 < size_; ++i)
        items[i] = std::move(items[i + 1]);

    resize(size_ - 1);
}

template<class T>
void dynamic_array<T>::resize(size_t new_size) {
    if (new_size == size_) return;

    T* new_items = new T[new_size]();
    std::move(items, items + std::min(size_, new_size), new_items);

    delete[] items;

    items = new_items;
    size_ = new_size;
}

template<class T>
dynamic_array<T> dynamic_array<T>::slice(size_t start, size_t end) const {
    if (start > end || end > size_)
        throw std::out_of_range("out of range");

    dynamic_array<T> result(end - start);
    for (size_t i = start; i < end; ++i)
        result[i - start] = (*this)[i];

    return result;
}

template<class T>
dynamic_array<T> dynamic_array<T>::operator()(size_t start, size_t end) const {
    return slice(start, end);
}

template<class T>
typename dynamic_array<T>::iterator dynamic_array<T>::begin() noexcept {
    return items;
}

template<class T>
typename dynamic_array<T>::const_iterator dynamic_array<T>::begin() const noexcept {
    return items;
}

template<class T>
typename dynamic_array<T>::iterator dynamic_array<T>::end() noexcept {
    return items + size_;
}

template<class T>
typename dynamic_array<T>::const_iterator dynamic_array<T>::end() const noexcept {
    return items + size_;
}