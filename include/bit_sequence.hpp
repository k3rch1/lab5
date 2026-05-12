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

    bit_sequence();
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
bit_sequence<T>::bit_sequence() : items(), size_(0) {}

template<std::integral T>
bit_sequence<T>::bit_sequence(size_t count) : items((count + sizeof(T) * 8 - 1) / (sizeof(T) * 8)), size_(count) {
    for (size_t i = 0; i < items.size(); ++i)
        items[i] = 0u;
}

template<std::integral T>
bit_sequence<T>::bit_sequence(const bool* items, size_t count) : items(), size_(0) {
    for (size_t i = 0; i < count; ++i)
        push_back(items[i]);
}

template<std::integral T>
bit_sequence<T>::bit_sequence(std::initializer_list<bool> init) : items(), size_(0) {
    for (bool bit : init)
        push_back(bit);
}

template<std::integral T>
size_t bit_sequence<T>::size() const noexcept {
    return size_;
}

template<std::integral T>
bool bit_sequence<T>::empty() const noexcept {
    return size() == 0;
}

template<std::integral T>
bit_sequence<T>::bit_proxy bit_sequence<T>::operator[](size_t index) {
    if (index >= size_)
        throw std::out_of_range("out of range");

    return bit_proxy(items[index / (sizeof(T) * 8)], index % (sizeof(T) * 8));
}

template<std::integral T>
bool bit_sequence<T>::operator[](size_t index) const {
    if (index >= size_)
        throw std::out_of_range("out of range");

    return (items[index / (sizeof(T) * 8)] >> (index % (sizeof(T) * 8))) & 1u;
}

template<std::integral T>
bool bit_sequence<T>::get(size_t index) const {
    return (*this)[index];
}

template<std::integral T>
void bit_sequence<T>::set(size_t index, bool value) {
    (*this)[index] = value;
}

template<std::integral T>
void bit_sequence<T>::push_back(bool value) {
    if (size_ % (sizeof(T) * 8) == 0)
        items.push_back(T(0));
    
    size_++;
    set(size_ - 1, value);
}

template<std::integral T>
void bit_sequence<T>::clear() {
    items.resize(0);
    size_ = 0;
}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator&(const bit_sequence& other) const {
    if (size_ != other.size_)
        throw std::invalid_argument("size mismatch");

    bit_sequence result(size_);
    for (size_t i = 0; i < items.size(); ++i)
        result.items[i] = items[i] & other.items[i];

    return result;
}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator|(const bit_sequence& other) const {
    if (size_ != other.size_)
        throw std::invalid_argument("size mismatch");

    bit_sequence result(size_);
    for (size_t i = 0; i < items.size(); ++i)
        result.items[i] = items[i] | other.items[i];

    return result;
}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator^(const bit_sequence& other) const {
    if (size_ != other.size_)
        throw std::invalid_argument("size mismatch");

    bit_sequence result(size_);
    for (size_t i = 0; i < items.size(); ++i)
        result.items[i] = items[i] ^ other.items[i];

    return result;
}

template<std::integral T>
bit_sequence<T> bit_sequence<T>::operator~() const {
    bit_sequence result(size_);
    for (size_t i = 0; i < items.size(); ++i)
        result.items[i] = ~items[i];

    return result;
}

template<std::integral T>
bit_sequence<T>::iterator bit_sequence<T>::begin() noexcept {
    return iterator(this, 0);
}

template<std::integral T>
bit_sequence<T>::iterator bit_sequence<T>::end() noexcept {
    return iterator(this, size_);
}

template<std::integral T>
bit_sequence<T>::const_iterator bit_sequence<T>::begin() const noexcept {
    return const_iterator(this, 0);
}

template<std::integral T>
bit_sequence<T>::const_iterator bit_sequence<T>::end() const noexcept {
    return const_iterator(this, size_);
}