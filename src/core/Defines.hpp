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
#include <deque>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include <chrono>
#include <thread>
#include <functional>
#include <future>

#include <type_traits>
#include <typeinfo> 

#define NOMINMAX

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

#define ENUM_FLAG_OPERATOR(T, OPERATOR) \
        inline T operator OPERATOR(T lhs, T rhs) { \
        return (T) (static_cast<std::underlying_type_t<T>>(lhs) OPERATOR static_cast<std::underlying_type_t<T>>(rhs)); } \
        inline T& operator OPERATOR ## =(T& lhs, T rhs) { \
        lhs = (T)(static_cast<std::underlying_type_t<T>>(lhs) OPERATOR static_cast<std::underlying_type_t<T>>(rhs)); \
        return lhs; }

#define ENUM_FLAGS(T) \
        enum class T; \
        inline T operator~(T t) { return (T) (~static_cast<std::underlying_type_t<T>>(t)); } \
        ENUM_FLAG_OPERATOR(T, |) \
        ENUM_FLAG_OPERATOR(T, ^) \
        ENUM_FLAG_OPERATOR(T, &) \
        enum class T

// Core system headers
#include <core/Datatypes.hpp>
#include <core/Logger.hpp>
#include <core/Math.hpp>
#include <core/Time.hpp>
#include <core/Traits.hpp>

// Core tag components
#include <core/Added.hpp>
#include <core/Deleted.hpp>
#include <core/Updated.hpp>
