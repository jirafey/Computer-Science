// main.cpp
int main (int argc, char * const argv[]) {
    CRay ray;
    CSphere* sphere3 = new CSphere ({ 0,0,0} , 5);
    ray.dir = {0.3, 0.3, -1};
    ray.pos = {0,0,10};
    std::cout << sphere3->intersect(ray);
    return 0;
}

