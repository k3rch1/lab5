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

TEST(array_sequence, map) {
    array_sequence<int> seq = {1, 2, 3};
    auto mapped = seq.map([](int x) {
        return x * 2;
    });
    int expected[] = {2, 4, 6};

    EXPECT_EQ(mapped.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(mapped[i], expected[i]);
}

TEST(array_sequence, map_type_change) {
    array_sequence<int> seq = {1, 2, 3};
    auto mapped = seq.map([](int x) {
        return x + 0.5;
    });
    double expected[] = {1.5, 2.5, 3.5};

    EXPECT_EQ(mapped.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_DOUBLE_EQ(mapped[i], expected[i]);
}

TEST(array_sequence, map_empty) {
    array_sequence<int> seq;
    auto mapped = seq.map([](int x) {
        return x * 2;
    });

    EXPECT_TRUE(mapped.empty());
}

TEST(array_sequence, filter) {
    array_sequence<int> seq = {1, 2, 3, 4, 5};
    auto filtered = seq.filter([](int x) {
        return x % 2 == 0;
    });
    int expected[] = {2, 4};

    EXPECT_EQ(filtered.size(), 2);

    for (size_t i = 0; i < 2; ++i)
        EXPECT_EQ(filtered[i], expected[i]);
}

TEST(array_sequence, filter_empty) {
    array_sequence<int> seq = {1, 3, 5};
    auto filtered = seq.filter([](int x) {
        return x % 2 == 0;
    });

    EXPECT_TRUE(filtered.empty());
}

TEST(array_sequence, filter_all) {
    array_sequence<int> seq = {2, 4, 6};
    auto filtered = seq.filter([](int x) {
        return x % 2 == 0;
    });

    EXPECT_EQ(filtered.size(), 3);

    for (size_t i = 0; i < 3; ++i)
        EXPECT_EQ(filtered[i], seq[i]);
}

TEST(array_sequence, reduce_sum) {
    array_sequence<int> seq = {1, 2, 3, 4};
    auto result = seq.reduce([](int a, int b) {
        return a + b;
    }, 0);

    EXPECT_EQ(result, 10);
}

TEST(array_sequence, reduce_mul) {
    array_sequence<int> seq = {1, 2, 3, 4};
    auto result = seq.reduce([](int a, int b) {
        return a * b;
    }, 1);

    EXPECT_EQ(result, 24);
}

TEST(array_sequence, reduce_empty) {
    array_sequence<int> seq;
    auto result = seq.reduce([](int a, int b) {
        return a + b;
    }, 42);

    EXPECT_EQ(result, 42);
}

TEST(array_sequence, zip) {
    array_sequence<int> nums = {1, 2, 3};
    array_sequence<char> chars = {'a', 'b', 'c'};
    auto zipped = nums.zip(chars);
    std::pair<int, char> expected[] = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'}
    };

    EXPECT_EQ(zipped.size(), 3);
    
    for (auto i = 0; i < 3; ++i) {
        EXPECT_EQ(zipped[i].first, expected[i].first);
        EXPECT_EQ(zipped[i].second, expected[i].second);
        ++i;
    }
}

TEST(array_sequence, zip_size_mismatch) {
    array_sequence<int> a = {1, 2};
    array_sequence<char> b = {'a'};

    EXPECT_THROW(a.zip(b), std::invalid_argument);
}

TEST(array_sequence, unzip) {
    array_sequence<std::pair<int, char>> seq = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'}
    };
    auto [nums, chars] = unzip(seq);
    int expected_nums[] = {1, 2, 3};
    char expected_chars[] = {'a', 'b', 'c'};

    EXPECT_EQ(nums.size(), 3);
    EXPECT_EQ(chars.size(), 3);

    for (auto i = 0; i < 3; ++i) {
        EXPECT_EQ(nums[i], expected_nums[i]);
        EXPECT_EQ(chars[i], expected_chars[i]);
    }
}

TEST(array_sequence, remove) {
    array_sequence<int> seq = {1, 2, 3, 4};
    seq.remove(1);
    int expected[] = {1, 3, 4};

    EXPECT_EQ(seq.size(), 3);

    for (auto i = 0; i < 3; ++i)
        EXPECT_EQ(seq[i], expected[i]);
}