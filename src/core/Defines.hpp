#pragma once

#include <cstdio>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <utility>

#include <array>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#include <functional>

#include <future>

#include <type_traits>
#include <typeinfo> 

#include <component/EntityId.hpp>

#include <core/Datatypes.hpp>
#include <core/Time.hpp>
#include <core/Traits.hpp>

#define MOVABLE_ONLY(T) T(const T&) = delete; \
						T(T&&) = default; \
						T& operator=(const T&) = delete; \
						T& operator=(T&&) = default;

#define NON_COPYABLE_NOR_MOVABLE T(const T&) = delete; \
					             T(T&&) = delete; \
						         T& operator=(const T&) = delete; \
								 T& operator=(T&&) = delete; 
							     