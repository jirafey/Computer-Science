//
//  CScene.cpp
//  rt
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

    cam.eyep = glm::vec3(0,-4,10);
    cam.lookp = glm::vec3 (0,0,0);
    cam.up = glm::vec3 (0,1,0);
    cam.fov = 50;
    cam.width = 500;
    cam.height = 400;

    /// light01
    CLight light1(glm::vec3(-3,-2,8));
    light1.color = {0.6,0.6,0.6};
    lightList.push_back(light1);


    /// light02
    CLight light2(glm::vec3(5,-2,8));
    light2.color = {0.3,0.3,0.3};
    lightList.push_back(light2);


    /// sphere01
    CSphere* sphere01 = new CSphere({0, 0, 0}, 1.6);
    sphere01->matAmbient = {0.1, 0.0, 0.0};
    sphere01->matDiffuse = {0.6, 0.0, 0.0};
    sphere01->matSpecular = {0.7, 0.7, 0.7};
    sphere01->matShininess = 30;
    sphere01->reflectance = 0;
    sphere01->isTexture = false;
    objectList.push_back(sphere01);



    /// sphere02
    CSphere* sphere02 = new CSphere({-1, 0, 3}, 0.4);
    sphere02->matAmbient = {0.0, 0.1, 0.0};
    sphere02->matDiffuse = {0.0, 0.6, 0.0};
    sphere02->matSpecular = {0.7, 0.7, 0.7};
    sphere02->matShininess = 30;
    sphere02->reflectance = 0;
    sphere02->isTexture = false;
    objectList.push_back(sphere02);


    /// sphere03
    CSphere* sphere03 = new CSphere({-3, -2, -2}, 0.6);
    sphere03->matAmbient = {0.0, 0.0, 0.1};
    sphere03->matDiffuse = {0.0, 0.0, 0.6};
    sphere03->matSpecular = {0.7, 0.7, 0.7};
    sphere03->matShininess = 30;
    sphere03->reflectance = 0;
    sphere03->isTexture = false;
    objectList.push_back(sphere03);


    /// triangle01
    glm::vec3 v01 = {5,5,-5};
    glm::vec3 v11 = {-5,5,-5};
    glm::vec3 v21= {-5,-5,-5};

    CTriangle* triangle01 = new CTriangle(v01,v11,v21);
    triangle01->matAmbient = {0.1,0.1,0.1};
    triangle01->matDiffuse = {0.4,0.4,0.4};
    triangle01->matSpecular = {0,0,0};
    triangle01->matShininess = 0;
    triangle01->reflectance = 1;
    triangle01->isTexture = false;
    objectList.push_back(triangle01);



    /// triangle02
    glm::vec3 v02 = {5,5,-5};
    glm::vec3 v12 = {-5,-5,-5};
    glm::vec3 v22= {5,-5,-5};

    CTriangle* triangle02 = new CTriangle(v02, v12, v22);
    triangle02->matAmbient = {0.1,0.1,0.1};
    triangle02->matDiffuse = {0.4,0.4,0.4};
    triangle02->matSpecular = {0,0,0};
    triangle02->matShininess = 0;
    triangle02->reflectance = 1;
    triangle02->isTexture = false;
    objectList.push_back(triangle02);
}
