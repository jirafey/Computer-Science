
#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();

///
int main (int argc, char * const argv[]) {
    
//    draw_triangles();
//    return 0;



    std::cout << "ray tracing ... \n";

    CScene scene;
    scene.create(); // defines sample scene parameters
    if(scene.cam.width == 0) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return -1;
    }

    CRayTrace rt;
    CRay ray;
    COutput results;

    /// computes primary ray matrix
    // glm::mat3 ray_matrix;
    // CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    // std::cout << "Camera projection matrix:" << std::endl;
    // PRINT_MAT3(ray_matrix);

    /// computes ray direction for sample pixel positions
    // ...


    /// creates raster image object
    // CImage image(scene.cam.width, scene.cam.height);

    /// main loop

            /// position of the image point
            /// ...

            /// primary ray
            /// ...

            /// background color
            // results.col = {0,0,0};
            /// secondary ray counter
            // results.tree = 0;
            /// ray energy
            // results.energy = 1.0f;
            
            /// rendering
            /// rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
            // if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
            //    results.col = {1,1,1};
            //}

            /// writes pixel to output image
            // image.setPixel(i, j, results.rgb);


    /// writes image to disk file with gamma correction
    // image.save("output.png", true);

    // cv::imshow("image", image.getImage());
    // cv::waitKey();
    
    std::cout << std::endl << std::endl;

//    x = ray.pos.x + t * ray.dir.x;
//    y = ray.pos.y + t * ray.dir.y;
//    z = ray.pos.z + t * ray.dir.z
//    std::vector<CObject*> objectList;
//    CSphere* sphere = new CSphere ({ -2.5 ,1.3 , -3} , 1.0);
//    CSphere* sphere2 = new CSphere ({ 0,0,0} , 1.6);
//    objectList.push_back(sphere);
//    objectList.push_back(sphere2);
//    double x = ray.pos.x + t * ray.dir.x;
//    double y = ray.pos.y + t * ray.dir.y;
//    double z = ray.pos.z + t * ray.dir.z;
//    w = ray.pos + t * ray.dir
    CSphere* sphere3 = new CSphere ({ 0,0,0} , 5);
    ray.dir = {0.3, 0.3, -1};
    ray.pos = {0,0,10};
    return 0;
}



/// Draws two trianges
void draw_triangles() {

    CImage img(1000, 1000);
    
    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green
    
    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
//    img.drawCircle(pp, radius, color1);
    
    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);
    
    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);
    
    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();



}
