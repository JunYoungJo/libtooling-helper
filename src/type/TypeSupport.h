//
// Created by junyoung jo on 1/2/24.
//

#ifndef TOOLINGHELPER_TYPESUPPORT_H
#define TOOLINGHELPER_TYPESUPPORT_H

#include <clang/Frontend/ASTUnit.h>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

namespace helper::type {
    template<typename T>
    struct is_container : public std::false_type {
        using TYPE = void;
    };

    template<typename T, typename Allocator>
    struct is_container<std::vector<T, Allocator>> : public std::true_type {
        using TYPE = T;
    };

    template<typename T>
    inline constexpr bool is_container_v = is_container<T>::value;

    template<typename T>
    using container_value_t = typename is_container<T>::TYPE;

    template<typename T>
    inline constexpr bool is_supported = (std::is_same_v<T, int> || std::is_same_v<T, char> || std::is_same_v<T, bool> || std::is_same_v<T, std::string>);

} // namespace helper::type


#endif //TOOLINGHELPER_TYPESUPPORT_H
