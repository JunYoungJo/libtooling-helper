//
// Created by junyoung jo on 1/2/24.
//

#ifndef TOOLINGHELPER_COMMANDLINEHELPER_H
#define TOOLINGHELPER_COMMANDLINEHELPER_H

#include "CommandOption.h"
#include <any>
#include <map>
#include <string>

namespace helper::opt {
    ///
    /// \brief Commandline Helper class.
    ///
    class CommandLineHelper {
    public:

        CommandLineHelper(const CommandLineHelper &other) = delete;

        CommandLineHelper(CommandLineHelper &&other) noexcept;

        virtual ~CommandLineHelper() = default;

        CommandLineHelper &operator=(const CommandLineHelper &other) = delete;

        CommandLineHelper &operator=(CommandLineHelper &&other) noexcept;

        ///
        /// \return Instance of CommandLineHelper class.
        ///
        static CommandLineHelper &instance();

        friend void swap(CommandLineHelper &first, CommandLineHelper &second) noexcept {
            using std::swap;
            swap(first._options, second._options);
        }

        ///
        /// \brief Parse commands with given input values.
        /// \param userOption The number of arguments.
        /// \param argv  Arguments.
        /// \return Returns true if commandline parsing is successful, false otherwise.
        ///
        bool parseCommandLine(int userOption, char **argv);

        ///
        /// \brief Set new command.
        /// \tparam T Type of input value to be assigned to the command.
        /// \param cmd Commandline character.
        /// \return Returns true if successful, false otherwise.
        ///
        template<typename T>
        std::optional<std::reference_wrapper<CommandOption<T>>> setOptionCommand(const std::string &cmd) {
            auto result = _options.emplace(cmd, std::make_any<CommandOption < T>>
            (cmd));
            return result.second ? std::optional<std::reference_wrapper<CommandOption < T>> > {std::any_cast<CommandOption < T> & >(result.first->second)} : std::nullopt;
        }

        ///
        /// \brief Return the input value of the command.
        /// \tparam T Type of input value.
        /// \param cmd Commandline character to get input value.
        /// \return If T is a type that matches the command character, it returns a value, otherwise it returns std::nullopt.
        ///
        template<typename T>
        std::optional<T> get(const std::string &cmd) {
            try {
                return std::optional<T>(std::any_cast<CommandOption < T> & > (_options.at(cmd)).get());
            } catch (const std::bad_any_cast &exception) {
                return std::nullopt;
            }
        }

    private:
        CommandLineHelper();

        std::map<std::string, std::any> _options;
    };
} // namespace helper::opt

#endif //TOOLINGHELPER_COMMANDLINEHELPER_H
