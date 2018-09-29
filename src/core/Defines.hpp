#pragma once

// Common C++ headers
#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <utility>
#include <ctime>

#include <array>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include <functional>
#include <future>

#include <type_traits>
#include <typeinfo> 

#define MOVABLE_ONLY(T) \
        T(const T&) = delete; \
        T(T&&) = default; \
        T& operator=(const T&) = delete; \
        T& operator=(T&&) = default;

#define NON_COPYABLE_NOR_MOVABLE(T) \
        T(const T&) = delete; \
        T(T&&) = delete; \
        T& operator=(const T&) = delete; \
        T& operator=(T&&) = delete; 

#define ENUM_FLAG_OPERATOR(T, X) \
        inline T operator X(T lhs, T rhs) { \
        return (T) (static_cast<std::underlying_type_t<T>>(lhs) X static_cast<std::underlying_type_t<T>>(rhs)); } \
        inline T& operator X=(T& lhs, T rhs) { \
        lhs = (T)(static_cast<std::underlying_type_t<T>>(lhs) X static_cast<std::underlying_type_t<T>>(rhs)); \
        return lhs; }

#define ENUM_FLAGS(T) \
        enum class T; \
        inline T operator~(T t) { return (T) (~static_cast<std::underlying_type_t<T>>(t)); } \
        ENUM_FLAG_OPERATOR(T, |) \
        ENUM_FLAG_OPERATOR(T, ^) \
        ENUM_FLAG_OPERATOR(T, &) \
        enum class T

// Common system headers
#include <component/EntityId.hpp>

#include <core/Datatypes.hpp>
#include <core/Logger.hpp>
#include <core/Time.hpp>
#include <core/Traits.hpp>