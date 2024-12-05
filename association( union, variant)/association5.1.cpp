// У цій задачі задаються дані фігур та обчислюється їх площа та периметр. За допомогою variant

#include <iostream>
#include <variant>
#include <cmath>
#include <ctime>  // Для вимірювання часу

struct Circle {
    double radius;
};

struct Square {
    double side;
};

struct Triangle {
    double a, b, c;
};

struct Rectangle {
    double length, width;
};

struct Trapezoid {
    double a, b, h;
};

using Shape = std::variant<Circle, Square, Triangle, Rectangle, Trapezoid>;
// обчислення площ
struct AreaVisitor {
    double operator()(const Circle& c) const {
        return M_PI * c.radius * c.radius;
    }

    double operator()(const Square& s) const {
        return s.side * s.side;
    }

    double operator()(const Triangle& t) const {
        double p = (t.a + t.b + t.c) / 2;
        return std::sqrt(p * (p - t.a) * (p - t.b) * (p - t.c));
    }

    double operator()(const Rectangle& r) const {
        return r.length * r.width;
    }

    double operator()(const Trapezoid& t) const {
        return 0.5 * (t.a + t.b) * t.h;
    }
};
// обчисленні периметрів
struct PerimeterVisitor {
    double operator()(const Circle& c) const {
        return 2 * M_PI * c.radius;
    }

    double operator()(const Square& s) const {
        return 4 * s.side;
    }

    double operator()(const Triangle& t) const {
        return t.a + t.b + t.c;
    }

    double operator()(const Rectangle& r) const {
        return 2 * (r.length + r.width);
    }

    double operator()(const Trapezoid& t) const {
        return t.a + t.b + 2 * std::sqrt(std::pow((t.b - t.a) / 2, 2) + std::pow(t.h, 2));
    }
};

int main() {
    int choice;
    Shape shape;

    // Початок вимірювання часу
    clock_t start_time = clock();

    std::cout << "Виберіть фігуру для обчислення:" << std::endl;
    std::cout << "1. Круг" << std::endl;
    std::cout << "2. Квадрат" << std::endl;
    std::cout << "3. Трикутник" << std::endl;
    std::cout << "4. Прямокутник" << std::endl;
    std::cout << "5. Трапеція" << std::endl;
    std::cout << "Ваш вибір: ";
    std::cin >> choice;

    switch (choice) {
        case 1: // Круг
            {
                Circle c;
                std::cout << "Введіть радіус кола: ";
                std::cin >> c.radius;
                shape = c;
                break;
            }
        case 2: // Квадрат
            {
                Square s;
                std::cout << "Введіть довжину сторони квадрата: ";
                std::cin >> s.side;
                shape = s;
                break;
            }
        case 3: // Трикутник
            {
                Triangle t;
                std::cout << "Введіть сторони трикутника (a, b, c): ";
                std::cin >> t.a >> t.b >> t.c;
                shape = t;
                break;
            }
        case 4: // Прямокутник
            {
                Rectangle r;
                std::cout << "Введіть довжину та ширину прямокутника: ";
                std::cin >> r.length >> r.width;
                shape = r;
                break;
            }
        case 5: // Трапеція
            {
                Trapezoid t;
                std::cout << "Введіть основи та висоту трапеції (a, b, h): ";
                std::cin >> t.a >> t.b >> t.h;
                shape = t;
                break;
            }
        default:
            std::cout << "Невірний вибір.\n";
            return 1;
    }

    std::cout << "Площа: " << std::visit(AreaVisitor{}, shape) << std::endl;
    std::cout << "Периметр: " << std::visit(PerimeterVisitor{}, shape) << std::endl;

    // Кінець вимірювання часу
    clock_t end_time = clock();

    // Обчислення часу виконання
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    std::cout << "Час виконання: " << time_taken << " секунд" << std::endl;

    return 0;
}

