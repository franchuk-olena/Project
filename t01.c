#include <stdio.h>
#include <math.h>

typedef union {
    struct {
        double x;
        double y;
    } cartesian;  // Декартові координати
    struct {
        double r;
        double theta;
    } polar;  // Полярні координати
} Point;

// Обчислення відстані між точками в декартових координатах
double distance_cartesian(Point p1, Point p2) {
    return sqrt((p2.cartesian.x - p1.cartesian.x) * (p2.cartesian.x - p1.cartesian.x) +
                (p2.cartesian.y - p1.cartesian.y) * (p2.cartesian.y - p1.cartesian.y));
}

// Обчислення відстані між точками в полярних координатах
double distance_polar(Point p1, Point p2) {
    return sqrt(p1.polar.r * p1.polar.r + p2.polar.r * p2.polar.r -
                2 * p1.polar.r * p2.polar.r * cos(p1.polar.theta - p2.polar.theta));
}

int main() {
    Point p1, p2;
    int is_polar;

    printf("Виберіть тип координат (0 для декартових, 1 для полярних): ");
    scanf("%d", &is_polar);

    if (is_polar) {
        printf("Введіть полярні координати першої точки (r, theta): ");
        scanf("%lf %lf", &p1.polar.r, &p1.polar.theta);
        printf("Введіть полярні координати другої точки (r, theta): ");
        scanf("%lf %lf", &p2.polar.r, &p2.polar.theta);

        // Відстань для полярних координат
        printf("Відстань між точками (полярні координати): %lf\n", distance_polar(p1, p2));
    } else {
        printf("Введіть декартові координати першої точки (x, y): ");
        scanf("%lf %lf", &p1.cartesian.x, &p1.cartesian.y);
        printf("Введіть декартові координати другої точки (x, y): ");
        scanf("%lf %lf", &p2.cartesian.x, &p2.cartesian.y);

        // Відстань для декартових координат
        printf("Відстань між точками (декартові координати): %lf\n", distance_cartesian(p1, p2));
    }

    return 0;
}

