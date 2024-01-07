//
// Created by junyoung jo on 1/3/24.
//

#ifndef TOOLINGHELPER_TOOLINGHELPER_H
#define TOOLINGHELPER_TOOLINGHELPER_H

#include "DelegateInterface.h"
#include <clang/Tooling/Tooling.h>
#include <memory>
#include <iostream>
#include <vector>
#include "Worker.h"

namespace helper {

    class ToolingHelper {
    public:
        ToolingHelper(const clang::tooling::CompilationDatabase &Compilations, const std::vector<std::string> &SourcePaths);

        template<typename T>
        bool run(T &worker) {
            bool isSuccess;
            if (isSuccess = this->buildAST(); isSuccess) {
                for (auto const &ast: _asts) {
                    worker.work(ast);
                }
            }
            return isSuccess;
        }

    private:
        bool buildAST();

        clang::tooling::ClangTool _tool;
        helper::type::ASTList _asts;
    };
} // namespace helper

#endif //TOOLINGHELPER_TOOLINGHELPER_H
