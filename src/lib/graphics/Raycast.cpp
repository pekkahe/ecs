#include <Precompiled.hpp>
#include <graphics/Raycast.hpp>
#include <core/Defines.hpp>

// https://github.com/opengl-tutorials/ogl/blob/master/misc05_picking/misc05_picking_custom.cpp
eng::gfx::Ray eng::gfx::cursorPosToWorldRay(double2 normalizedCursorPos, const Camera& camera)
{
    mat4 inverseProjectionMatrix = glm::inverse(camera.projectionMatrix);
    mat4 inverseViewMatrix = glm::inverse(camera.viewMatrix);

    // The near plane maps to Z = -1 in Normalized Device Coordinates
    vec4 rayStartNdc(
        normalizedCursorPos.x,
        normalizedCursorPos.y,
        -1.0,
        1.0f);

    vec4 rayEndNdc(
        normalizedCursorPos.x,
        normalizedCursorPos.y,
        0.0,
        1.0f);

    vec4 rayStartCamera = inverseProjectionMatrix * rayStartNdc;   
    rayStartCamera /= rayStartCamera.w;

    vec4 rayStartWorld = inverseViewMatrix * rayStartCamera;
    rayStartWorld /= rayStartWorld.w;

    vec4 rayEndCamera = inverseProjectionMatrix * rayEndNdc;  
    rayEndCamera /= rayEndCamera.w;

    vec4 rayEndWorld = inverseViewMatrix * rayEndCamera;
    rayEndWorld /= rayEndWorld.w;

    vec4 rayDirection = glm::normalize(rayEndWorld - rayStartWorld);

    Ray ray;
    ray.origin = vec3(rayStartWorld);
    ray.direction = vec3(rayDirection);
    return ray;
}

// http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
// Additional reference: http://antongerdelan.net/opengl/raycasting.html
bool eng::gfx::raycastObb(
    const Ray& ray,
    const BoundingBox& aabb,
    const mat4& modelMatrix, 
    float& intersectionDistance)
{
    // Largest or farthest "near" intersection found
    float minDistance = 0.0f;
    // Smallest or nearest "far" intersection found
    float maxDistance = 100000.0f;

    vec3 obbPositionWorldspace(
        modelMatrix[3].x, 
        modelMatrix[3].y, 
        modelMatrix[3].z);

    // Delta used to compute the intersections with the planes
    vec3 delta = obbPositionWorldspace - ray.origin;

    // Make a function to test intersection with the two planes 
    // perpendicular to a specific OBB axis
    auto testIntersection = [
        &ray,
        &delta,
        &minDistance, 
        &maxDistance](
            vec3 axis, 
            float aabbMin,
            float aabbMax)
    {
        float e = glm::dot(axis, delta);
        float f = glm::dot(ray.direction, axis);
        constexpr float epsilon = 0.001f;

        if (std::abs(f) > epsilon)
        {
            // Intersection with the "left" plane
            float t1 = (e + aabbMin) / f; 
            // Intersection with the "right" plane
            float t2 = (e + aabbMax) / f; 

            // t1 and t2 now contain distances between ray origin and ray-plane intersections, 
            // but we don’t know in what order, so we make sure that t1 represents the "near"
            // intersection and t2 the "far"
            if (t1 > t2)
            {
                float tMax = t1; 
                t1 = t2; 
                t2 = tMax; 
            }

            if (t2 < maxDistance)
            {
                maxDistance = t2;
            }

            if (t1 > minDistance)
            {
                minDistance = t1;
            }

            // If "far" is closer than "near", then there is NO intersection
            if (maxDistance < minDistance)
            {
                return false;
            }
        }
        else 
        {
            // Rare case: the ray is almost parallel to the planes,
            // so they don't have any "intersection"
            if (-e + aabbMin > 0.0f || -e + aabbMax < 0.0f)
            {
                return false;
            }
        }

        // Intersection is possible
        return true;
    };

    if (!testIntersection(
        vec3(
            modelMatrix[0].x,
            modelMatrix[0].y,
            modelMatrix[0].z),
        aabb.min().x,
        aabb.max().x))
    {
        return false;
    }
        
    if (!testIntersection(
        vec3(
            modelMatrix[1].x,
            modelMatrix[1].y,
            modelMatrix[1].z),
        aabb.min().y,
        aabb.max().y))
    {
        return false;
    }
        
    if (!testIntersection(
        vec3(
            modelMatrix[2].x,
            modelMatrix[2].y,
            modelMatrix[2].z),
        aabb.min().z,
        aabb.max().z))
    {
        return false;
    }

    intersectionDistance = minDistance;
    return true;
}
