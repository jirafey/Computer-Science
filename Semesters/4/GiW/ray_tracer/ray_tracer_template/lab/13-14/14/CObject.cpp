//
//  CObject.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include "CObject.hpp"


/// \fn intersect(CRay ray)
/// \brief Computes intersection between ray and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CSphere::intersect(const CRay& ray) {
    float t = -1;

    auto v = (ray.pos-this->pos);
    auto A = glm::dot(ray.dir,ray.dir);
    auto B = ((float)2*glm::dot(v,ray.dir));
    auto C = glm::dot(v,v)-(this->r*this->r);
    auto del = B*B-4.0f*A*C;

    if (del < 0)
        return t;
    auto t1 = (-1.0f*B+ glm::sqrt(del))/(2.0f*A);
    auto t2 = (-1.0f*B- glm::sqrt(del))/(2.0f*A);

    if(t1 < 0){
        if (t2 < 0){

        }
        else
        {
            t = t2;
        }
    }
    else{
        if (t2 < 0){
            t = t1;
        }
        else
        {
            t = t1 < t2 ? t1:t2;
        }
    }

    return t;
}


/// Normal vector to the sphere surface
/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point.
/// \return Normal vector parameters.
///
glm::vec3 CSphere::normal(const glm::vec3& hit_pos) {
    glm::vec3 n = {0,0,0};

    n = glm::normalize(hit_pos-this->pos);


    return n;
}

/// Computes texture mapping coordinates (u,v).
/// \param normal_vec Normalized normal vector at intersection point.
/// \return (u,v) texture coordinates in <0,1> range.
glm::vec2 CSphere::textureMapping(const glm::vec3& normal_vec) {
    glm::vec2 uv = {0,0};
    uv.x = 0.5f+asin(normal_vec.x)/M_PI;
    uv.y = 0.5f-asin(normal_vec.y)/M_PI;
    return uv;
}

glm::vec3 konwersjadocartesian(const glm::vec3& x, const glm::vec3& y, const glm::vec3& z, const glm::vec3& bary) {
    return bary.x * x + bary.y * y + bary.z * z;
}


float CTriangle::intersect(const CRay& ray) {
    //wektor na wsp barycentr.
    float t = -1;
    glm::vec3 pktbary;
    bool przeciecie = glm::intersectRayTriangle(ray.pos, ray.dir, v0, v1, v2, pktbary);
    if (przeciecie == true) {
        glm::vec3 norm = normal(pktbary);
        glm::vec3 trCent = (v0+v1+v2)/3.0f;
        glm::intersectRayPlane(ray.pos,ray.dir,trCent,norm,t);
    }
    return t;
}



/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point (not used for triangle).
/// \return Normal vector parameters.
///
glm::vec3 CTriangle::normal(const glm::vec3& hit_pos) {
    glm::vec3 u = this->v1 - this->v0;
    glm::vec3 v = this->v2 - this->v0;
    return glm::normalize(glm::cross(u,v));

}
