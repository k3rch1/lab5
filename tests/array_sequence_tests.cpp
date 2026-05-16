#include <gtest/gtest.h>

#include "array_sequence.hpp"

TEST(array_sequence, dctor) {
    array_sequence<int> seq;

    EXPECT_EQ(seq.size(), 0);
}

TEST(array_sequence, size_ctor) {
    array_sequence<int> seq(3);

    EXPECT_EQ(seq.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], 0);
}

TEST(array_sequence, ptr_ctor) {
    int data[] = {1, 2, 3};
    array_sequence<int> seq(data, 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], data[i]);
}

TEST(array_sequence, ilist_ctor) {
    array_sequence<int> seq = {1, 2, 3};
    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(array_sequence, dynamic_array_ctor) {
    dynamic_array<int> arr = {1, 2, 3};
    array_sequence<int> seq(arr);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], arr[i]);
}

TEST(array_sequence, front) {
    array_sequence<int> seq = {1, 2, 3};

    EXPECT_EQ(seq.front(), 1);
}

TEST(array_sequence, back) {
    array_sequence<int> seq = {1, 2, 3};

    EXPECT_EQ(seq.back(), 3);
}

TEST(array_sequence, set) {
    array_sequence<int> seq = {1, 2, 3};
    seq.set(1, 100);

    EXPECT_EQ(seq[1], 100);
}

TEST(array_sequence, append) {
    array_sequence<int> seq = {1, 2};
    seq.append(3);

    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(array_sequence, prepend) {
    array_sequence<int> seq = {2, 3};
    seq.prepend(1);

    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(array_sequence, insert) {
    array_sequence<int> seq = {1, 3};
    seq.insert(1, 2);

    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(array_sequence, clear) {
    array_sequence<int> seq = {1, 2, 3};
    seq.clear();

    EXPECT_EQ(seq.size(), 0);
}

TEST(array_sequence, slice) {
    array_sequence<int> array = {1, 2, 3, 4};
    auto sliced = array.slice(1, 3);
    int expected[] = {2, 3};

    EXPECT_EQ(sliced.size(), 2);

    for (size_t i = 0; i < 2; ++i)
        EXPECT_EQ(sliced[i], expected[i]);
}

TEST(array_sequence, slice_full) {
    array_sequence<int> array = {1, 2, 3};
    auto sliced = array.slice(0, 3);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(sliced.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(sliced[i], expected[i]);
}

TEST(array_sequence, slice_empty) {
    array_sequence<int> array = {1, 2, 3};
    auto sliced = array.slice(1, 1);

    EXPECT_EQ(sliced.size(), 0);
}

TEST(array_sequence, slice_out_of_range) {
    array_sequence<int> array = {1, 2, 3};

    EXPECT_THROW(array.slice(1, 4), std::out_of_range);
}

TEST(array_sequence, operator_slice) {
    array_sequence<int> array = {1, 2, 3, 4};
    auto sliced = array(1, 3);
    int expected[] = {2, 3};

    EXPECT_EQ(sliced.size(), 2);

    for (size_t i = 0; i < 2; ++i)
        EXPECT_EQ(sliced[i], expected[i]);
}