#include <Precompiled.hpp>
#include <scene/Transform.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace eng;

mat4 Transform::modelMatrix() const
{
    mat4 model(1.0f);
    model = glm::translate(model, position);
    model *= glm::mat4_cast(rotation);
    model = glm::scale(model, scale);
    // translate * rotate * scale

    //glm::mat4 translate = glm::translate(glm::mat4(1.0), position);
    //glm::mat4 rotate = glm::mat4_cast(rotation);
    //glm::mat4 scale = glm::scale(glm::mat4(1.0f), this->scale);
    //glm::mat4 model = translate * rotate * scale;

    return model;
}
