#include <gtest/gtest.h>

#include "dynamic_array.hpp"

TEST(dynamic_array, dctor) {
    dynamic_array<int> arr;

    EXPECT_EQ(arr.size(), 0);
}

TEST(dynamic_array, size_ctor) {
    dynamic_array<int> arr(5);

    EXPECT_EQ(arr.size(), 5);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], 0);
}

TEST(dynamic_array, ptr_ctor) {
    int data[] = {1, 2, 3};

    dynamic_array<int> arr(data, 3);

    EXPECT_EQ(arr.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], data[i]);

    data[0] = 100;

    EXPECT_EQ(arr.get(0), 1);
}

TEST(dynamic_array, ilist_ctor) {
    dynamic_array<int> arr = {1, 2, 3};
    int expected[] = {1, 2, 3};

    EXPECT_EQ(arr.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(dynamic_array, move_ctor) {
    dynamic_array<int> source = {1, 2, 3};

    dynamic_array<int> moved(std::move(source));

    EXPECT_EQ(moved.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(source[i], moved[i]);

    EXPECT_EQ(source.size(), 0);
}

TEST(dynamic_array, copy_ctor) {
    dynamic_array<int> source = {1, 2, 3};

    dynamic_array<int> copy(source);

    EXPECT_EQ(copy.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(copy[i], source[i]);

    copy[0] = 100;

    EXPECT_EQ(source[0], 1);
}

TEST(dynamic_array, move_operator) {
    dynamic_array<int> source = {1, 2, 3};
    dynamic_array<int> moved = std::move(source);

    int expected[] = {1, 2, 3};

    EXPECT_EQ(moved.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(moved[i], source[i]);

    EXPECT_EQ(source.size(), 0);
}

TEST(dynamic_array, copy_operator) {
    dynamic_array<int> source = {1, 2, 3};
    dynamic_array<int> copy = source;

    EXPECT_EQ(copy.size(), source.size());

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(copy[i], source[i]);

    copy[0] = 100;

    EXPECT_EQ(source[0], 1);
}

TEST(dynamic_array, get_out_of_range) {
    dynamic_array<int> arr = {1, 2, 3};

    EXPECT_THROW(arr.get(3), std::out_of_range);
}

TEST(dynamic_array, set) {
    dynamic_array<int> arr = {1, 2, 3};
    arr.set(1, 100);

    EXPECT_EQ(arr[1], 100);
}

TEST(dynamic_array, set_out_of_range) {
    dynamic_array<int> arr = {1, 2, 3};

    EXPECT_THROW(arr.set(10, 100), std::out_of_range);
}

TEST(dynamic_array, push_front) {
    dynamic_array<int> arr = {2, 3};
    arr.push_front(1);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(arr.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(dynamic_array, push_back) {
    dynamic_array<int> arr = {1, 2};
    arr.push_back(3);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(arr.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(dynamic_array, insert) {
    dynamic_array<int> arr = {1, 3};
    arr.insert(1, 2);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(arr.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(dynamic_array, insert_end) {
    dynamic_array<int> arr = {1, 2};
    arr.insert(2, 3);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(arr.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(dynamic_array, insert_out_of_range) {
    dynamic_array<int> arr = {1, 2};

    EXPECT_THROW(arr.insert(3, 100), std::out_of_range);
}

TEST(dynamic_array, resize_extend) {
    dynamic_array<int> arr = {1, 2};
    arr.resize(4);

    EXPECT_EQ(arr.size(), 4);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(dynamic_array, resize_shrink) {
    dynamic_array<int> arr = {1, 2, 3};
    arr.resize(2);

    EXPECT_EQ(arr.size(), 2);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
}

TEST(dynamic_array, resize_zero) {
    dynamic_array<int> arr = {1, 2, 3};
    arr.resize(0);

    EXPECT_EQ(arr.size(), 0);
}