#include <Precompiled.hpp>
#include <scene/Camera.hpp>

using namespace eng;

// By convention, OpenGL is a right-handed system:
// +x = right
// +y = up
// +z = back
// -x = left
// -y = down
// -z = front

const vec3 Camera::WorldUp = vec3(0.0f, 1.0f, 0.0f);
