#include "swIntersection.h"

namespace sw {

Ray Intersection::getShadowRay(const Vec3 &lightPos) {
    Vec3 L = lightPos - position;
    float tMax = sqrt(L * L);
    return Ray(position, L.normalize(), 0.01f, tMax);
}

Ray Intersection::getReflectedRay(void) {
    Vec3 N = normal;
    const Vec3 D = ray.dir;

    Vec3 R = D-2*(N*D)*N;

    return Ray(position, R, 0.01f, FLT_MAX);
}

Ray Intersection::getRefractedRay(void) {
    const Vec3 &D = ray.dir;
    Vec3 N = normal;
    float eta = 1.0f / material.refractiveIndex;
    if (!frontFacing) eta = 1.0f / eta; // Inside material.

    // TODO: Implement refraction
    // -------------------
    float R = -D*N;
    float c = 1 - (eta * eta) * (1 - R*R);
    if (c < 0) return getReflectedRay();
    Vec3 t = eta * D + (eta * R - sqrt(c))* N;
    // -------------------
    return Ray(position, t, 0.01f, FLT_MAX);
}

} // namespace sw
