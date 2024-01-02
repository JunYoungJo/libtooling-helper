//
// Created by junyoung jo on 1/2/24.
//


#include "CommandLineHelper.h"
#include <llvm/Support/CommandLine.h>

namespace helper::opt {

    CommandLineHelper::CommandLineHelper() {
        std::any_cast<CommandOption<std::vector<std::string>>>(
                _options.emplace("f", std::make_any<CommandOption<std::vector<std::string>>>("f")).first->second)
                .setDescription("<file1> <file2> ...").setNumOccurrences(Occurrence::ZeroOrMore).setPositional(true);

        std::any_cast<CommandOption<std::string>>(
                _options.emplace("d", std::make_any<CommandOption<std::string>>("d")).first->second)
                .setValueDescription("file").setDescription("Set compile_commands.json file path").setNumOccurrences(Occurrence::Required).setValueExpected(true);
    }

    CommandLineHelper::CommandLineHelper(helper::opt::CommandLineHelper &&other) noexcept: CommandLineHelper() {
        swap(*this, other);
    }

    CommandLineHelper &CommandLineHelper::operator=(helper::opt::CommandLineHelper &&other) noexcept {
        CommandLineHelper temporary{std::move(other)};
        swap(*this, temporary);
        return *this;
    }

    CommandLineHelper &CommandLineHelper::instance() {
        static CommandLineHelper _instance{};
        return _instance;
    }

    bool CommandLineHelper::parseCommandLine(int argc, char **argv) {
        auto allOptions = llvm::cl::getRegisteredOptions(llvm::cl::SubCommand::getTopLevel());

        for (auto &registeredOption: allOptions) {
            if (!std::any_of(_options.begin(), _options.end(), [&registeredOption](const std::pair<std::string, std::any> &userOption) {
                return registeredOption.second->ArgStr.equals(userOption.first);
            })) {
                registeredOption.second->setHiddenFlag(llvm::cl::ReallyHidden);
            }
        }

        return llvm::cl::ParseCommandLineOptions(argc, argv);
    }

} // namespace helper::opt