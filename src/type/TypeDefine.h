//
// Created by junyoung jo on 1/7/24.
//

#ifndef TOOLINGHELPER_TYPEDEFINE_H
#define TOOLINGHELPER_TYPEDEFINE_H

#include <clang/AST/Decl.h>
#include <clang/AST/Expr.h>
#include <clang/Frontend/ASTUnit.h>
#include <clang/Tooling/CompilationDatabase.h>

namespace helper::type {

    using ASTUnit = std::unique_ptr<clang::ASTUnit>;
    using ASTList = std::vector<ASTUnit>;
    using ASTContext = clang::ASTContext;
    using SourceManager = clang::SourceManager;
    using NamedDecl = clang::NamedDecl;
    using VarDecl = clang::VarDecl;
    using FunctionDecl = clang::FunctionDecl;
    using CallExpr = clang::CallExpr;
    using CompilationDatabase = clang::tooling::CompilationDatabase;

} // namespace helper::type

#endif //TOOLINGHELPER_TYPEDEFINE_H
