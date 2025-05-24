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
    auto look = cam.lookp - cam.eyep;
    auto u = glm::normalize(glm::cross(cam.up,look));
    auto v = glm::normalize(glm::cross(u,look));
    glm::vec3 o = glm::normalize(look)*(cam.width/(2*std::tan(3.14f*(cam.fov/2)/180.0f))) - ((float)(cam.width/2)*u + (float)(cam.height/2)*v);

    m = glm::mat3(u,v,o);


    return true;
}


/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///
bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& out) {
    CObject* hit_object;
    int MAX_RAY_TREE = 1;
    float MIN_RAY_ENERGY = 0.01;
    float tmin = FLT_MAX;
    float EPS = 0.00001f;
    bool isIntersection = false;

    float tShadowmin = FLT_MAX;
    // stare
    for(auto obj : scene.objectList){
        float t = obj->intersect(ray);
        if(t > EPS && t < tmin){
            tmin = t;
            hit_object = obj;
            isIntersection = true;
        }
    }


    if(isIntersection){
        //out.col= glm::vec3(0,0.5,0);
    }
    else{
        //out.col= glm::vec3(0,0.0,0);
        return isIntersection;
    }
    // nowe
    glm::vec3 hit_point = ray.pos + tmin *ray.dir;

    /// computes 3D position of the intersection point

    /// computes normal vector at intersection point
    glm::vec3  n;
    /// for each it source defined in the scene

        for (auto it : scene.lightList)
        {
            /// computes if the intersection point is in the shadows
            out.col = out.col + out.energy * it.color * hit_object->matAmbient;
            /// computes diffuse color component
            n = hit_object->normal(hit_point);
            glm::vec3  L = glm::normalize(it.pos-hit_point);

           const CRay shadowRay {hit_point,glm::normalize(it.pos - hit_point)};

            bool isIntersectionShadow {false};
            for(auto obj : scene.objectList){
                float tShadow = obj->intersect(shadowRay);
                if(tShadow > EPS && tShadow < tmin){
                    if(obj != hit_object) {
                        hit_object = obj;
                        tShadowmin = tShadow;
                        isIntersectionShadow = true;
                    }
                }
                if(isIntersectionShadow)
                    break;
            }
            if(isIntersectionShadow)
                continue;



            float cos_angle = glm::dot(n,L);
            if(cos_angle > 0.001){

                out.col = out.col + out.energy * it.color * hit_object->matDiffuse * cos_angle;

                glm::vec3 h = glm::normalize(L-ray.dir);

                float cos_beta = glm::dot(n,h);

                if(cos_beta > 0.001){
                    // compute and add specular color component
                    out.col = out.col + out.energy * it.color * hit_object->matSpecular * pow(cos_beta,hit_object->matShininess);
                }

            }

            if(hit_object->reflectance > 0 && out.tree < MAX_RAY_TREE && out.energy > MIN_RAY_ENERGY){
                out.tree++;
                out.energy = out.energy*hit_object->reflectance;
                CRay secondary_ray = reflectedRay(ray,n,hit_point);

                rayTrace(scene,secondary_ray, out);
            }

        }
    /// adds texture for textured spheres
    if(hit_object->isTexture){
       // print_vec3("Normal: ",n);
        glm::vec2 uv = hit_object->textureMapping(n);

       // std::cout << "U: " << uv.x << " V: " << uv.y << std::endl;
        glm::vec3 text_col = CImage::getTexel(hit_object->texture, uv.x, uv.y);
       // print_vec3("Vis ", text_col);
        out.col = out.col * text_col;
    }

    return isIntersection;
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

    reflected_ray.pos = pos;
    glm::vec3 v = ray.dir;
    glm::vec3 r = v-(2.0f*glm::dot(v,n))*n;
    reflected_ray.dir = glm::normalize(r);

    return reflected_ray;
}


