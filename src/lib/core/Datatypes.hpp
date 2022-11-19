#pragma once

#include <core/ecs/EntityId.hpp>

#include <utility>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/vec_swizzle.hpp>

namespace eng
{
    template <typename T>
    struct Point2
    {
        T x;
        T y;
    };

    using int2 = Point2<int>;
    using float2 = Point2<float>;
    using double2 = Point2<double>;
    
    using ivec1 = glm::ivec1;
    using ivec2 = glm::ivec2;
    using ivec3 = glm::ivec3;
    using ivec4 = glm::ivec4;

    using uvec1 = glm::uvec1;
    using uvec2 = glm::uvec2;
    using uvec3 = glm::uvec3;
    using uvec4 = glm::uvec4;

    using vec1 = glm::vec1;
    using vec2 = glm::vec2;
    using vec3 = glm::vec3;
    using vec4 = glm::vec4;

    using mat2 = glm::mat2;
    using mat3 = glm::mat3;
    using mat4 = glm::mat4;

    using qua = glm::quat;
}
