#include <gtest/gtest.h>
#include "core_mock.h"
#include "check_syntax_command.h"
#include "insert_command.h"
#include "truncate_command.h"
#include "intersection_command.h"
#include "symmetric_difference_command.h"
#include "command_handling_exception.h"
#include "tables_manager.h"

TEST(CHECK_SYNTAX_COMMAND, EMPTY_REQUEST)
{
    std::string request;
    command_context empty_cntxt;
    std::string expected_error("empty request");

    try {
        check_syntax_command cmd(request);
        cmd.execute(empty_cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYNTAX_COMMAND, UNKNOWN_REQUEST)
{
    std::string request("create_one_trillion_dollars");
    command_context empty_cntxt;
    std::string expected_error = "unknown command type " + request;

    try {
        check_syntax_command cmd(request);
        cmd.execute(empty_cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYNTAX_COMMAND, WRONG_INSERT_REQUEST)
{
    std::string request("INSERT a 12");
    command_context empty_cntxt;
    std::string expected_error("INSERT command needs 3 arguments, but contains 2");

    try {
        check_syntax_command cmd(request);
        cmd.execute(empty_cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYNTAX_COMMAND, RIGHT_INSERT_REQUEST)
{
    std::string request("INSERT a 12 hello");
    auto core = std::make_shared<core_mock>();
    command_context cntxt {nullptr, core};

    check_syntax_command cmd(request);
    cmd.execute(cntxt);

    ASSERT_EQ(core->_exec_units.size(), 1);
    ASSERT_NE(dynamic_cast<insert_command*>(core->_exec_units.front()->command.get()), nullptr);
}

TEST(CHECK_SYNTAX_COMMAND, WRONG_TRUNCATE_REQUEST)
{
    std::string request("TRUNCATE");
    command_context empty_cntxt;
    std::string expected_error("TRUNCATE command needs 1 argument, but contains 0");

    try {
        check_syntax_command cmd(request);
        cmd.execute(empty_cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYNTAX_COMMAND, RIGHT_TRUNCATE_REQUEST)
{
    std::string request("TRUNCATE A");
    auto core = std::make_shared<core_mock>();
    command_context cntxt {nullptr, core};

    check_syntax_command cmd(request);
    cmd.execute(cntxt);

    ASSERT_EQ(core->_exec_units.size(), 1);
    ASSERT_NE(dynamic_cast<truncate_command*>(core->_exec_units.front()->command.get()), nullptr);
}

TEST(CHECK_SYNTAX_COMMAND, WRONG_INTERSECTION_REQUEST)
{
    std::string request("INTERSECTION A");
    command_context empty_cntxt;
    std::string expected_error("INTERSECTION command needs 2 arguments, but contains 1");

    try {
        check_syntax_command cmd(request);
        cmd.execute(empty_cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYNTAX_COMMAND, RIGHT_INTERSECTION_REQUEST)
{
    std::string request("INTERSECTION A B");
    auto core = std::make_shared<core_mock>();
    command_context cntxt {nullptr, core};

    check_syntax_command cmd(request);
    cmd.execute(cntxt);

    ASSERT_EQ(core->_exec_units.size(), 1);
    ASSERT_NE(dynamic_cast<intersection_command*>(core->_exec_units.front()->command.get()), nullptr);
}

TEST(CHECK_SYNTAX_COMMAND, WRONG_SYM_DIFF_REQUEST)
{
    std::string request("SYMMETRIC_DIFFERENCE A");
    command_context empty_cntxt;
    std::string expected_error("SYMMETRIC_DIFFERENCE command needs 2 arguments, but contains 1");

    try {
        check_syntax_command cmd(request);
        cmd.execute(empty_cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYNTAX_COMMAND, RIGHT_SYM_DIFF_REQUEST)
{
    std::string request("SYMMETRIC_DIFFERENCE A B");
    auto core = std::make_shared<core_mock>();
    command_context cntxt {nullptr, core};


    check_syntax_command cmd(request);
    cmd.execute(cntxt);

    ASSERT_EQ(core->_exec_units.size(), 1);
    ASSERT_NE(dynamic_cast<symmetric_difference_command*>(core->_exec_units.front()->command.get()), nullptr);
}

TEST(CHECK_INSERT_COMMAND, WRONG_ID_TYPE)
{
    auto t_manager = std::make_shared<tables_manager>();
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("INSERT command: wrong id type");

    try {
        insert_command cmd("A", {"abc", "def"});
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_INSERT_COMMAND, ID_OUT_OF_RANGE)
{
    auto t_manager = std::make_shared<tables_manager>();
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("INSERT command: id out of range");

    try {
        insert_command cmd("A", {"-2", "def"});
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_INSERT_COMMAND, ROW_ALREADY_EXISTS)
{
    auto t_manager = std::make_shared<tables_manager>();
    auto table = t_manager->add_table("A");
    table->insert(12, "i'm already here");

    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("INSERT command: line with id 12 already exists");

    try {
        insert_command cmd("A", {"12", "def"});
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_INSERT_COMMAND, OK)
{
    auto t_manager = std::make_shared<tables_manager>();
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};

    std::string table_name("A");
    insert_command cmd(table_name, {"12", "def"});
    auto result = cmd.execute(cntxt);

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), std::string());

    ASSERT_TRUE(t_manager->contain_table(table_name));

    auto table = t_manager->get_table(table_name);
    ASSERT_TRUE(table->line_exists(12));

    std::string line_value = table->line_value(12);
    std::string expected_line_value("def");
    ASSERT_TRUE(line_value == expected_line_value);
}

TEST(CHECK_TRUNCATE_COMMAND, TABLE_DOESNT_EXIST)
{
    auto t_manager = std::make_shared<tables_manager>();
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("TRUNCATE command: server doesnt't contain table A");

    try {
        truncate_command cmd("A");
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_TRUNCATE_COMMAND, OK)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string table_name("A");
    auto table = t_manager->add_table(table_name);

    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};

    truncate_command cmd(table_name);
    auto result = cmd.execute(cntxt);

    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value(), std::string());
    ASSERT_FALSE(t_manager->contain_table(table_name));
}

TEST(CHECK_INTERSECTION_COMMAND, LEFT_TABLE_DOESNT_EXIST)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string left_table_name("L");
    std::string right_table_name("R");
    auto table = t_manager->add_table(right_table_name);
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("INTERSECTION command: server doesnt't contain table L");

    try {
        intersection_command cmd(left_table_name, right_table_name);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_INTERSECTION_COMMAND, RIGHT_TABLE_DOESNT_EXIST)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string left_table_name("L");
    std::string right_table_name("R");
    auto table = t_manager->add_table(left_table_name);
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("INTERSECTION command: server doesnt't contain table R");

    try {
        intersection_command cmd(left_table_name, right_table_name);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_INTERSECTION_COMMAND, OK)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string left_table_name("L");
    auto table = t_manager->add_table(left_table_name);
    std::size_t id = 0;
    std::string left_value("left");
    table->insert(id, left_value);

    std::string right_table_name("R");
    table = t_manager->add_table(right_table_name);
    std::string right_value("right");
    table->insert(id, right_value);

    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};

    intersection_command cmd(left_table_name, right_table_name);
    auto result = cmd.execute(cntxt);
    ASSERT_TRUE(result.has_value());

    std::string expected_result = std::to_string(id) + " " + left_value + " " + right_value + "\n";
    ASSERT_EQ(result.value(), expected_result);
}

TEST(CHECK_SYMMETRIC_DIFFERENCE_COMMAND, LEFT_TABLE_DOESNT_EXIST)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string left_table_name("L");
    std::string right_table_name("R");
    auto table = t_manager->add_table(right_table_name);
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("SYMMETRIC DIFFERENCE command: server doesnt't contain table L");

    try {
        symmetric_difference_command cmd(left_table_name, right_table_name);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYMMETRIC_DIFFERENCE_COMMAND, RIGHT_TABLE_DOESNT_EXIST)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string left_table_name("L");
    std::string right_table_name("R");
    auto table = t_manager->add_table(left_table_name);
    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};
    std::string expected_error("SYMMETRIC DIFFERENCE command: server doesnt't contain table R");

    try {
        symmetric_difference_command cmd(left_table_name, right_table_name);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        std::string error(ex.what());
        ASSERT_EQ(error, expected_error);
        return;
    }
    ASSERT_FALSE(true);
}

TEST(CHECK_SYMMETRIC_DIFFERENCE_COMMAND, OK)
{
    auto t_manager = std::make_shared<tables_manager>();
    std::string left_table_name("L");
    auto table = t_manager->add_table(left_table_name);
    std::size_t left_id = 0;
    std::string left_value("left");
    table->insert(left_id, left_value);

    std::string right_table_name("R");
    table = t_manager->add_table(right_table_name);;
    table->insert(left_id, left_value);
    std::size_t right_id = 1;
    std::string right_value("right");
    table->insert(right_id, right_value);

    auto core = std::make_shared<core_mock>(t_manager);
    command_context cntxt {nullptr, core};

    symmetric_difference_command cmd(left_table_name, right_table_name);
    auto result = cmd.execute(cntxt);
    ASSERT_TRUE(result.has_value());

    std::string expected_result = std::to_string(right_id) + " " + "---" + " " + right_value + "\n";
    ASSERT_EQ(result.value(), expected_result);
}
