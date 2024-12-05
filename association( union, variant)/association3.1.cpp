//У цій задачі використовується  універсальний тип, що дозволяє представляти вектор в як дві точки та як точку та вектор до другої точки. Вводиться три вектори та
//перевіряється чи колінеарні вони за допомогою variant

//Введіть координати першої точки (x1 y1): 0 0
//Введіть координати другої точки (x2 y2): 1 1
//Введіть координати третьої точки (x3 y3): 2 2
//Вектори колінеарні

//Введіть координати першої точки (x1 y1): 0 0
//Введіть координати другої точки (x2 y2): 1 1
//Введіть координати третьої точки (x3 y3): 2 3
//Вектори не колінеарні



#include <iostream>
#include <variant>
#include <cmath>
#include <ctime>  // Для вимірювання часу

// Структури для точок
struct Point {
    float x, y;
};

// Універсальний тип для точки або вектора
using PointOrVector = std::variant<Point>;

// Функція для перевірки колінеарності трьох точок
bool areCollinear(const Point& p1, const Point& p2, const Point& p3) {
    float area = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return std::fabs(area) < 1e-6;
}

int main() {
    // Введення трьох точок користувачем
    Point p1, p2, p3;

    // Початок вимірювання часу
    clock_t start_time = clock();

    std::cout << "Введіть координати першої точки (x1 y1): ";
    std::cin >> p1.x >> p1.y;

    std::cout << "Введіть координати другої точки (x2 y2): ";
    std::cin >> p2.x >> p2.y;

    std::cout << "Введіть координати третьої точки (x3 y3): ";
    std::cin >> p3.x >> p3.y;

    if (areCollinear(p1, p2, p3)) {
        std::cout << "Вектори колінеарні" << std::endl;
    } else {
        std::cout << "Вектори не колінеарні" << std::endl;
    }

    // Кінець вимірювання часу
    clock_t end_time = clock();

    // Обчислення часу виконання
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Час виконання: " << time_taken << " секунд" << std::endl;

    return 0;
}

