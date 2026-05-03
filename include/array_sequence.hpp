#pragma once

#include <initializer_list>
#include <utility>
#include "dynamic_array.hpp"

template<class T>
class array_sequence {
private:
    dynamic_array<T> items;
public:
    array_sequence() = default;
    explicit array_sequence(size_t count);
    array_sequence(const T* items, size_t count);
    array_sequence(std::initializer_list<T> init);

    array_sequence(const dynamic_array<T>& data);
    array_sequence(dynamic_array<T>&& data);

    array_sequence(const array_sequence& other) = default;
    array_sequence(array_sequence&& other) = default;

    ~array_sequence() = default;

    array_sequence& operator=(const array_sequence&) = default;
    array_sequence& operator=(array_sequence&&) = default;
    
    size_t size() const noexcept;
    bool empty() const noexcept;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T& get(size_t index);
    const T& get(size_t index) const;

    void append(const T& value);
    void append(T&& value);

    void prepend(const T& value);
    void prepend(T&& value);

    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);

    void clear();

    auto begin() const noexcept;
    auto begin() noexcept;

    auto end() const noexcept;
    auto end() noexcept;
};

template<class T>
array_sequence<T>::array_sequence(size_t count) : items(count) {}

template<class T>
array_sequence<T>::array_sequence(const T* items, size_t count) : items(items, count) {}

template<class T>
array_sequence<T>::array_sequence(std::initializer_list<T> init) : items(init) {}

template<class T>
array_sequence<T>::array_sequence(const dynamic_array<T>& data) : items(data) {}

template<class T>
array_sequence<T>::array_sequence(dynamic_array<T>&& data) : items(std::move(data)) {}

template<class T>
size_t array_sequence<T>::size() const noexcept {
    return items.size();
}

template<class T>
bool array_sequence<T>::empty() const noexcept {
    return items.size() == 0;
}

template<class T>
T& array_sequence<T>::front() {
    return items.get(0);
}

template<class T>
const T& array_sequence<T>::front() const {
    return items.get(0);
}

template<class T>
T& array_sequence<T>::back() {
    return items.get(items.size() - 1);
}

template<class T>
const T& array_sequence<T>::back() const {
    return items.get(items.size() - 1);
}

template<class T>
T& array_sequence<T>::get(size_t index) {
    return items.get(index);
}

template<class T>
const T& array_sequence<T>::get(size_t index) const {
    return items.get(index);
}

template<class T>
void array_sequence<T>::append(const T& value) {
    items.push_back(value);
}

template<class T>
void array_sequence<T>::append(T&& value) {
    items.push_back(std::move(value));
}

template<class T>
void array_sequence<T>::prepend(const T& value) {
    items.push_front(value);
}

template<class T>
void array_sequence<T>::prepend(T&& value) {
    items.push_front(std::move(value));
}

template<class T>
void array_sequence<T>::insert(size_t index, const T& value) {
    items.insert(index, value);
}

template<class T>
void array_sequence<T>::insert(size_t index, T&& value) {
    items.insert(index, std::move(value));
}

template<class T>
void array_sequence<T>::clear() {
    items.resize(0);
}

template<class T>
auto array_sequence<T>::begin() noexcept {
    return items.begin();
}

template<class T>
auto array_sequence<T>::begin() const noexcept {
    return items.begin();
}

template<class T>
auto array_sequence<T>::end() noexcept {
    return items.end();
}

template<class T>
auto array_sequence<T>::end() const noexcept {
    return items.end();
}