#include <gtest/gtest.h>

#include "bit_sequence.hpp"

TEST(bit_sequence, dctor) {
    bit_sequence<uint8_t> bits;

    EXPECT_EQ(bits.size(), 0);
}

TEST(bit_sequence, size_ctor) {
    bit_sequence<uint8_t> bits(10);

    EXPECT_EQ(bits.size(), 10);

    for (auto i = 0; i < 10; ++i)
        EXPECT_FALSE(bits[i]);
}

TEST(bit_sequence, ptr_ctor) {
    bool data[] = {1, 0, 1, 1};
    bit_sequence<uint8_t> bits(data, 4);

    EXPECT_EQ(bits.size(), 4);

    for (auto i = 0; i < 4; ++i)
        EXPECT_EQ(bits[i], data[i]);
}

TEST(bit_sequence, ilist_ctor) {
    bit_sequence<uint8_t> bits = {1, 0, 1};
    bool expected[] = {1, 0, 1};

    EXPECT_EQ(bits.size(), 3);

    for (auto i = 0; i < 3; ++i)
        EXPECT_EQ(bits[i], expected[i]);
}

TEST(bit_sequence, copy_ctor) {
    bit_sequence<uint8_t> source = {1, 0, 1, 1};
    bit_sequence<uint8_t> copy(source);

    EXPECT_EQ(copy.size(), source.size());

    for (auto i = 0; i < source.size(); ++i)
        EXPECT_EQ(copy[i], source[i]);

    copy[0] = false;
    EXPECT_TRUE(source[0]);
}

TEST(bit_sequence, move_ctor) {
    bit_sequence<uint8_t> source = {1, 0, 1, 1};
    bit_sequence<uint8_t> moved(std::move(source));

    bool expected[] = {1, 0, 1, 1};

    EXPECT_EQ(moved.size(), 4);

    for (auto i = 0; i < 4; ++i)
        EXPECT_EQ(moved[i], expected[i]);

    EXPECT_EQ(source.size(), 0);
}

TEST(bit_sequence, copy_operator) {
    bit_sequence<uint8_t> source = {1, 0, 1, 1};
    bit_sequence<uint8_t> copy = source;

    EXPECT_EQ(copy.size(), source.size());

    for (auto i = 0; i < source.size(); ++i)
        EXPECT_EQ(copy[i], source[i]);

    copy[0] = false;
    EXPECT_TRUE(source[0]);
}

TEST(bit_sequence, set) {
    bit_sequence<uint8_t> bits(4);
    bits.set(0, true);
    bits.set(2, true);
    bool expected[] = {1, 0, 1, 0};

    for (auto i = 0; i < 4; ++i)
        EXPECT_EQ(bits[i], expected[i]);
}

TEST(bit_sequence, set_out_of_range) {
    bit_sequence<uint8_t> bits(4);

    EXPECT_THROW(bits.set(10, true), std::out_of_range);
}

TEST(bit_sequence, push_back) {
    bit_sequence<uint8_t> bits;
    bits.push_back(true);
    bits.push_back(false);
    bits.push_back(true);
    bool expected[] = {1, 0, 1};

    EXPECT_EQ(bits.size(), 3);

    for (auto i = 0; i < 3; ++i)
        EXPECT_EQ(bits[i], expected[i]);
}

TEST(bit_sequence, clear) {
    bit_sequence<uint8_t> bits = {1, 0, 1, 1};
    bits.clear();

    EXPECT_EQ(bits.size(), 0);
}

TEST(bit_sequence, and) {
    bit_sequence<uint8_t> a = {1, 0, 1, 1};
    bit_sequence<uint8_t> b = {1, 1, 0, 1};
    auto c = a & b;
    bool expected[] = {1, 0, 0, 1};

    EXPECT_EQ(c.size(), 4);

    for (auto i = 0; i < 4; ++i)
        EXPECT_EQ(c[i], expected[i]);
}

TEST(bit_sequence, and_size_mismatch) {
    bit_sequence<uint8_t> a = {1, 0};
    bit_sequence<uint8_t> b = {1, 0, 1};

    EXPECT_THROW(a & b, std::invalid_argument);
}

TEST(bit_sequence, or) {
    bit_sequence<uint8_t> a = {1, 0, 1, 0};
    bit_sequence<uint8_t> b = {0, 1, 0, 0};
    auto c = a | b;
    bool expected[] = {1, 1, 1, 0};

    EXPECT_EQ(c.size(), 4);

    for (auto i = 0; i < 4; ++i)
        EXPECT_EQ(c[i], expected[i]);
}

TEST(bit_sequence, or_size_mismatch) {
    bit_sequence<uint8_t> a = {1, 0};
    bit_sequence<uint8_t> b = {1, 0, 1};

    EXPECT_THROW(a | b, std::invalid_argument);
}

TEST(bit_sequence, xor) {
    bit_sequence<uint8_t> a = {1, 0, 1, 1};
    bit_sequence<uint8_t> b = {1, 1, 0, 1};
    auto c = a ^ b;
    bool expected[] = {0, 1, 1, 0};

    EXPECT_EQ(c.size(), 4);

    for (auto i = 0; i < 4; ++i)
        EXPECT_EQ(c[i], expected[i]);
}

TEST(bit_sequence, xor_mismatch) {
    bit_sequence<uint8_t> a = {1, 0};
    bit_sequence<uint8_t> b = {1, 0, 1};

    EXPECT_THROW(a ^ b, std::invalid_argument);
}

TEST(bit_sequence, not) {
    bit_sequence<uint8_t> a = {1, 0, 1};
    auto b = ~a;
    bool expected[] = {0, 1, 0};

    EXPECT_EQ(b.size(), 3);

    for (auto i = 0; i < 3; ++i)
        EXPECT_EQ(b[i], expected[i]);
}