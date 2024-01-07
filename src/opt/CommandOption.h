//
// Created by junyoung jo on 1/2/24.
//

#ifndef LIBTOOLING_HELPER_COMMANDOPTION_H
#define LIBTOOLING_HELPER_COMMANDOPTION_H

#include "../type/TypeSupport.h"
#include <llvm/Support/CommandLine.h>
#include <cstdint>
#include <iostream>

namespace helper::opt {
    ///
    /// \brief wrapper of llvm::cl::NumOccurrencesFlag
    ///
    enum class Occurrence : std::uint8_t {
        Optional,
        ZeroOrMore,
        Required,
        OneOrMore
    };

    ///
    /// @brief wrapper class of llvm::cl::list and llvm::cl::opt
    /// @tparam ValueType One of the following types: int, char, bool, std::string, std::vector<std::string>
    ///
    template<typename ValueType>
    class CommandOption {
    public:
        using OperationType = std::conditional_t<helper::type::is_container_v<ValueType>, llvm::cl::list<typename helper::type::container_value_t<ValueType>>, llvm::cl::opt<ValueType>>;

        ///
        /// \brief Constructor of CommandOption class.
        /// \param cmd command character.
        /// \details
        ///
        explicit CommandOption(llvm::StringRef cmd) : _option(std::make_shared<OperationType>(cmd, llvm::cl::desc(""), llvm::cl::value_desc(""), llvm::cl::Optional, llvm::cl::ValueOptional, llvm::cl::DefaultOption, llvm::cl::NormalFormatting)) {}

        CommandOption(const CommandOption &other) = default;

        CommandOption(CommandOption &&other) noexcept: CommandOption() {
            swap(*this, other);
        }

        virtual ~CommandOption() = default;

        CommandOption &operator=(const CommandOption &other) = default;

        CommandOption &operator=(CommandOption &&other) noexcept {
            CommandOption temporary{other};
            swap(*this, other);
        }

        friend void swap(CommandOption<ValueType> &first, CommandOption<ValueType> &second) noexcept {
            using std::swap;
            swap(first._option, second._option);
        }

        ///
        /// \brief Set command description.
        /// \param desc Description string of the command.
        /// \return this
        ///
        [[maybe_unused]] CommandOption<ValueType> &setDescription(llvm::StringRef desc) {
            _option->setDescription(desc);
            return *this;
        }

        ///
        /// \brief Set value description.
        /// \param valueDesc Description string of the value.
        /// \return this
        ///
        [[maybe_unused]] CommandOption<ValueType> &setValueDescription(llvm::StringRef valueDesc) {
            _option->setValueStr(valueDesc);
            return *this;
        }

        ///
        /// \brief Controlling the number of occurrences required and allowed.
        /// \param occurrence One of the following values: Optional, ZeroOrMore, Required, OneOrMore
        /// \return this
        /// \see <a href="https://llvm.org/docs/CommandLine.html#controlling-the-number-of-occurrences-required-and-allowed">LLVM CommandLine Library Manual</a>
        ///
        [[maybe_unused]] CommandOption<ValueType> &setNumOccurrences(helper::opt::Occurrence occurrence) {
            switch (occurrence) {
                case Occurrence::Optional:
                    _option->setNumOccurrencesFlag(llvm::cl::Optional);
                    break;
                case Occurrence::ZeroOrMore:
                    _option->setNumOccurrencesFlag(llvm::cl::ZeroOrMore);
                    break;
                case Occurrence::Required:
                    _option->setNumOccurrencesFlag(llvm::cl::Required);
                    break;
                case Occurrence::OneOrMore:
                    _option->setNumOccurrencesFlag(llvm::cl::OneOrMore);
                    break;
            }
            return *this;
        }

        ///
        /// \brief Controlling whether or not a value must be specified.
        /// \param isRequired
        /// \return  this
        /// \see <a href="https://llvm.org/docs/CommandLine.html#controlling-whether-or-not-a-value-must-be-specified">LLVM CommandLine Library Manual</a>
        ///
        [[maybe_unused]] CommandOption<ValueType> &setValueExpected(bool isRequired) {
            if (isRequired) {
                _option->setValueExpectedFlag(llvm::cl::ValueRequired);
            }
            return *this;
        }

        ///
        /// \brief Miscellaneous option modifiers.
        /// \param isCommaSeparated
        /// \return this
        /// \see <a href="https://llvm.org/docs/CommandLine.html#miscellaneous-option-modifiers">LLVM CommandLine Library Manual</a>
        ///
        [[maybe_unused]] CommandOption<ValueType> &setCommaSeparated(bool isCommaSeparated) {
            if (isCommaSeparated) {
                _option->setMiscFlag(llvm::cl::CommaSeparated);
            }
            return *this;
        }

        ///
        /// \brief Set Positional Arguments.
        /// \param isPositional
        /// \return this
        /// \see <a href="https://llvm.org/docs/CommandLine.html#positional-options">LLVM CommandLine Library Manual</a>
        ///
        [[maybe_unused]] CommandOption<ValueType> &setPositional(bool isPositional) {
            if (isPositional) {
                _option->setFormattingFlag(llvm::cl::Positional);
            }
            return *this;
        }

        ///
        /// \brief Get command line input values.
        /// \return list of input values.
        ///
        template<typename U = ValueType, typename std::enable_if_t<helper::type::is_container_v<U>, bool> = true>
        ValueType get() {
            return *_option;
        }

        ///
        /// \brief Get command line input values.
        /// \return value.
        ///
        template<typename U = ValueType, typename std::enable_if_t<!(helper::type::is_container_v<U>), bool> = true>
        ValueType get() {
            return _option->getValue();
        }

    private:
        CommandOption() : _option(nullptr) {}

        std::shared_ptr<OperationType> _option; ///< One of the following types: llvm::cl::list or llvm::cl::opt.
    };
} // namespace helper::opt

#endif //LIBTOOLING_HELPER_COMMANDOPTION_H
