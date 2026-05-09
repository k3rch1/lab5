#include <gtest/gtest.h>

#include "dynamic_array.hpp"

TEST(dynamic_array, dctor) {
    dynamic_array<int> arr;

    EXPECT_EQ(arr.size(), 0);
}

TEST(dynamic_array, size_ctor) {
    dynamic_array<int> arr(5);

    EXPECT_EQ(arr.size(), 5);

    EXPECT_EQ(arr.get(0), 0);
    EXPECT_EQ(arr.get(1), 0);
    EXPECT_EQ(arr.get(2), 0);
}

TEST(dynamic_array, ptr_ctor) {
    int data[] = {1, 2, 3};

    dynamic_array<int> arr(data, 3);

    EXPECT_EQ(arr.size(), 3);

    EXPECT_EQ(arr.get(0), 1);
    EXPECT_EQ(arr.get(1), 2);
    EXPECT_EQ(arr.get(2), 3);

    data[0] = 100;

    EXPECT_EQ(arr.get(0), 1);
}

TEST(dynamic_array, ilist_ctor) {
    dynamic_array<int> arr = {1, 2, 3};

    EXPECT_EQ(arr.size(), 3);

    EXPECT_EQ(arr.get(0), 1);
    EXPECT_EQ(arr.get(1), 2);
    EXPECT_EQ(arr.get(2), 3);
}

TEST(dynamic_array, move_ctor) {
    dynamic_array<int> source = {1, 2, 3};

    dynamic_array<int> moved(std::move(source));

    EXPECT_EQ(moved.size(), 3);

    EXPECT_EQ(moved.get(0), 1);
    EXPECT_EQ(moved.get(1), 2);
    EXPECT_EQ(moved.get(2), 3);

    EXPECT_EQ(source.size(), 0);
}

TEST(dynamic_array, copy_ctor) {
    dynamic_array<int> source = {1, 2, 3};

    dynamic_array<int> copy(source);

    EXPECT_EQ(copy.size(), 3);

    EXPECT_EQ(copy.get(0), 1);
    EXPECT_EQ(copy.get(1), 2);
    EXPECT_EQ(copy.get(2), 3);

    copy[0] = 100;

    EXPECT_EQ(source[0], 1);
}