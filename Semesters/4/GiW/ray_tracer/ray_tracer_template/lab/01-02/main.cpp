#include <iostream>
#include "rt.h"

extern void draw_robot();
extern void draw_triangles();

int main (int argc, char * const argv[]) {
    draw_robot();
    return 0;
}

/// Draws robot.
void draw_robot() {
    CImage img(1000, 1000); // obraz 1000x1000
    glm::vec3 color1(0.94, 0.82, 0.67); // czerowny

    /// Rysowanie koła w punkcie (pp)
    glm::vec3 pp(0.0, 0.45, 1.0);
    float radius = 0.1f; // promień
    img.drawCircle(pp, radius, color1);

    /// Rysowanie prostokąta na środku
    // punkty
    glm::vec3 pp0(-0.2, 0.3, 1);
    glm::vec3 pp1(0.2, 0.3, 1);
    glm::vec3 pp2(0.2, -0.3, 1);
    glm::vec3 pp3(-0.2, -0.3, 1);

    // rysowanie linii
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp3, color1);
    img.drawLine(pp3, pp0, color1);

    /// Rysowanie prostokąta po prawej stronie
    // punkty
    glm::vec3 l0(-0.25, 0.3, 1);
    glm::vec3 l1(-0.25, 0.2, 1);
    glm::vec3 l2(-0.6, 0.2, 1);
    glm::vec3 l3(-0.6, 0.3, 1);

    // rysowanie linii
    img.drawLine(l0, l1, color1);
    img.drawLine(l1, l2, color1);
    img.drawLine(l2, l3, color1);
    img.drawLine(l3, l0, color1);

    /// Rysowanie prostokąta po lewej stronie na dole
    // punkty
    glm::vec3 p0(0.25, 0.3, 1);
    glm::vec3 p1(0.25, 0.2, 1);
    glm::vec3 p2(0.6, 0.2, 1);
    glm::vec3 p3(0.6, 0.3, 1);

    // rysowanie linii
    img.drawLine(p0, p1, color1);
    img.drawLine(p1, p2, color1);
    img.drawLine(p2, p3, color1);
    img.drawLine(p3, p0, color1);

    // Rysowanie prostokąta po lewej stronie na dole
    glm::vec3 n0(0.17, -0.35, 1); // (lewa strona dół) początek
    glm::vec3 n1(0.25, -0.30, 1); // (lewa strona dół) koniec
    p0 = n0;
    p1 = n1;

    float tX = 0.2f;
    float tY = -0.4f;
    glm::mat3x3 mTrans {{1, 0, 0}, {0, 1, 0}, {tX, tY, 1}};
    // mTrans, przesuwa punkty o tX wzdłuż osi X i tY wzdłuż osi Y
    PRINT_MAT3(mTrans);

    n0 = mTrans * n0; // Przesunięcie o mTrans
    n1 = mTrans * n1;

    // rysowanie linii
    img.drawLine(p0, p1, color1);
    img.drawLine(p1, n1, color1);
    img.drawLine(n1, n0, color1);
    img.drawLine(p0, n0, color1);

    /// Rysowanie prostokąta po prawej stronie na dole
    glm::vec3 n2(-0.17, -0.35, 1);// (prawa strona dół) początek
    glm::vec3 n3(-0.25, -0.30, 1);// (prawa strona dół) początek
    p2 = n2;
    p3 = n3;

    img.drawLine(n0, n1, color1);
    tX = -0.2f;
    tY = -0.4f;
    glm::mat3x3 mTrans2 {{1, 0, 0}, {0, 1, 0}, {tX, tY, 1}}; // macierz translacji
    // mTrans, przesuwa punkty o tX wzdłuż osi X i tY wzdłuż osi Y
    PRINT_MAT3(mTrans2);

    n2 = mTrans2 * n2; // Przesunięcie o mTrans
    n3 = mTrans2 * n3;

    // rysowanie linii
    img.drawLine(p2, p3, color1);
    img.drawLine(p3, n3, color1);
    img.drawLine(n3, n2, color1);
    img.drawLine(p2, n2, color1);

    // Zapisanie obrazu do pliku
    img.save("robot.png");

    // Wyświetlenie obrazu
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();
}