#pragma once

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<class T>
class linked_list {
private:
    struct node {
        T value;
        node* prev;
        node* next;

        node(const T& value) : value(value), prev(nullptr), next(nullptr) {}
        node(T&& value) : value(std::move(value)), prev(nullptr), next(nullptr) {}
    };

    node* head;
    node* tail;

public:
    class iterator {
    private:
        node* current;

    public:
        iterator(node* current) : current(current) {}

        T& operator*() {
            return current->value;
        }

        iterator& operator++() {
            current = current->next;
            return *this;
        }

        iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    class const_iterator {
    private:
        const node* current;

    public:
        const_iterator(const node* current) : current(current) {}

        const T& operator*() const {
            return current->value;
        }

        const_iterator& operator++() {
            current = current->next;
            return *this;
        }

        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator==(const const_iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const const_iterator& other) const {
            return current != other.current;
        }
    };

    linked_list();
    explicit linked_list(size_t count);
    linked_list(const T* items, size_t count);
    linked_list(std::initializer_list<T> init);

    linked_list(const linked_list<T>& other);
    linked_list(linked_list<T>&& other) noexcept;

    ~linked_list();

    linked_list<T>& operator=(const linked_list<T>& other);
    linked_list<T>& operator=(linked_list<T>&& other) noexcept;

    size_t size() const noexcept;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T& get(size_t index);
    const T& get(size_t index) const;

    void push_front(const T& value);
    void push_front(T&& value);

    void push_back(const T& value);
    void push_back(T&& value);

    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value);

    void pop_front();
    void pop_back();
    
    void extract(size_t index);

    void clear();

    linked_list<T> slice(size_t start, size_t end) const;
    linked_list<T> operator()(size_t start, size_t end) const;

    linked_list<T> concat(const linked_list<T>& other) const;
    linked_list<T> concat(linked_list<T>&& other) const;

    linked_list<T> operator+(const linked_list<T>& other) const;
    linked_list<T> operator+(linked_list<T>&& other) const;

    linked_list<T>& operator+=(const linked_list<T>& other);
    linked_list<T>& operator+=(linked_list<T>&& other);

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
};

template<class T>
linked_list<T>::linked_list() : head(nullptr), tail(nullptr) {}

template<class T>
linked_list<T>::linked_list(size_t count) : head(nullptr), tail(nullptr) {
    for (size_t i = 0; i < count; ++i) {
        push_back(T());
    }
}

template<class T>
linked_list<T>::linked_list(const T* items, size_t count) : head(nullptr), tail(nullptr) {
    for (size_t i = 0; i < count; ++i) {
        push_back(items[i]);
    }
}

template<class T>
linked_list<T>::linked_list(std::initializer_list<T> init) : head(nullptr), tail(nullptr) {
    for (const auto& el : init) {
        push_back(el);
    }
}

template<class T>
linked_list<T>::linked_list(const linked_list<T>& other) : head(nullptr), tail(nullptr) {
    for (const auto& el : other) {
        push_back(el);
    }
}


template<class T>
linked_list<T>::linked_list(linked_list<T>&& other) noexcept : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

template<class T>
linked_list<T>::~linked_list() {
    clear();
}

template<class T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& other) {
    if (this != &other) {
        clear();

        for (const auto& el : other) {
            push_back(el);
        }
    }

    return *this;
}

template<class T>
linked_list<T>& linked_list<T>::operator=(linked_list<T>&& other) noexcept {
    if (this != &other) {
        clear();

        head = other.head;
        tail = other.tail;

        other.head = nullptr;
        other.tail = nullptr;
    }

    return *this;
}

template<class T>
size_t linked_list<T>::size() const noexcept {
    size_t count = 0;

    for (auto el : *this) {
        ++count;
    }

    return count;
}

template<class T>
T& linked_list<T>::front() {
    if (!head) throw std::out_of_range("empty list");
    
    return head->value;
}

template<class T>
const T& linked_list<T>::front() const {
    if (!head) throw std::out_of_range("empty list");
    
    return head->value;
}

template<class T>
T& linked_list<T>::back() {
    if (!tail) throw std::out_of_range("empty list");
    
    return tail->value;
}

template<class T>
const T& linked_list<T>::back() const {
    if (!tail) throw std::out_of_range("empty list");

    return tail->value;
}

template<class T>
T& linked_list<T>::get(size_t index) {
    node* cur = head;

    for (size_t i = 0; i < index; ++i) {
        if (!cur) throw std::out_of_range("out of range");
        cur = cur->next;
    }

    if (!cur) throw std::out_of_range("out of range");

    return cur->value;
}

template<class T>
const T& linked_list<T>::get(size_t index) const {
    node* cur = head;

    for (size_t i = 0; i < index; ++i) {
        if (!cur) throw std::out_of_range("out of range");
        cur = cur->next;
    }

    if (!cur) throw std::out_of_range("out of range");

    return cur->value;
}

template<class T>
void linked_list<T>::push_front(const T& value) {
    node* n = new node(value);

    if (!head) head = tail = n;
    else {
        n->next = head;
        head->prev = n;
        head = n;
    }
}

template<class T>
void linked_list<T>::push_front(T&& value) {
    node* n = new node(std::move(value));

    if (!head) head = tail = n; 
    else {
        n->next = head;
        head->prev = n;
        head = n;
    }
}

