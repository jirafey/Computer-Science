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

    CObject* hit_obj;
    float tmin = FLT_MAX;
    float EPS = 0.0001f;
    bool isIntersection = false;
    for (CObject* obj: scene.objectList) {
        float t = obj->intersect(ray);
        if (t > EPS && t < tmin) {
            tmin = t;
            hit_obj = obj;
            isIntersection = true;
        }
        if (isIntersection)
            out.col = {0, 0.5, 0};
        else
            out.col = {0, 0, 0};
            return false;
    }
    // stare


//     // nowe
//     glm::vec3 p = ray.pos + tmin * ray.dir;
//         for (auto it : scene.lightList)
//         {
// // compute and add ambient color component
// out.col = out.col + it.color * hit_obj->matAmbient;
// // compute normal vector at p
// glm::vec3 n = hit_obj->normal(p);
// // compute vector from p to light position
// glm::vec3 L = glm::normalize(it.pos -p);
// // compute angle between n and vector to light
//                 float cos_angle = glm::dot(n, L);
//                 if(cos_angle > 0.001)
//                 {
// // compute and add diffuse color component
//                     out.col = out.col + it.color * hit_obj->matDiffuse * cos_angle;
// // compute half angle vector h
//                     glm::vec3 h = glm::normalize(L + -ray.dir);
// // compute angle between n and h
//                     float cos_beta = glm::dot(n, h);
//                     if (cos_beta > 0.001) {
// // compute and add specular color component
//                         out.col = out.col + it.color * hit_obj->matSpecular * (float) pow(cos_beta,hit_obj->matShininess);
//                     }
//                 }
//         }
//     return true;

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



