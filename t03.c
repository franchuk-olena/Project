#include <stdio.h>
#include <math.h>

// Структура для точки
typedef struct {
    float x, y;
} Point;

// Загальний тип для точки або вектора
typedef union {
    Point p;
} PointOrVector;

// Функція для перевірки колінеарності трьох точок
int areCollinear(Point p1, Point p2, Point p3) {
    // Якщо вектор (p1 -> p2) та вектор (p1 -> p3) колінеарні, то їх детермінант дорівнює нулю
    float area = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return (fabs(area) < 1e-6);  // Якщо детермінант ≈ 0, то точки колінеарні
}

int main() {
    // Визначення трьох точок
    Point p1, p2, p3;
    printf("Введіть координати першої точки (x1 y1): ");
    scanf("%f %f", &p1.x, &p1.y);

    printf("Введіть координати другої точки (x2 y2): ");
    scanf("%f %f", &p2.x, &p2.y);

    printf("Введіть координати третьої точки (x3 y3): ");
    scanf("%f %f", &p3.x, &p3.y);

    if (areCollinear(p1, p2, p3)) {
        printf("Вектори колінеарні\n");
    } else {
        printf("Вектори не колінеарні\n");
    }
    return 0;
}