template<class T>
void linked_list<T>::push_back(const T& value) {
    node* n = new node(value);

    if (!tail) head = tail = n;
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

template<class T>
void linked_list<T>::push_back(T&& value) {
    node* n = new node(std::move(value));

    if (!tail) head = tail = n; 
    else {
        tail->next = n;
        n->prev = tail;
        tail = n;
    }
}

template<class T>
void linked_list<T>::insert(size_t index, const T& value) {
    if (index == 0) {
        push_front(value);
        return;
    }

    node* cur = head;

    for (size_t i = 0; i < index; ++i) {
        if (!cur) throw std::out_of_range("out of range");
        cur = cur->next;
    }

    if (!cur) {
        push_back(value);
        return;
    }

    node* n = new node(value);

    n->next = cur;
    n->prev = cur->prev;

    cur->prev->next = n;
    cur->prev = n;
}

template<class T>
void linked_list<T>::insert(size_t index, T&& value) {
    if (index == 0) {
        push_front(std::move(value));
        return;
    }

    node* cur = head;

    for (size_t i = 0; i < index; ++i) {
        if (!cur) throw std::out_of_range("out of range");
        cur = cur->next;
    }

    if (!cur) {
        push_back(std::move(value));
        return;
    }

    node* n = new node(std::move(value));

    n->next = cur;
    n->prev = cur->prev;

    cur->prev->next = n;
    cur->prev = n;
}

template<class T>
void linked_list<T>::pop_front() {
    if (!head) return;

    node* tmp = head;
    head = head->next;

    if (head) head->prev = nullptr;
    else tail = nullptr;

    delete tmp;
}

template<class T>
void linked_list<T>::pop_back() {
    if (!tail) return;

    node* tmp = tail;
    tail = tail->prev;

    if (tail) tail->next = nullptr;
    else head = nullptr;

    delete tmp;
}

template<class T>
void linked_list<T>::extract(size_t index) {
    node* cur = head;

    for (size_t i = 0; i < index; ++i) {
        if (!cur) throw std::out_of_range("out of range");
        cur = cur->next;
    }

    if (!cur) throw std::out_of_range("out of range");

    if (cur->prev) cur->prev->next = cur->next;
    else head = cur->next;

    if (cur->next) cur->next->prev = cur->prev;
    else tail = cur->prev;

    delete cur;
}

template<class T>
void linked_list<T>::clear() {
    for (; head; ) pop_front();
}

template<class T>
linked_list<T> linked_list<T>::slice(size_t start, size_t end) const {
    if (start > end) {
        throw std::out_of_range("invalid range");
    }

    linked_list<T> result;
    const node* cur = head;

    for (size_t i = 0; i < start; ++i) {
        if (!cur) throw std::out_of_range("out of range");
        cur = cur->next;
    }
    for (size_t i = start; i < end; ++i) {
        if (!cur) std::out_of_range("out of range");
        result.push_back(cur->value);
        cur = cur->next;
    }

    return result;
}

template<class T>
linked_list<T> linked_list<T>::operator()(size_t start, size_t end) const {
    linked_list<T> result;
    const node* cur = head;

    for (size_t i = 0; i < start; ++i) {
        cur = cur->next;
    }
    for (size_t i = start; i < end; ++i) {
        result.push_back(cur->value);
        cur = cur->next;
    }

    return result;
}

template<class T>
linked_list<T> linked_list<T>::concat(const linked_list<T>& other) const {
    linked_list<T> result;

    for (auto el : *this) {
        result.push_back(el);
    }
    for (auto el : other) {
        result.push_back(el);
    }

    return result;
}

template<class T>
linked_list<T> linked_list<T>::concat(linked_list<T>&& other) const {
    linked_list<T> result = *this;
    result.concat(std::move(other));
    return result;
}

template<class T>
linked_list<T> linked_list<T>::operator+(const linked_list<T>& other) const {
    linked_list<T> result = *this;
    result += other;
    return result;
}

template<class T>
linked_list<T> linked_list<T>::operator+(linked_list<T>&& other) const {
    linked_list<T> result = *this;
    result += std::move(other);
    return result;
}

template<class T>
linked_list<T>& linked_list<T>::operator+=(const linked_list<T>& other) {
    for (auto el : other) {
        push_back(el);
    }
    return *this;
}

template<class T>
linked_list<T>& linked_list<T>::operator+=(linked_list<T>&& other) {
    if (!other.head) return *this;

    if (!head) {
        head = other.head;
        tail = other.tail;
    } else {
        tail->next = other.head;
        other.head->prev = tail;
        tail = other.tail;
    }

    other.head = nullptr;
    other.tail = nullptr;

    return *this;
}

template<class T>
typename linked_list<T>::iterator linked_list<T>::begin() noexcept {
    return iterator(head);
}

template<class T>
typename linked_list<T>::iterator linked_list<T>::end() noexcept {
    return iterator(nullptr);
}

template<class T>
typename linked_list<T>::const_iterator linked_list<T>::begin() const noexcept {
    return const_iterator(head);
}

template<class T>
typename linked_list<T>::const_iterator linked_list<T>::end() const noexcept {
    return const_iterator(nullptr);
}