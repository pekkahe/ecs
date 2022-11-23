#pragma once

#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
#ifdef _MSC_VER
	#pragma warning( push )
	#pragma warning( disable : 4201)
#endif
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#ifdef _MSC_VER
	#pragma warning( pop )
#endif
