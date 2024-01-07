//
// Created by junyoung jo on 1/7/24.
//

#ifndef TOOLINGHELPER_WORKERFACTORY_H
#define TOOLINGHELPER_WORKERFACTORY_H

#include "Worker.h"

namespace helper {
    class WorkerFactory {
    public:
        ///
        /// \tparam Delegate See DelegateInterface.
        /// \return Worker class.
        ///
        template<typename Delegate>
        static Worker<Delegate> create() { return Worker<Delegate>(); };
    };
}

#endif //TOOLINGHELPER_WORKERFACTORY_H
