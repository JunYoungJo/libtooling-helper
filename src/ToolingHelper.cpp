//
// Created by junyoung jo on 1/3/24.
//

#include "ToolingHelper.h"


namespace helper {
    ToolingHelper::ToolingHelper(const clang::tooling::CompilationDatabase &Compilations, const std::vector<std::string> &SourcePaths) : _tool(Compilations, SourcePaths) {}

    bool ToolingHelper::buildAST() {
        return _tool.buildASTs(_asts) == 0;
    }
} // namespace helper
