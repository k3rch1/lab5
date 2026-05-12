#pragma once

#include <concepts>
#include "dynamic_array.hpp"

template<std::integral T>
class bit_sequence {
private:
    class bit_proxy {
    private:
        T& block;
        size_t offset;

    public:
        bit_proxy(T& block, size_t offset) : block(block), offset(offset) {}

        bit_proxy& operator=(bool value) {
            if (value)
                block |= static_cast<T>(1u << offset);
            else
                block &= ~static_cast<T>(1u << offset);

            return *this;
        }

        operator bool() const {
            return (block >> offset) & 1u;
        }
    };

    dynamic_array<T> items;
    size_t size_;
public:
    class iterator {
    private:
        bit_sequence* seq;
        size_t index;

    public:
        iterator(bit_sequence* seq, size_t index) : seq(seq), index(index) {}

        bit_proxy operator*() {
            return (*seq)[index];
        }

        iterator& operator++() {
            ++index;
            return *this;
        }

        bool operator==(const iterator& other) const {
            return seq == other.seq && index == other.index;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }
    };

    class const_iterator {
    private:
        const bit_sequence* seq;
        size_t index;

    public:
        const_iterator(const bit_sequence* seq, size_t index) : seq(seq), index(index) {}

        bool operator*() const {
            return (*seq)[index];
        }

        const_iterator& operator++() {
            ++index;
            return *this;
        }

        bool operator==(const const_iterator& other) const {
            return seq == other.seq && index == other.index;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };

    bit_sequence() = default;
    explicit bit_sequence(size_t count);
    bit_sequence(const bool* items, size_t count);
    bit_sequence(std::initializer_list<bool> init);

    bit_sequence(const bit_sequence&) = default;
    bit_sequence(bit_sequence&&) noexcept = default;

    ~bit_sequence() = default;

    bit_sequence& operator=(const bit_sequence&) = default;
    bit_sequence& operator=(bit_sequence&&) noexcept = default;

    size_t size() const noexcept;
    bool empty() const noexcept;

    bit_proxy operator[](size_t index);
    bool operator[](size_t index) const;

    bool get(size_t index) const;
    void set(size_t index, bool value);

    void push_back(bool value);

    void clear();

    bit_sequence operator&(const bit_sequence& other) const;
    bit_sequence operator|(const bit_sequence& other) const;
    bit_sequence operator^(const bit_sequence& other) const;
    bit_sequence operator~() const;

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
};

template<std::integral T>
bit_sequence<T>::bit_sequence(size_t count) : items(count) {}

template<std::integral T>
bit_sequence<T>::bit_sequence(const bool* items, size_t count) {}

template<std::integral T>
bit_sequence<T>::bit_sequence(std::initializer_list<bool> init) {}

template<std::integral T>
size_t bit_sequence<T>::size() const noexcept {}

template<std::integral T>
bool bit_sequence<T>::empty() const noexcept {}

template<std::integral T>
bit_sequence<T>::bit_proxy bit_sequence<T>::operator[](size_t index) {}

template<std::integral T>
bool bit_sequence<T>::operator[](size_t index) const {}

template<std::integral T>
bool bit_sequence<T>::get(size_t index) const {}

template<std::integral T>
void bit_sequence<T>::set(size_t index, bool value) {}

template<std::integral T>
void bit_sequence<T>::push_back(bool value) {}

template<std::integral T>
void bit_sequence<T>::clear() {}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator&(const bit_sequence& other) const {}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator|(const bit_sequence& other) const {}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator^(const bit_sequence& other) const {}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator~() const {}

template<std::integral T>
bit_sequence<T>::iterator bit_sequence<T>::begin() noexcept {}

template<std::integral T>
bit_sequence<T>::iterator bit_sequence<T>::end() noexcept {}

template<std::integral T>
bit_sequence<T>::const_iterator bit_sequence<T>::begin() const noexcept {}

template<std::integral T>
bit_sequence<T>::const_iterator bit_sequence<T>::end() const noexcept {}