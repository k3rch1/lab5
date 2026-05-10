#include <gtest/gtest.h>

#include "linked_list.hpp"

TEST(linked_list, dctor) {
    linked_list<int> list;

    EXPECT_EQ(list.size(), 0);
}

TEST(linked_list, size_ctor) {
    linked_list<int> list(5);

    EXPECT_EQ(list.size(), 5);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], 0);
}

TEST(linked_list, ptr_ctor) {
    int data[] = {1, 2, 3};

    linked_list<int> list(data, 3);

    EXPECT_EQ(list.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], data[i]);

    data[0] = 100;

    EXPECT_EQ(list.get(0), 1);
}

TEST(linked_list, ilist_ctor) {
    linked_list<int> list = {1, 2, 3};
    int expected[] = {1, 2, 3};

    EXPECT_EQ(list.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, move_ctor) {
    linked_list<int> source = {1, 2, 3};
    linked_list<int> moved(std::move(source));
    int expected[] = {1, 2, 3};

    EXPECT_EQ(moved.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(moved[i], expected[i]);

    EXPECT_EQ(source.size(), 0);
}

TEST(linked_list, copy_ctor) {
    linked_list<int> source = {1, 2, 3};

    linked_list<int> copy(source);

    EXPECT_EQ(copy.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(copy[i], source[i]);

    copy[0] = 100;

    EXPECT_EQ(source[0], 1);
}

TEST(linked_list, move_operator) {
    linked_list<int> source = {1, 2, 3};
    linked_list<int> moved;
    moved = std::move(source);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(moved.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(moved[i], expected[i]);

    EXPECT_EQ(source.size(), 0);
}

TEST(linked_list, copy_operator) {
    linked_list<int> source = {1, 2, 3};
    linked_list<int> copy;
    copy = source;

    EXPECT_EQ(copy.size(), source.size());

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(copy[i], source[i]);

    copy[0] = 100;

    EXPECT_EQ(source[0], 1);
}

TEST(linked_list, front) {
    linked_list<int> list = {1, 2, 3};
    EXPECT_EQ(list.front(), 1);
}

TEST(linked_list, front_empty) {
    linked_list<int> list;
    EXPECT_THROW(list.front(), std::out_of_range);
}

TEST(linked_list, back) {
    linked_list<int> list = {1, 2, 3};
    EXPECT_EQ(list.back(), 3);
}

TEST(linked_list, back_empty) {
    linked_list<int> list;
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(linked_list, get_out_of_range) {
    linked_list<int> list = {1, 2, 3};

    EXPECT_THROW(list.get(3), std::out_of_range);
}

TEST(linked_list, set) {
    linked_list<int> list = {1, 2, 3};
    list.set(1, 100);

    EXPECT_EQ(list[1], 100);
}

TEST(linked_list, set_out_of_range) {
    linked_list<int> list = {1, 2, 3};

    EXPECT_THROW(list.set(10, 100), std::out_of_range);
}

TEST(linked_list, push_front) {
    linked_list<int> list = {2, 3};
    list.push_front(1);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(list.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, push_back) {
    linked_list<int> list = {1, 2};
    list.push_back(3);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(list.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, insert) {
    linked_list<int> list = {1, 3};
    list.insert(1, 2);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(list.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, insert_end) {
    linked_list<int> list = {1, 2};
    list.insert(2, 3);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(list.size(), 3);

    for (auto i = 0; i < 3; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, insert_out_of_range) {
    linked_list<int> list = {1, 2};

    EXPECT_THROW(list.insert(3, 100), std::out_of_range);
}

TEST(linked_list, pop_front) {
    linked_list<int> list = {1, 2, 3};

    list.pop_front();

    int expected[] = {2, 3};

    EXPECT_EQ(list.size(), 2);

    for (auto i = 0; i < 2; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, pop_back) {
    linked_list<int> list = {1, 2, 3};

    list.pop_back();

    int expected[] = {1, 2};

    EXPECT_EQ(list.size(), 2);

    for (auto i = 0; i < 2; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, extract) {
    linked_list<int> list = {1, 2, 3};

    list.extract(1);

    int expected[] = {1, 3};

    EXPECT_EQ(list.size(), 2);

    for (auto i = 0; i < 2; i++)
        EXPECT_EQ(list[i], expected[i]);
}

TEST(linked_list, extract_out_of_range) {
    linked_list<int> list = {1, 2, 3};

    EXPECT_THROW(list.extract(3), std::out_of_range);
}

TEST(linked_list, clear) {
    linked_list<int> list = {1, 2, 3};

    list.clear();

    EXPECT_EQ(list.size(), 0);
}

TEST(linked_list, slice) {
    linked_list<int> list = {1, 2, 3, 4};

    auto sliced = list.slice(1, 3);

    int expected[] = {2, 3};

    EXPECT_EQ(sliced.size(), 2);

    for (auto i = 0; i < 2; i++)
        EXPECT_EQ(sliced[i], expected[i]);
}

TEST(linked_list, slice_invalid_range) {
    linked_list<int> list = {1, 2, 3};

    EXPECT_THROW(list.slice(2, 1), std::out_of_range);
}

TEST(linked_list, concat) {
    linked_list<int> a = {1, 2};
    linked_list<int> b = {3, 4};

    auto result = a.concat(b);

    int expected[] = {1, 2, 3, 4};

    EXPECT_EQ(result.size(), 4);

    for (auto i = 0; i < 4; i++)
        EXPECT_EQ(result[i], expected[i]);
}