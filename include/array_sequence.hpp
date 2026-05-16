#pragma once

#include <initializer_list>
#include <utility>
#include "sequence.hpp"
#include "dynamic_array.hpp"

template<class T>
class array_sequence : public sequence<T> {
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

    ~array_sequence() override = default;

    array_sequence& operator=(const array_sequence&) = default;
    array_sequence& operator=(array_sequence&&) = default;
    
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

    array_sequence<T> slice(size_t start, size_t end) const;
    array_sequence<T> operator()(size_t start, size_t end) const;

    auto begin() const noexcept;
    auto begin() noexcept;

    auto end() const noexcept;
    auto end() noexcept;

    template<std::invocable<T> F>
    auto map(F func) const;

    template<std::predicate<T> P>
    array_sequence<T> filter(P pred) const;

    template<std::invocable<T, T> F>
    T reduce(F func, T init) const;

    template<class U>
    array_sequence<std::pair<T, U>> zip(const array_sequence<U>& other) const;
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
T& array_sequence<T>::operator[](size_t index) {
    return items[index];
}

template<class T>
const T& array_sequence<T>::operator[](size_t index) const {
    return items[index];
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
void array_sequence<T>::set(size_t index, const T& value) {
    items.set(index, value);
}

template<class T>
void array_sequence<T>::set(size_t index, T&& value) {
    items.set(index, std::move(value));
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
array_sequence<T> array_sequence<T>::slice(size_t start, size_t end) const {
    return array_sequence<T>(items.slice(start, end));
}

template<class T>
array_sequence<T> array_sequence<T>::operator()(size_t start, size_t end) const {
    return array_sequence<T>(items(start, end));
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

template<class T>
template<std::invocable<T> F>
auto array_sequence<T>::map(F func) const {
    using U = decltype(func(std::declval<T>()));
    array_sequence<U> result;

    for (auto el : *this)
        result.append(func(el));

    return result;
}

template<class T>
template<std::predicate<T> P>
array_sequence<T> array_sequence<T>::filter(P pred) const {
    array_sequence<T> result;

    for (auto el : *this)
        if (pred(el))
            result.append(el);

    return result;
}

template<class T>
template<std::invocable<T, T> F>
T array_sequence<T>::reduce(F func, T init) const {
    T result = init;

    for (auto el : *this)
        result = func(result, el);

    return result;
}

template<class T>
template<class U>
array_sequence<std::pair<T, U>> array_sequence<T>::zip(const array_sequence<U>& other) const {
    if (size() != other.size())
        throw std::invalid_argument("size mismatch");
    array_sequence<std::pair<T, U>> result;

    for (size_t i = 0; i < size(); ++i)
        result.append({(*this)[i], other[i]});

    return result;
}

template<class T, class U>
std::pair<array_sequence<T>, array_sequence<U>> unzip(const array_sequence<std::pair<T, U>>& seq) {
    array_sequence<T> first;
    array_sequence<U> second;

    for (auto el : seq) {
        first.append(el.first);
        second.append(el.second);
    }

    return {first, second};
}