
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



    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    std::cout << "Camera projection matrix:" << std::endl;
    PRINT_MAT3(ray_matrix);


    /// main loop
    CImage image(scene.cam.width, scene.cam.height);

    for (int j = 0; j<scene.cam.height; j++)
    {
        for (int i = 0; i < scene.cam.width; i++)
        {
            /// position of the image point
            float fx = (float)i + 0.5f;
            float fy = (float)j + 0.5f;

            ray.pos = scene.cam.eyep;
            ray.dir = ray_matrix * glm::vec3(fx,fy,1.0f);
            ray.dir = glm::normalize(ray.dir);

            results.col = {0,0,0};
            //results.tree = 0;
            //results.energy = 1.0f;

            rt.rayTrace(scene, ray, results);

            if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1)
            {
                results.col = {1,1,1};
            }

            image.setPixel(i, j, results.col);
        }
    }

    cv::imshow("aaaa", image.getImage());
    cv::waitKey();


    /// writes image to disk file with gamma correction
    image.save("output_image.png", false);
    std::cout << std::endl << std::endl;
    return 0;
}

