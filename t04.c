#include <stdio.h>
#include <math.h>

// Універсальний тип для представлення точки
typedef struct {
    enum { CARTESIAN, POLAR, SPHERICAL } type;
    union {
        struct { double x, y, z; } cartesian;       // Декартова
        struct { double r, theta; } polar;         // Полярна
        struct { double r, theta, phi; } spherical; // Сферична
    } coord;
} Point;

// Обчислення відстані між точками у декартовій системі
double distance_cartesian(Point p1, Point p2) {
    double dx = p1.coord.cartesian.x - p2.coord.cartesian.x;
    double dy = p1.coord.cartesian.y - p2.coord.cartesian.y;
    double dz = p1.coord.cartesian.z - p2.coord.cartesian.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// Обчислення відстані між точками у полярній системі
double distance_polar(Point p1, Point p2) {
    double x1 = p1.coord.polar.r * cos(p1.coord.polar.theta);
    double y1 = p1.coord.polar.r * sin(p1.coord.polar.theta);
    double x2 = p2.coord.polar.r * cos(p2.coord.polar.theta);
    double y2 = p2.coord.polar.r * sin(p2.coord.polar.theta);
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// Обчислення відстані між точками у сферичній системі
double distance_spherical(Point p1, Point p2) {
    double x1 = p1.coord.spherical.r * sin(p1.coord.spherical.theta) * cos(p1.coord.spherical.phi);
    double y1 = p1.coord.spherical.r * sin(p1.coord.spherical.theta) * sin(p1.coord.spherical.phi);
    double z1 = p1.coord.spherical.r * cos(p1.coord.spherical.theta);

    double x2 = p2.coord.spherical.r * sin(p2.coord.spherical.theta) * cos(p2.coord.spherical.phi);
    double y2 = p2.coord.spherical.r * sin(p2.coord.spherical.theta) * sin(p2.coord.spherical.phi);
    double z2 = p2.coord.spherical.r * cos(p2.coord.spherical.theta);

    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
}

int main() {
    // Введення двох точок
    Point p1, p2;

    int system;
    printf("Оберіть систему координат (1 - декартова, 2 - полярна, 3 - сферична): ");
    scanf("%d", &system);

    if (system == 1) { // Декартова
        p1.type = CARTESIAN;
        p2.type = CARTESIAN;
        printf("Введіть x, y, z для першої точки: ");
        scanf("%lf %lf %lf", &p1.coord.cartesian.x, &p1.coord.cartesian.y, &p1.coord.cartesian.z);
        printf("Введіть x, y, z для другої точки: ");
        scanf("%lf %lf %lf", &p2.coord.cartesian.x, &p2.coord.cartesian.y, &p2.coord.cartesian.z);
        printf("Відстань: %.2f\n", distance_cartesian(p1, p2));
    } else if (system == 2) { // Полярна
        p1.type = POLAR;
        p2.type = POLAR;
        printf("Введіть r, theta (у радіанах) для першої точки: ");
        scanf("%lf %lf", &p1.coord.polar.r, &p1.coord.polar.theta);
        printf("Введіть r, theta (у радіанах) для другої точки: ");
        scanf("%lf %lf", &p2.coord.polar.r, &p2.coord.polar.theta);
        printf("Відстань: %.2f\n", distance_polar(p1, p2));
    } else if (system == 3) { // Сферична
        p1.type = SPHERICAL;
        p2.type = SPHERICAL;
        printf("Введіть r, theta, phi (у радіанах) для першої точки: ");
        scanf("%lf %lf %lf", &p1.coord.spherical.r, &p1.coord.spherical.theta, &p1.coord.spherical.phi);
        printf("Введіть r, theta, phi (у радіанах) для другої точки: ");
        scanf("%lf %lf %lf", &p2.coord.spherical.r, &p2.coord.spherical.theta, &p2.coord.spherical.phi);
        printf("Відстань: %.2f\n", distance_spherical(p1, p2));
    } else {
        printf("Неправильний вибір системи координат!\n");
    }

    return 0;
}
