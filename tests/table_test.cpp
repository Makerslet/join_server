#include <gtest/gtest.h>
#include "table.h"

TEST(TABLE, DEFAULT_TABLE_IS_EMPTY)
{
    table t;
    ASSERT_TRUE(t.empty());
}

TEST(TABLE, INSERT)
{
    table t;
    std::size_t id = 12;
    std::string value = "hello_world";

    t.insert(id, value);
    ASSERT_TRUE(t.line_exists(id));
    ASSERT_EQ(t.line_value(id), value);
}

TEST(TABLE, COPY)
{
    table t1;
    std::size_t id = 12;
    std::string value = "hello_world";
    t1.insert(id, value);
    table t2(t1);

    ASSERT_TRUE(t2.line_exists(id));
    ASSERT_EQ(t2.line_value(id), value);
}

TEST(TABLE, COMPARE)
{
    table t1;
    std::size_t id = 12;
    std::string value = "hello_world";
    t1.insert(id, value);
    table t2(t1);

    ASSERT_TRUE(t1 == t2);
}

TEST(TABLE, INTERSECTION)
{
    table t1;
    std::size_t t1id1 = 1;
    std::string t1value1 = "hw1";
    t1.insert(t1id1, t1value1);

    std::size_t t1id2 = 2;
    std::string t1value2 = "hw2";
    t1.insert(t1id2, t1value2);

    table t2;
    std::size_t t2id1 = 3;
    std::string t2value1 = "hw3";
    t2.insert(t2id1, t2value1);

    std::size_t t2id2 = 2;
    std::string t2value2 = "hw4";
    t2.insert(t2id2, t2value2);

    auto result = t1.intersection(t2);
    ASSERT_EQ(result.size(), 1);

    auto row = result.front();
    ASSERT_EQ(std::get<0>(row), t1id2);
    ASSERT_EQ(std::get<1>(row), t1value2);
    ASSERT_EQ(std::get<2>(row), t2value2);
}

TEST(TABLE, INTERSECTION_ORDER)
{
    table t1;
    t1.insert(3, "");
    t1.insert(4, "");
    t1.insert(1, "");
    t1.insert(10, "");

    table t2;
    t2.insert(17, "");
    t2.insert(8, "");
    t2.insert(3, "");
    t2.insert(10, "");
    t2.insert(1, "");

    auto result = t1.intersection(t2);
    ASSERT_EQ(result.size(), 3);
    auto comparator = [](const table::intersection_row& left,
            const table::intersection_row& right) {return  std::get<0>(left) < std::get<0>(right);};
    bool is_sorted = std::is_sorted(result.begin(), result.end(), comparator);
    ASSERT_TRUE(is_sorted);
}

TEST(TABLE, SYM_DIFF)
{
    table t1;
    std::size_t t1id2 = 2;
    std::string t1value2 = "hw2";
    t1.insert(t1id2, t1value2);

    table t2;
    std::size_t t2id1 = 3;
    std::string t2value1 = "hw3";
    t2.insert(t2id1, t2value1);

    std::size_t t2id2 = 2;
    std::string t2value2 = "hw4";
    t2.insert(t2id2, t2value2);

    auto result = t1.sym_diff(t2);
    ASSERT_EQ(result.size(), 1);

    auto row = result.front();
    ASSERT_EQ(std::get<0>(row), t2id1);
    ASSERT_EQ(std::get<1>(row), "");
    ASSERT_EQ(std::get<2>(row), t2value1);
}

TEST(TABLE, SYM_DIFF_ORDER)
{
    table t1;
    t1.insert(3, "");
    t1.insert(4, "");
    t1.insert(1, "");
    t1.insert(10, "");

    table t2;
    t2.insert(17, "");
    t2.insert(8, "");
    t2.insert(3, "");
    t2.insert(10, "");
    t2.insert(1, "");

    auto result = t1.sym_diff(t2);
    ASSERT_EQ(result.size(), 3);
    auto comparator = [](const table::intersection_row& left,
            const table::intersection_row& right) {return  std::get<0>(left) < std::get<0>(right);};
    bool is_sorted = std::is_sorted(result.begin(), result.end(), comparator);
    ASSERT_TRUE(is_sorted);
}
