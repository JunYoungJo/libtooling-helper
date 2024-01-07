//
// Created by junyoung jo on 1/2/24.
//

#include "../src/opt/CommandLineHelper.h"
#include <catch2/catch_test_macros.hpp>

SCENARIO("CommandLineHelper can parse compile database file paths.") {
    std::vector<const char *> argv;
    argv.push_back("tests");
    auto &helper = helper::opt::CommandLineHelper::instance();

    GIVEN("a compilation database file path with the \"-d\" option") {
        argv.push_back("-d=compile_commands.json");

        THEN("command line parsing should succeed.") {
            REQUIRE(helper.parseCommandLine(argv.size(), const_cast<char **>(argv.data())) == true);
            AND_WHEN("try to get the compilation database file path") {
                THEN("returned file path must be the same as the input path") {
                    REQUIRE(helper.get<std::string>("d") == "compile_commands.json");
                }
            }
        }
    }
}

SCENARIO("CommandLineHelper can parse source file paths.") {
    std::vector<const char *> argv;
    argv.push_back("tests");
    argv.push_back("-d=compile_commands.json");
    auto &helper = helper::opt::CommandLineHelper::instance();

    GIVEN("a source files path") {
        argv.push_back("a.cpp");
        argv.push_back("b.cpp");

        THEN("command line parsing should succeed.") {
            REQUIRE(helper.parseCommandLine(argv.size(), const_cast<char **>(argv.data())) == true);
            AND_WHEN("try to get the source files path") {
                auto files = helper.get<std::vector<std::string>>("f").value();
                THEN("returned file path must be the same as the input path") {
                    REQUIRE(files.size() == 2);
                    REQUIRE(std::all_of(files.begin(), files.end(), [&argv](const std::string &file) {
                        return std::any_of(argv.begin(), argv.end(), [&file](const char *input) {
                            return std::string(input) == file;
                        });
                    }));
                }
            }
        }
    }
}

SCENARIO("CommandLineHelper can add user commands") {
    std::vector<const char *> argv;
    argv.push_back("tests");
    argv.push_back("-d=compile_commands.json");
    auto &helper = helper::opt::CommandLineHelper::instance();

    GIVEN("a default CommandLineHelper instance") {
        WHEN("add user commands") {
            auto result = helper.setOptionCommand<int>("u");
            result->get().setDescription("user input").setValueDescription("integer value").
                    setNumOccurrences(helper::opt::Occurrence::Required).setValueExpected("true");
            THEN("returned value is not nullopt") {
                REQUIRE(result != std::nullopt);
                AND_GIVEN("a user input with the user option") {
                    argv.push_back("-u=256");
                    WHEN("parse command line") {
                        THEN("the result of parsing the command line should be true") {
                            REQUIRE(helper.parseCommandLine(argv.size(), const_cast<char **>(argv.data())) == true);
                            AND_WHEN("try to get the user input") {
                                auto value = helper.get<int>("u");
                                THEN("returned value must be same as the input value") {
                                    REQUIRE(value != std::nullopt);
                                    REQUIRE(value.value() == 256);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
