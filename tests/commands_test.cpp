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

    try {
        check_syntax_command cmd(request);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        ASSERT_FALSE(true);
    }

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

    try {
        check_syntax_command cmd(request);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        ASSERT_FALSE(true);
    }

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

    try {
        check_syntax_command cmd(request);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        ASSERT_FALSE(true);
    }

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

    try {
        check_syntax_command cmd(request);
        cmd.execute(cntxt);
    } catch (const command_handling_exception& ex) {
        ASSERT_FALSE(true);
    }

    ASSERT_EQ(core->_exec_units.size(), 1);
    ASSERT_NE(dynamic_cast<symmetric_difference_command*>(core->_exec_units.front()->command.get()), nullptr);
}
