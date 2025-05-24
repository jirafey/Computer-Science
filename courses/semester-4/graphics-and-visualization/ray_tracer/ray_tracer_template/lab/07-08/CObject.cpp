// CObject.cpp

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

    double A = glm::dot(ray.dir, ray.dir);
    glm::vec3 v = ray.pos - pos;

    double B = 2 * glm::dot(v, ray.dir);
    double C = glm::dot(v, v) - r * r ;

    double delta =  B * B - 4 * A * C;
    double t1 = (- B + sqrt(delta))/ 2 * A;
    double t2 = (- B - sqrt(delta))/ 2 * A;
    if (t1 > 0 && t1 > t2){
        return t1;
    }
    if (t2 > 0 && t2 > t1){
        return t2;
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

    return n;
}

/// Computes texture mapping coordinates (u,v).
/// \param normal_vec Normalized normal vector at intersection point.
/// \return (u,v) texture coordinates in <0,1> range.
glm::vec2 CSphere::textureMapping(const glm::vec3& normal_vec) {
    glm::vec2 uv = {0,0};

    return uv;
}



/// \fn intersect(CRay ray)
/// \brief Computes intersection between triangle and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CTriangle::intersect(const CRay& ray) {
    float t = -1;

    return t;
}


/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point (not used for triangle).
/// \return Normal vector parameters.
///
glm::vec3 CTriangle::normal(const glm::vec3& hit_pos) {
    glm::vec3 n;

    return n;
}


// CScene.cpp
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create() {

    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects
    // add camera, light sources, and objects
    //    cam.eyep = {0, 0, 10};
    //    cam.lookp = {0, 0, 0};
    //    cam.up = {0, 1, 0};
    //    cam.fov = 50;
    //    cam.width = 500;
    //    cam.height = 400;

    cam.eyep = {2, 5, 10};
    cam.lookp = {-2, 1, 0};
    cam.up = {0, 1, 0};
    cam.fov = 50;
    cam.width = 500;
    cam.height = 400;
    //    objectList.add();

    //    CSphere* sphere = new CSphere ({ -2.5 ,1.3 , -3} , 1.0);
    //    CSphere* sphere2 = new CSphere ({ 0,0,0} , 1.6);
    //    objectList.push_back(sphere);
    //    objectList.push_back(sphere2);
}


