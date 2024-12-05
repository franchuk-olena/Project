// У цій задачі обчислюється відстань між точками в декартових тп полярних координатах за допомогою union

// Приклад використання

//Виберіть тип координат (0 для декартових, 1 для полярних): 1
//Введіть полярні координати першої точки (r, theta): 5 1.57
//Введіть полярні координати другої точки (r, theta): 7 3.14
//Відстань між точками (полярні координати): 12.295817

//Виберіть тип координат (0 для декартових, 1 для полярних): 0
//Введіть декартові координати першої точки (x, y): 3 4
//Введіть декартові координати другої точки (x, y): 6 8
//Відстань між точками (декартові координати): 5.000000



#include <stdio.h>
#include <math.h>
#include <time.h>

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

        // Початок вимірювання часу для обчислення
        clock_t start_time = clock();
        double distance = distance_polar(p1, p2);
        clock_t end_time = clock();
        // Кінець вимірювання часу для обчислення

        // Відстань для полярних координат
        printf("Відстань між точками (полярні координати): %lf\n", distance_polar(p1, p2));
        printf("Час обчислення: %lf секунд\n",
               (double)(end_time - start_time) / CLOCKS_PER_SEC);
    } else {
        printf("Введіть декартові координати першої точки (x, y): ");
        scanf("%lf %lf", &p1.cartesian.x, &p1.cartesian.y);
        printf("Введіть декартові координати другої точки (x, y): ");
        scanf("%lf %lf", &p2.cartesian.x, &p2.cartesian.y);

        // Початок вимірювання часу для обчислення
        clock_t start_time = clock();
        double distance = distance_cartesian(p1, p2);
        clock_t end_time = clock();
        // Кінець вимірювання часу для обчислення

        // Відстань для декартових координат
        printf("Відстань між точками (декартові координати): %lf\n", distance_cartesian(p1, p2));
        printf("Час обчислення: %lf секунд\n",
               (double)(end_time - start_time) / CLOCKS_PER_SEC);
    }


    return 0;
}

