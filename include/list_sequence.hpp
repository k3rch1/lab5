#pragma once

#include <initializer_list>
#include <utility>
#include "sequence.hpp"
#include "linked_list.hpp"

template<class T>
class list_sequence : public sequence<T> {
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

    ~list_sequence() override = default;

    list_sequence& operator=(const list_sequence&) = default;
    list_sequence& operator=(list_sequence&&) = default;
    
    size_t size() const noexcept override;
    bool empty() const noexcept override;

    T& front() override;
    const T& front() const override;

    T& back() override;
    const T& back() const override;

    T& operator[](size_t index) override;
    const T& operator[](size_t index) const override;

    T& get(size_t index) override;
    const T& get(size_t index) const override;

    void set(size_t index, const T& value) override;
    void set(size_t index, T&& value) override;

    void append(const T& value) override;
    void append(T&& value) override;

    void prepend(const T& value) override;
    void prepend(T&& value) override;

    void insert(size_t index, const T& value) override;
    void insert(size_t index, T&& value) override;

    void clear() override;

    list_sequence<T> slice(size_t start, size_t end) const;
    list_sequence<T> operator()(size_t start, size_t end) const;

    auto begin() const noexcept;
    auto begin() noexcept;

    auto end() const noexcept;
    auto end() noexcept;

    template<std::invocable<T> F>
    auto map(F func) const;

    template<std::predicate<T> P>
    list_sequence<T> filter(P pred) const;

    template<std::invocable<T, T> F>
    T reduce(F func, T init) const;
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
T& list_sequence<T>::operator[](size_t index) {
    return items[index];
}

template<class T>
const T& list_sequence<T>::operator[](size_t index) const {
    return items[index];
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
void list_sequence<T>::set(size_t index, const T& value) {
    items.set(index, value);
}

template<class T>
void list_sequence<T>::set(size_t index, T&& value) {
    items.set(index, std::move(value));
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
list_sequence<T> list_sequence<T>::slice(size_t start, size_t end) const {
    return list_sequence<T>(items.slice(start, end));
}

template<class T>
list_sequence<T> list_sequence<T>::operator()(size_t start, size_t end) const {
    return list_sequence<T>(items(start, end));
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

template<class T>
template<std::invocable<T> F>
auto list_sequence<T>::map(F func) const {
    using U = decltype(func(std::declval<T>()));
    list_sequence<U> result;

    for (auto el : *this)
        result.append(func(el));

    return result;
}

template<class T>
template<std::predicate<T> P>
list_sequence<T> list_sequence<T>::filter(P pred) const {
    list_sequence<T> result;

    for (auto el : *this)
        if (pred(el))
            result.append(el);

    return result;
}

template<class T>
template<std::invocable<T, T> F>
T list_sequence<T>::reduce(F func, T init) const {
    T result = init;

    for (auto el : *this)
        result = func(result, el);

    return result;
}