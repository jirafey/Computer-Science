//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"


/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {
    //wzór na look
    glm::vec3 look = cam.lookp - cam.eyep;
    //wzór na u
    glm::vec3 u = glm::cross(cam.up, look);
    u = glm::normalize(u);
    //wzór na v
    glm::vec3 v = glm::cross(u, look);
    v = glm::normalize(v);
    look = glm::normalize(look);
    //wzór na o
    glm::vec3 o = look * ((float)cam.width/(2 * tan((cam.fov/2)*3.14f / 180.0f))) - (((float)cam.width/2.0f * u) + ((float)cam.height/2.0f * v));
    //zapis do macierzy
    m[0][0] = u[0];
    m[0][1] = u[1];
    m[0][2] = u[2];
    m[1][0] = v[0];
    m[1][1] = v[1];
    m[1][2] = v[2];
    m[2][0] = o[0];
    m[2][1] = o[1];
    m[2][2] = o[2];
    return true;
}


bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& out) {
    CObject* obj;
    float tmin = FLT_MAX;
    float EPS = 0.0001f;
    bool isIntersection = false;
    for (CObject* obj: scene.objectList) {
        float t = obj->intersect(ray);
        if (t > EPS && t < tmin) {
            tmin = t;
            isIntersection = true;
        }
        if (isIntersection)
            out.col = {0, 0.5, 0};
        else
            out.col = {0, 0, 0};
    }
    return true;
}

/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;

    return reflected_ray;
}


