//
// Created by junyoung jo on 1/7/24.
//

#ifndef TOOLINGHELPER_DELEGATEINTERFACE_H
#define TOOLINGHELPER_DELEGATEINTERFACE_H

#include "type/TypeDefine.h"
#include "detail/ConsumerWrapper.h"

namespace helper {

    template<typename Impl>
    class DelegateInterface {
    public:
        bool VisitNamedDecl(type::NamedDecl *decl) {
            return (*static_cast<Impl *>(this))(decl);
        }

        bool VisitVarDecl(type::VarDecl *decl) {
            return (*static_cast<Impl *>(this))(decl);
        }

        bool VisitFunctionDecl(type::FunctionDecl *decl) {
            return (*static_cast<Impl *>(this))(decl);
        }

        bool VisitCallExpr(type::CallExpr *expr) {
            return (*static_cast<Impl *>(this))(expr);
        }
    };

} // namespace helper

#endif //TOOLINGHELPER_DELEGATEINTERFACE_H
