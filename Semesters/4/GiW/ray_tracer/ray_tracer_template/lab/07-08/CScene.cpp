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

