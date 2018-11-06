#pragma once

#include <core/Datatypes.hpp>
#include <graphics/AABB.hpp>
#include <graphics/OBB.hpp>
#include <scene/Camera.hpp>

namespace eng
{
    namespace gfx
    {
        struct Ray
        {
            // Ray origin in world space.
            vec3 origin = vec3(0);
            // Ray direction in world space, normalized.
            vec3 direction = vec3(0);
        };

        // Transform cursor position in Normalized Device Coordinates (NDC) into a ray with
        // a world space origin and direction.
        //   'normalizedCursorPos' : Screen position to transform in range [-1,-1] to [1,1].
        //   'camera' : Camera with a view and projection matrix.
        // Returns a ray representing the cursor position, usable in raycasting.
        Ray cursorPosToWorldRay(double2 normalizedCursorPos, const Camera& camera);

        // Raycast algorithm based on an Oriented Bounding Box (OOB).
        //   'ray' : Ray origin and direction, in world space.
        //   'aabb' : Axis-aligned bounding box of the mesh to check against ray intersection.
        //   'modelMatrix' : Transformation applied to the mesh, which will thus be also applied to its bounding box.
        //   'intersectionDistance' : Additional output; distance between 'origin' and the intersection with the OBB
        // Returns true if the ray intersects with the oriented bounding box, otherwise false.
        bool raycastObb(
            const Ray& ray,
            const AABB& aabb,
            const mat4& modelMatrix,
            float& intersectionDistance);

        // Algorithms taken from "Game Physics Cookbook" chapter "3D Line Intersections"

        float raycast(const Ray& ray, const AABB& aabb);

        float raycast(const Ray& ray, const OBB& obb);
    }
}
