#pragma once

#include <initializer_list>
#include <utility>
#include "linked_list.hpp"

template<class T>
class list_sequence {
private:
    linked_list<T> items;
public:
    list_sequence() = default;
    explicit list_sequence(size_t count);
    list_sequence(const T* items, size_t count);
    list_sequence(std::initializer_list<T> init);

    list_sequence(const linked_list<T>& data);
    list_sequence(linked_list<T>&& data);

    list_sequence(const list_sequence& other) = default;
    list_sequence(list_sequence&& other) = default;

    ~list_sequence() = default;

    list_sequence& operator=(const list_sequence&) = default;
    list_sequence& operator=(list_sequence&&) = default;
    
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
list_sequence<T>::list_sequence(size_t count) : items(count) {}

template<class T>
list_sequence<T>::list_sequence(const T* items, size_t count) : items(items, count) {}

template<class T>
list_sequence<T>::list_sequence(std::initializer_list<T> init) : items(init) {}

template<class T>
list_sequence<T>::list_sequence(const linked_list<T>& data) : items(data) {}

template<class T>
list_sequence<T>::list_sequence(linked_list<T>&& data) : items(std::move(data)) {}

template<class T>
size_t list_sequence<T>::size() const noexcept {
    return items.size();
}

template<class T>
bool list_sequence<T>::empty() const noexcept {
    return items.size() == 0;
}

template<class T>
T& list_sequence<T>::front() {
    return items.front();
}

template<class T>
const T& list_sequence<T>::front() const {
    return items.front();
}

template<class T>
T& list_sequence<T>::back() {
    return items.back();
}

template<class T>
const T& list_sequence<T>::back() const {
    return items.back();
}

template<class T>
T& list_sequence<T>::get(size_t index) {
    return items.get(index);
}

template<class T>
const T& list_sequence<T>::get(size_t index) const {
    return items.get(index);
}

template<class T>
void list_sequence<T>::append(const T& value) {
    items.push_back(value);
}

template<class T>
void list_sequence<T>::append(T&& value) {
    items.push_back(std::move(value));
}

template<class T>
void list_sequence<T>::prepend(const T& value) {
    items.push_front(value);
}

template<class T>
void list_sequence<T>::prepend(T&& value) {
    items.push_front(std::move(value));
}

template<class T>
void list_sequence<T>::insert(size_t index, const T& value) {
    items.insert(index, value);
}

template<class T>
void list_sequence<T>::insert(size_t index, T&& value) {
    items.insert(index, std::move(value));
}

template<class T>
void list_sequence<T>::clear() {
    items.clear();
}

template<class T>
auto list_sequence<T>::begin() noexcept {
    return items.begin();
}

template<class T>
auto list_sequence<T>::begin() const noexcept {
    return items.begin();
}

template<class T>
auto list_sequence<T>::end() noexcept {
    return items.end();
}

template<class T>
auto list_sequence<T>::end() const noexcept {
    return items.end();
}