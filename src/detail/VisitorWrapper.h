//
// Created by junyoung jo on 1/7/24.
//

#ifndef TOOLINGHELPER_VISITORWRAPPER_H
#define TOOLINGHELPER_VISITORWRAPPER_H

#include <clang/AST/RecursiveASTVisitor.h>
#include "../type/TypeDefine.h"

namespace helper::detail {

    template<typename Delegate>
    class VisitorWrapper : public clang::RecursiveASTVisitor<VisitorWrapper<Delegate>> {
    public:
        explicit VisitorWrapper(Delegate *delegate) : _delegate(delegate) {}

        bool VisitNamedDecl(clang::NamedDecl *decl) {
            return _delegate->VisitNamedDecl(decl);
        }

        bool VisitVarDecl(clang::VarDecl *decl) {
            return _delegate->VisitVarDecl(decl);
        }

        bool VisitFunctionDecl(clang::FunctionDecl *decl) {
            return _delegate->VisitFunctionDecl(decl);
        }

        bool VisitCallExpr(clang::CallExpr *expr) {
            return _delegate->VisitCallExpr(expr);
        }
    private:
        Delegate *_delegate;
    };
} // namespace helper::detail

#endif //TOOLINGHELPER_VISITORWRAPPER_H
