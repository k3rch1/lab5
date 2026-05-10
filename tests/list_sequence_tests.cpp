#include <gtest/gtest.h>

#include "list_sequence.hpp"

TEST(list_sequence, dctor) {
    list_sequence<int> seq;

    EXPECT_EQ(seq.size(), 0);
}

TEST(list_sequence, size_ctor) {
    list_sequence<int> seq(3);

    EXPECT_EQ(seq.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], 0);
}

TEST(list_sequence, ptr_ctor) {
    int data[] = {1, 2, 3};
    list_sequence<int> seq(data, 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], data[i]);
}

TEST(list_sequence, ilist_ctor) {
    list_sequence<int> seq = {1, 2, 3};
    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(list_sequence, linked_list_ctor) {
    linked_list<int> arr = {1, 2, 3};
    list_sequence<int> seq(arr);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], arr[i]);
}

TEST(list_sequence, front) {
    list_sequence<int> seq = {1, 2, 3};

    EXPECT_EQ(seq.front(), 1);
}

TEST(list_sequence, back) {
    list_sequence<int> seq = {1, 2, 3};

    EXPECT_EQ(seq.back(), 3);
}

TEST(list_sequence, set) {
    list_sequence<int> seq = {1, 2, 3};
    seq.set(1, 100);

    EXPECT_EQ(seq[1], 100);
}

TEST(list_sequence, append) {
    list_sequence<int> seq = {1, 2};
    seq.append(3);

    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(list_sequence, prepend) {
    list_sequence<int> seq = {2, 3};
    seq.prepend(1);

    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(list_sequence, insert) {
    list_sequence<int> seq = {1, 3};
    seq.insert(1, 2);

    int expected[] = {1, 2, 3};

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(seq[i], expected[i]);
}

TEST(list_sequence, clear) {
    list_sequence<int> seq = {1, 2, 3};
    seq.clear();

    EXPECT_EQ(seq.size(), 0);
}