#include <Precompiled.hpp>
#include <scene/Transform.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace eng;

mat4 Transform::modelMatrix() const
{
    //mat4 model(1.0f);
    //model = glm::translate(model, position);
    //model *= glm::mat4_cast(rotation);
    //model = glm::scale(model, scale);

    mat4 translate = glm::translate(mat4(1.0f), position);
    mat4 rotate    = glm::mat4_cast(rotation);
    mat4 scale_    = glm::scale(mat4(1.0f), scale);

    return translate * rotate * scale_;
}
