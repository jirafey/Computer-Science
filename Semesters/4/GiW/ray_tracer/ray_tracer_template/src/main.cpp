
#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();

///
int main (int argc, char * const argv[]) {

    //draw_triangles();
    //draw_robot();
    //return 0;

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

    CImage image(scene.cam.width, scene.cam.height);

    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    std::cout << "Camera projection matrix:" << std::endl;
    PRINT_MAT3(ray_matrix);

    ray.pos = {0,0,0};
    ray.dir = {0.5f,0.5f,0.0f};
    glm::vec3 n{0,1.0,0};
    glm::vec3 pos{0,0,0};
    CRay ray_reflected = rt.reflectedRay(ray,n,pos);
    std::cout << "RRP: " << "(" << ray_reflected.pos.x << "," << ray_reflected.pos.y << "," << ray_reflected.pos.z << ")" << "\nRRD" << "(" <<ray_reflected.dir.x << "," << ray_reflected.dir.y << "," << ray_reflected.dir.z << ")" << std::endl;


    ray.pos = scene.cam.eyep;



    /// main loop
    for(int j = 0; j < scene.cam.height; j++){
        for(int i = 0; i < scene.cam.width; i++){


            /// position of the image point
            float fx = (float)i+0.5f;
            float fy = (float)j+0.5f;

            /// primary ray
            ray.dir = glm::normalize((ray_matrix*glm::vec3(fx,fy,1)));
            /*
                        glm::vec3 rgb(0.0f,0.0f,0.0f);
                        rgb.x = (ray.dir.x+ 1.0f)/2.0f;
            */


            /// background color
            results.col = {0,0,0};
            /// secondary ray counter
            results.tree = 0;
            /// ray energy
            results.energy = 1.0f;

            /// rendering
            rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
            if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
                results.col = {1,1,1};
            }

            /// writes pixel to output image
            image.setPixel(i, j, results.col);
            //image.setPixel(i,j,rgb);

        }
    }
    /// writes image to disk file with gamma correction
    image.save("output_image.png", false);
    cv::imshow("image", image.getImage());
    cv::waitKey();

    std::cout << std::endl << std::endl;
    return 0;
}


