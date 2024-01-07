//
// Created by junyoung jo on 1/7/24.
//

#ifndef TOOLINGHELPER_WORKER_H
#define TOOLINGHELPER_WORKER_H

#include "type/TypeDefine.h"
#include "detail/ConsumerWrapper.h"

namespace helper {

    template<typename Delegate>
    class Worker {
    public:
        Worker() : _consumer(&_delegate) {}

        void work(const type::ASTUnit &astUnit) {
            _consumer.HandleTranslationUnit(astUnit->getASTContext());
        }

    private:
        detail::ConsumerWrapper<Delegate> _consumer;
        Delegate _delegate;
    };

} // namespace helper

#endif //TOOLINGHELPER_WORKER_H
