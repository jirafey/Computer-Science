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
    //    cam.eyep = {0, 0, 10};
    //    cam.lookp = {0, 0, 0};
    //    cam.up = {0, 1, 0};
    //    cam.fov = 50;
    //    cam.width = 500;
    //    cam.height = 400;

    cam.eyep = {0,0, 10};
    cam.lookp = {0,0,0};
    cam.up = {0, 1, 0};
    cam.fov = 50;
    cam.width = 500;
    cam.height = 400;


    // glm::vec3 v0 = {3,3,-5};
    // glm::vec3 v1 = {-3,3,-10};
    // glm::vec3 v2= {-3,-3,-8};
    // CTriangle* triangle01 = new CTriangle (v0, v1, v2);
    // objectList.push_back(triangle01);

    CSphere* sphere01 = new CSphere ({ 0.0 ,0.0 , 0.0} , 1.6);
    sphere01->matAmbient = {0.5, 0.0, 0.0};
    sphere01->matDiffuse = {0.0, 0.0, 0.0}; // 0.7-> 0.0
    sphere01->matSpecular = {0.0, 0.0, 0.0};
    sphere01->matShininess = 30;
    sphere01->reflectance = 0.0;
    sphere01->isTexture = false;

    objectList.push_back(sphere01);



    CLight light1(glm::vec3(-3, -2, 8));
    light1.color = {0.6f, 0.6f, 0.6f};
    lightList.push_back(light1);



    // CTriangle* triangle02 = new CTriangle (v0,v1,v2);
    // objectList.push_back(triangle02);

}


