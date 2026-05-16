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

TEST(list_sequence, slice) {
    list_sequence<int> array = {1, 2, 3, 4};
    auto sliced = array.slice(1, 3);
    int expected[] = {2, 3};

    EXPECT_EQ(sliced.size(), 2);

    for (size_t i = 0; i < 2; ++i)
        EXPECT_EQ(sliced[i], expected[i]);
}

TEST(list_sequence, slice_full) {
    list_sequence<int> array = {1, 2, 3};
    auto sliced = array.slice(0, 3);
    int expected[] = {1, 2, 3};

    EXPECT_EQ(sliced.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(sliced[i], expected[i]);
}

TEST(list_sequence, slice_empty) {
    list_sequence<int> array = {1, 2, 3};
    auto sliced = array.slice(1, 1);

    EXPECT_EQ(sliced.size(), 0);
}

TEST(list_sequence, slice_out_of_range) {
    list_sequence<int> array = {1, 2, 3};

    EXPECT_THROW(array.slice(1, 4), std::out_of_range);
}

TEST(list_sequence, operator_slice) {
    list_sequence<int> array = {1, 2, 3, 4};
    auto sliced = array(1, 3);
    int expected[] = {2, 3};

    EXPECT_EQ(sliced.size(), 2);

    for (size_t i = 0; i < 2; ++i)
        EXPECT_EQ(sliced[i], expected[i]);
}

TEST(list_sequence, map) {
    list_sequence<int> seq = {1, 2, 3};
    auto mapped = seq.map([](int x) {
        return x * 2;
    });
    int expected[] = {2, 4, 6};

    EXPECT_EQ(mapped.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(mapped[i], expected[i]);
}

TEST(list_sequence, map_type_change) {
    list_sequence<int> seq = {1, 2, 3};
    auto mapped = seq.map([](int x) {
        return x + 0.5;
    });
    double expected[] = {1.5, 2.5, 3.5};

    EXPECT_EQ(mapped.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_DOUBLE_EQ(mapped[i], expected[i]);
}

TEST(list_sequence, map_empty) {
    list_sequence<int> seq;
    auto mapped = seq.map([](int x) {
        return x * 2;
    });

    EXPECT_TRUE(mapped.empty());
}

TEST(list_sequence, filter) {
    list_sequence<int> seq = {1, 2, 3, 4, 5};
    auto filtered = seq.filter([](int x) {
        return x % 2 == 0;
    });
    int expected[] = {2, 4};

    EXPECT_EQ(filtered.size(), 2);

    for (size_t i = 0; i < 2; ++i)
        EXPECT_EQ(filtered[i], expected[i]);
}

TEST(list_sequence, filter_empty) {
    list_sequence<int> seq = {1, 3, 5};
    auto filtered = seq.filter([](int x) {
        return x % 2 == 0;
    });

    EXPECT_TRUE(filtered.empty());
}

TEST(list_sequence, filter_all) {
    list_sequence<int> seq = {2, 4, 6};
    auto filtered = seq.filter([](int x) {
        return x % 2 == 0;
    });

    EXPECT_EQ(filtered.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(filtered[i], seq[i]);
}

TEST(list_sequence, reduce_sum) {
    list_sequence<int> seq = {1, 2, 3, 4};
    auto result = seq.reduce([](int a, int b) {
        return a + b;
    }, 0);

    EXPECT_EQ(result, 10);
}

TEST(list_sequence, reduce_mul) {
    list_sequence<int> seq = {1, 2, 3, 4};
    auto result = seq.reduce([](int a, int b) {
        return a * b;
    }, 1);

    EXPECT_EQ(result, 24);
}

TEST(list_sequence, reduce_empty) {
    list_sequence<int> seq;
    auto result = seq.reduce([](int a, int b) {
        return a + b;
    }, 42);

    EXPECT_EQ(result, 42);
}