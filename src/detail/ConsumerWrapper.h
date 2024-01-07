//
// Created by junyoung jo on 1/7/24.
//

#ifndef TOOLINGHELPER_CONSUMERWRAPPER_H
#define TOOLINGHELPER_CONSUMERWRAPPER_H

#include <clang/AST/ASTConsumer.h>
#include "VisitorWrapper.h"

namespace helper::detail {

    template<typename Delegate>
    class ConsumerWrapper : public clang::ASTConsumer {
    public:
        explicit ConsumerWrapper(Delegate *delegate) : _visitor(delegate) {}

        void HandleTranslationUnit(clang::ASTContext &context) final {
            auto decls = context.getTranslationUnitDecl()->decls();
            auto &sourceManager = context.getSourceManager();
            for (auto &decl: decls) {
                // visit only current main files.
                const auto &FileID = sourceManager.getFileID(decl->getLocation());
                if (FileID != sourceManager.getMainFileID())
                    continue;
                _visitor.TraverseDecl(decl);
            }
        };
    private:
        VisitorWrapper<Delegate> _visitor;
    };
} // namespace helper::detail

#endif //TOOLINGHELPER_CONSUMERWRAPPER_H
